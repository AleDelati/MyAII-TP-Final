#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "SFMLRenderer.h"
#include "Actor.h"
#include "Ragdoll.h"
#include <list>

using namespace sf;
class Game {

	private:
		// Propiedades de la ventana
		int height, width;
		RenderWindow *wnd;
		Color clearColor;

		float fps, frameTime, time_2;
		Clock* clock_1;
		Time* time_1;

		//					-| Box2D |-

		b2World* phyWorld;
		SFMLRenderer* debugRender;

		// Piso
		b2Body* groundBody;

		// Caja
		b2Body* bdy_Box;
		Actor* act_Box;

		// Cañon
		b2Body* canonWheel;
		b2Body* canonBase;
		b2Body* canon;

		// Ragdolls
		Ragdoll* rag_1;
		Ragdoll* rag_2;

		//					-| Texturas y Sprites |-

		Texture txt_ground;
		Texture txt_box;
		
		Sprite spr_ground;
		Sprite spr_box;

	public:

		// Constructores, destructores e inicializadores
		Game(int ancho, int alto,std::string titulo);
		~Game(void);

		void SetZoom();
		void InitPhysics();
		void InitSprites();
		void InitActors();

		// Main game loop
		void Loop();
		void DrawGame();
		void UpdatePhysics();
		void CheckCollitions();
		void DoEvents();

		float deg2rad(float deg);
		float rad2deg(float rad);
		
};

