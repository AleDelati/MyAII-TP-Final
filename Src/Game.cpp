#include "Game.h"
#include "Box2DHelper.h"

//					-| Constructores, destructores e inicializadores |-
Game::Game(int ancho, int alto, std::string titulo) {
	
	fps = 60.0f; frameTime = 1.0f / fps;
	clock_1 = new Clock; time_1 = new Time; 

	wnd = new RenderWindow(VideoMode(ancho, alto), titulo);
	wnd->setVisible(true);
	wnd->setFramerateLimit(fps);
	
	SetZoom();
	InitPhysics();
	InitSprites();
	InitActors();

}

Game::~Game(void) {

}

// Definimos el area del mundo que veremos en nuestro juego
// Box2D tiene problemas para simular magnitudes muy grandes
void Game::SetZoom() {
	View camara;
	// Posicion del view
	camara.setSize(100.0f, 100.0f);
	camara.setCenter(50.0f, 50.0f);
	wnd->setView(camara); //asignamos la camara
}

void Game::InitPhysics() {
	// Inicializamos el mundo con la gravedad por defecto
	phyWorld = new b2World(b2Vec2(0.0f, 9.8f));

	// Creamos el renderer de debug y le seteamos las banderas para que dibuje TODO
	debugRender = new SFMLRenderer(wnd);
	debugRender->SetFlags(UINT_MAX);
	phyWorld->SetDebugDraw(debugRender);

	// Crea el piso
	groundBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 100, 10);
	groundBody->SetTransform(b2Vec2(50.0f, 100.0f), 0.0f);

	// Crea la Caja
	bdy_Box = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 3, 3, 1.0f, 0.3f, 0.1f);
	bdy_Box->SetTransform(b2Vec2(50.0f, 50.0f), 0.0f);

	// Crea el cañon
	canonWheel = Box2DHelper::CreateCircularStaticBody(phyWorld, 2.0f);
	canonWheel->SetTransform(b2Vec2(8.0f, 93.0f), 0.0f);

	canonBase = Box2DHelper::CreateRectangularStaticBody(phyWorld, 15, 1);
	canonBase->SetTransform(b2Vec2(4.0f, 92.0f), canonBase->GetAngle() + deg2rad(-10.0f));

	canon = Box2DHelper::CreateRectangularStaticBody(phyWorld, 9, 3);
	canon->SetTransform(b2Vec2(11.0f, 90.0f), 0.0f);
}

void Game::InitSprites() {

	txt_ground.loadFromFile("Sprites/Edge.png");

	spr_ground.setTexture(txt_ground);
	spr_ground.setOrigin({ txt_ground.getSize().x / 2.0f, txt_ground.getSize().y / 2.0f });

	txt_box.loadFromFile("Sprites/Box.png");
	spr_box.setTexture(txt_box);
	spr_box.setOrigin({ txt_box.getSize().x / 2.0f, txt_box.getSize().y / 2.0f });

}

void Game::InitActors() {

	act_Box = new Actor(bdy_Box, spr_box);

}

//					-| Main game loop |-

void Game::Loop() {
	while(wnd->isOpen()) {

		*time_1 = clock_1->getElapsedTime();
		if (time_2 + frameTime < time_1->asSeconds()) {

			wnd->clear(clearColor);
			DoEvents();
			CheckCollitions();
			UpdatePhysics();
			DrawGame();
			wnd->display();

		}
	}
}

void Game::DrawGame() {

	wnd->draw(spr_ground);
	spr_ground.setPosition(groundBody->GetPosition().x, groundBody->GetPosition().y);

	act_Box->Draw(*wnd);

}

void Game::UpdatePhysics() {
	phyWorld->Step(frameTime, 8, 8);
	phyWorld->ClearForces();
	phyWorld->DebugDraw();
}

void Game::CheckCollitions() {
	// Veremos mas adelante
}

void Game::DoEvents() {
	Event evt;
	while(wnd->pollEvent(evt)) {
		switch(evt.type) {
			case Event::Closed:
				wnd->close();
				break;
			case Event::MouseButtonPressed:
				
				break;
			case Event::MouseButtonReleased:
				
				break;
		}
	}
}

float Game::deg2rad(float deg) {
	
	float pi = 3.14f;
	return deg * pi / 180;

}

float Game::rad2deg(float rad) {

	float pi = 3.14f;
	return rad / pi * 180;

}