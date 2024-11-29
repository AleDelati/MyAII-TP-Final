#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "SFMLRenderer.h"
#include "Ragdoll.h"
#include <list>

using namespace sf;
class Game {

	private:
		// Propiedades de la ventana
		int height, width;
		RenderWindow *wnd;
		Color clearColor;

		bool pause, toggleZoom;
		float fps, frameTime, time_2;
		Clock* clock_1;
		Time* time_1;

		View camera;
		//					-| Box2D |-

		b2World* phyWorld;
		SFMLRenderer* debugRender;

		// Piso
		b2Body* groundBody;

		// Cañon
		b2Body* canonWheel;
		b2Body* canonBase;
		b2Body* canon;

		// Ragdoll
		Ragdoll* rag_1;

		//					-| Texturas y Sprites |-

		Texture txt_ground;
		
		Sprite spr_ground;

	public:

		// Constructores, destructores e inicializadores
		Game(int ancho, int alto,std::string titulo);
		~Game(void);

		void InitCamera();
		void InitPhysics();
		void InitSprites();

		// Main game loop
		void Loop();
		void DrawGame();
		void UpdatePhysics();
		void CheckCollitions();
		void DoEvents();
		void UpdateCamera();

		//Aux
		void SetZoom(Vector2f zoom);
		void UpdateCameraPos(b2Vec2 pos);
		float deg2rad(float deg);
		float rad2deg(float rad);
		
};

