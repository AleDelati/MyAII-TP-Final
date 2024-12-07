#include "Game.h"
#include "Box2DHelper.h"

//					-| Constructores, destructores e inicializadores |-
Game::Game(int ancho, int alto, std::string titulo) {
	
	pause = false, toggleZoom = false;
	fps = 60.0f; frameTime = 1.0f / fps;
	clock_1 = new Clock; time_1 = new Time; 

	wnd = new RenderWindow(VideoMode(ancho, alto), titulo);
	wnd->setVisible(true);
	wnd->setFramerateLimit(fps);
	
	ragdollsCount = -1;
	for (int i = 0; i < 50; i++) { instantiatedRagdolls[i] = false; }

	InitCamera();
	InitPhysics();
	InitSprites();

}

Game::~Game(void) {
	
}

// Definimos el area del mundo que veremos en nuestro juego
// Box2D tiene problemas para simular magnitudes muy grandes
void Game::InitCamera() {
	// Posicion del view
	camera.setSize(100.0f, 100.0f);
	camera.setCenter(50.0f, 50.0f);
	wnd->setView(camera); //asignamos la camara
}

void Game::InitPhysics() {
	// Inicializamos el mundo con la gravedad por defecto
	phyWorld = new b2World(b2Vec2(0.0f, 9.8f * 3));

	// Creamos el renderer de debug y le seteamos las banderas para que dibuje TODO
	debugRender = new SFMLRenderer(wnd);
	debugRender->SetFlags(UINT_MAX);
	//phyWorld->SetDebugDraw(debugRender);

	// Crea el suelo, muros laterales y techo
	groundBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 100, 10, 0.5f);
	groundBody->SetTransform(b2Vec2(50.0f, 99.45f), 0.0f);

	for (int i = 0; i < 3; i++) { borders[i] = Box2DHelper::CreateRectangularStaticBody(phyWorld, 100, 10); }
	borders[0]->SetTransform(b2Vec2(50.0f, -5.0f), 0.0f);
	borders[1]->SetTransform(b2Vec2(-5.0f, 50.0f), deg2rad(90));
	borders[2]->SetTransform(b2Vec2(105.0f, 50.0f), deg2rad(-90));

	// Crea el cañon
	canon = Box2DHelper::CreateRectangularStaticBody(phyWorld, 9, 3);
	canon->SetTransform(b2Vec2(2.0f, 93.0f), 0);

	canonBase = Box2DHelper::CreateCircularStaticBody(phyWorld, 3.5);
	canonBase->SetTransform(canon->GetPosition(), 0);

	// Inicializa el Level Manager
	lvl_Manager = new LevelManager(phyWorld, 0);
}

void Game::InitSprites() {

	// Suelo
	txt_ground.loadFromFile("Sprites/Edge.png");
	SetUpSprite(groundBody, txt_ground, spr_ground);

	// Cañon
	txt_canon.loadFromFile("Sprites/Canon.png");
	SetUpSprite(canon, txt_canon, spr_canon);

}

//					-| Main game loop |-

void Game::Loop() {
	while(wnd->isOpen()) {

		*time_1 = clock_1->getElapsedTime();
		if (time_2 + frameTime < time_1->asSeconds()) {

			wnd->clear(clearColor);
			DoEvents();
			UpdateCanon();
			if(!pause){ UpdatePhysics(); }
			UpdateCamera();
			DrawGame();
			wnd->display();

		}
	}
}

void Game::DrawGame() {

	// Dibuja el Cañon
	//wnd->draw(spr_canonBase);
	wnd->draw(spr_canon);
	spr_canon.setRotation(rad2deg(canon->GetAngle()));

	wnd->draw(spr_ground);
	
	// Dibuja el nivel actual
	lvl_Manager->DrawLevel(*wnd);

	// Dibuja los Ragdolls
	for (int i = 0; i < 50; i++) {
		if (i <= ragdollsCount) {
			if (rag_i[i] != nullptr) {
				rag_i[i]->Draw(*wnd);
			}
		}
	}

}

void Game::UpdatePhysics() {
	phyWorld->Step(frameTime, 8, 8);
	phyWorld->ClearForces();
	phyWorld->DebugDraw();
}

void Game::UpdateCanon() {

	// Actualiza la posicion del mouse relativa a la ventana
	mouse_Pos = Mouse::getPosition(*wnd);
	mouse_PosCoord = wnd->mapPixelToCoords(mouse_Pos);

	// Calcula el angulo de la posicion objetivo para rotar el cañon
	float targetPos = atan2f(mouse_PosCoord.y - canon->GetPosition().y, mouse_PosCoord.x - canon->GetPosition().x);
	// Rota el cañon en el angulo calculado solo si el angulo esta dentro del rango deseado ( de 0° a -90° )
	if (rad2deg(targetPos) <= 0 && rad2deg(targetPos) >= -90) {
		canon->SetTransform(canon->GetPosition(), targetPos);
	}

}

