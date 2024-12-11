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
	
	// Variables Ragdolls
	rag_Count = 0; rag_ReadyToDraw = 0, rag_Shot = 0;
	for (int i = 0; i < 50; i++) { rag_Instantiated[i] = false; }

	InitCamera();
	InitPhysics();
	InitSprites();

	// Inicializa el Level Manager
	lvl_Manager = new LevelManager(phyWorld, 0);
	// Inicializa el UI Manager
	ui_Manager = new UI_Manager();

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
	debugRender->SetFlags(0);
	phyWorld->SetDebugDraw(debugRender);

	// Crea el suelo, muros laterales y techo
	for (int i = 0; i < 2; i++) { borders[i] = Box2DHelper::CreateRectangularStaticBody(phyWorld, 120, 10, 0.5f); }
	borders[0]->SetTransform(b2Vec2(50.0f, 99.5f), 0.0f);
	borders[1]->SetTransform(b2Vec2(50.0f, -0.5f), 0.0f);
	for (int i = 2; i < 4; i++){ borders[i] = Box2DHelper::CreateRectangularStaticBody(phyWorld, 10, 120, 0.5f); }
	borders[2]->SetTransform(b2Vec2(-4.5f, 50.0f), 0.0f);
	borders[3]->SetTransform(b2Vec2(104.5f, 50.0f), 0.0f);

	// Crea el cañon
	canon = Box2DHelper::CreateRectangularStaticBody(phyWorld, 9, 3);
	canon->SetTransform(b2Vec2(4.5f, 90.5f), 0);

	canonBase = Box2DHelper::CreateCircularStaticBody(phyWorld, 3.5);
	canonBase->SetTransform(canon->GetPosition(), 0);

}

void Game::InitSprites() {

	// Bordes
	txt_UpDown_Edge.loadFromFile("Sprites/lvl_Sprites/Up-Down_Edge.png");
	SetUpSprite(borders[0], txt_UpDown_Edge, spr_UpDown_Edge[0]);
	SetUpSprite(borders[1], txt_UpDown_Edge, spr_UpDown_Edge[1]);

	txt_SideEdge.loadFromFile("Sprites/lvl_Sprites/Side_Edge.png");
	SetUpSprite(borders[2], txt_SideEdge, spr_Side_Edge[0]);
	SetUpSprite(borders[3], txt_SideEdge, spr_Side_Edge[1]);

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
			CheckCollisions();
			UpdateCamera();
			DrawGame();
			wnd->display();

		}
	}
}

void Game::DrawGame() {

	// Dibuja los bordes del nivel
	for (int i = 0; i < 2; i++) { wnd->draw(spr_Side_Edge[i]); }
	for (int i = 0; i < 2; i++) { wnd->draw(spr_UpDown_Edge[i]); }

	// Dibuja el nivel actual
	lvl_Manager->DrawLevel(*wnd);

	// Dibuja los textos
	ui_Manager->Draw_Text(*wnd, lvl_Manager->GetCurrentLevel(), rag_Shot);

	// Dibuja el Cañon
	wnd->draw(spr_canon);
	spr_canon.setRotation(rad2deg(canon->GetAngle()));

	// Dibuja los Ragdolls
	for (int i = 0; i < rag_ReadyToDraw; i++) { rag_i[i]->Draw(*wnd); }

}

void Game::UpdatePhysics() {
	phyWorld->Step(frameTime, 8, 8);
	phyWorld->ClearForces();
	phyWorld->DebugDraw();
}

void Game::CheckCollisions() {
	// Si un ragdoll entra en la zona de salida del nivel
	for (int i = 0; i < rag_ReadyToDraw; i++) {
		if (lvl_Manager->GetExitBounds().contains(rag_i[i]->GetPosition().x, rag_i[i]->GetPosition().y)) {
			lvl_Manager->NextLevel();
			ResetRagdolls();
		}
	}
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
				if (evt.key.code == Keyboard::F1)		{
					// Activa|Desactiva la vista de Debug
					if (debugRender->GetFlags() == UINT_MAX) { debugRender->SetFlags(0); }
					else { debugRender->SetFlags(UINT_MAX); }
				}
				if (evt.key.code == Keyboard::Z)		{
					if (rag_Count > 0) { toggleZoom = !toggleZoom; }
				}
				if (evt.key.code == Keyboard::R)		{
					//Reinicio del nivel actual
					lvl_Manager->ResetLevel();
					ResetRagdolls();
				}
				if (evt.key.code == Keyboard::L) { lvl_Manager->NextLevel(); ResetRagdolls(); }
				if (evt.key.code == Keyboard::Space)	{ pause = !pause; }

			case Event::MouseButtonPressed:		// Inputs del mouse
				if (evt.mouseButton.button == Mouse::Left && !toggleZoom) {

					if (rag_Count >= 50) { rag_Count = 0; }
					rag_Shot++;

					if (rag_Instantiated[rag_Count] == false) {
						rag_Instantiated[rag_Count] = true;

						// Calcula la posicion de la punta del cañon y lo spawnea en esa posicion
						rag_i[rag_Count] = new Ragdoll(phyWorld, Vector2f(canon->GetPosition().x + 6 * cos(canon->GetAngle()), canon->GetPosition().y + 6 * sin(canon->GetAngle())), 0);

						// Calcula la direccion en la cual aplicar la fuerza al ragdoll disparado
						rag_i[rag_Count]->ApplyForce({ mouse_PosCoord.x - canon->GetPosition().x, mouse_PosCoord.y - canon->GetPosition().y });

						rag_Count++; rag_ReadyToDraw++;
					}
					else {
						
						// Calcula la posicion de la punta del cañon y lo resetea en esa posicion
						rag_i[rag_Count]->Reset(Vector2f(canon->GetPosition().x + 6 * cos(canon->GetAngle()), canon->GetPosition().y + 6 * sin(canon->GetAngle())));

						// Calcula la direccion en la cual aplicar la fuerza al ragdoll disparado
						rag_i[rag_Count]->ApplyForce({ mouse_PosCoord.x - canon->GetPosition().x, mouse_PosCoord.y - canon->GetPosition().y });

						rag_Count++;
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
		UpdateCameraPos(rag_i[rag_Count - 1]->GetPosition());
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

void Game::ResetRagdolls() {
	//Reinicia los ragdolls
	Vector2f resetOffset = Vector2f(0, -200);
	for (int i = 0; i <= rag_ReadyToDraw; i++) {
		if (rag_Instantiated[i] == true) { 
			rag_i[i]->Disable(resetOffset);
			resetOffset = resetOffset + Vector2f(20, 0);
		}
	}
	rag_Shot = 0; rag_Count = 0;
	toggleZoom = false;
}

float Game::deg2rad(float deg) {
	
	float pi = 3.14f;
	return deg * pi / 180;

}

float Game::rad2deg(float rad) {

	float pi = 3.14f;
	return rad / pi * 180;

}