void Game::DoEvents() {
	Event evt;
	while(wnd->pollEvent(evt)) {
		switch(evt.type) {
			case Event::Closed:
				wnd->close();
				break;

			case Event::KeyPressed:				// Inputs del teclado
				if (evt.key.code == Keyboard::Escape)	{ wnd->close(); }
				if (evt.key.code == Keyboard::Z)		{ toggleZoom = !toggleZoom; }
				if (evt.key.code == Keyboard::R)		{
					//Reinicio del nivel actual
					lvl_Manager->ResetLevel();
					//Reinicia los ragdolls
					for (int i = 0; i <= ragdollsCount; i++) {
						rag_i[i]->Disable();
						if (i == ragdollsCount) { ragdollsCount = -1; }
					}
				}
				if (evt.key.code == Keyboard::L)		{ lvl_Manager->NextLevel(); }
				if (evt.key.code == Keyboard::Space)	{ pause = !pause; }

			case Event::MouseButtonPressed:		// Inputs del mouse
				if (evt.mouseButton.button == Mouse::Left) {

					if (instantiatedRagdolls[ragdollsCount+1] == false) {
						instantiatedRagdolls[ragdollsCount + 1] = true;
						ragdollsCount++;

						// Calcula la posicion de la punta del cañon y lo spawnea en esa posicion
						rag_i[ragdollsCount] = new Ragdoll(phyWorld, Vector2f(canon->GetPosition().x + 6 * cos(canon->GetAngle()), canon->GetPosition().y + 6 * sin(canon->GetAngle())), 0);

						// Calcula la direccion en la cual aplicar la fuerza al ragdoll disparado
						rag_i[ragdollsCount]->ApplyForce({ mouse_PosCoord.x - canon->GetPosition().x, mouse_PosCoord.y - canon->GetPosition().y });
					}
					else {
						ragdollsCount++;

						// Calcula la posicion de la punta del cañon y lo resetea en esa posicion
						rag_i[ragdollsCount]->Reset(Vector2f(canon->GetPosition().x + 6 * cos(canon->GetAngle()), canon->GetPosition().y + 6 * sin(canon->GetAngle())));

						// Calcula la direccion en la cual aplicar la fuerza al ragdoll disparado
						rag_i[ragdollsCount]->ApplyForce({ mouse_PosCoord.x - canon->GetPosition().x, mouse_PosCoord.y - canon->GetPosition().y });
					}
					
				}
				
			case Event::MouseButtonReleased:
				
				break;
		}
	}
}

void Game::UpdateCamera() {
	
	// Al Activar el Zoom, se lleva a cabo en el ultimo ragdoll disparado por el cañon
	if (toggleZoom) {
		SetZoom(Vector2f(15.0f, 15.0f));
		UpdateCameraPos(rag_i[ragdollsCount]->GetPosition());
	}
	else {
		SetZoom(Vector2f(100.0f, 100.0f)); 
		UpdateCameraPos(b2Vec2(50.0f, 50.0f));
	}
	wnd->setView(camera);
}

//					-| Aux |-

// Setea el sprite para que coincida su tamaño con el del body asignado
void Game::SetUpSprite(b2Body *body, Texture &txt, Sprite &spr) {

	spr.setTexture(txt);

	spr.setOrigin(txt.getSize().x / 2.0f, txt.getSize().y / 2.0f);
	spr.setPosition(body->GetPosition().x, body->GetPosition().y);
	spr.setRotation(rad2deg(body->GetAngle()));

	b2AABB dimension;
	dimension.upperBound = b2Vec2(-FLT_MAX, -FLT_MAX);
	dimension.lowerBound = b2Vec2(FLT_MAX, FLT_MAX);
	for (b2Fixture* f = body->GetFixtureList(); f != NULL; f = f->GetNext()) {
		dimension = f->GetAABB(0);
	}

	spr.setScale(dimension.GetExtents().x * 2 / txt.getSize().x, dimension.GetExtents().y * 2 / txt.getSize().y);

}

void Game::SetZoom(Vector2f zoom) {
	camera.setSize(zoom.x, zoom.y);
}

void Game::UpdateCameraPos(b2Vec2 pos) {
	camera.setCenter(pos.x, pos.y);
}

float Game::deg2rad(float deg) {
	
	float pi = 3.14f;
	return deg * pi / 180;

}

float Game::rad2deg(float rad) {

	float pi = 3.14f;
	return rad / pi * 180;

}