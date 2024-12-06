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
		int height, width, ragdollsCount;
		RenderWindow *wnd;
		Color clearColor;

		bool pause, toggleZoom;
		float fps, frameTime, time_2;
		Clock* clock_1;
		Time* time_1;

		View camera;

		Vector2i mouse_Pos;
		Vector2f mouse_PosCoord;

		//					-| Box2D |-

		b2World* phyWorld;
		SFMLRenderer* debugRender;

		// Suelo, laterales y techo
		b2Body* groundBody;
		b2Body* borders[3];

		// Cañon
		b2Body* canonWheel;
		b2Body* canonBase;
		b2Body* canon;

		// Ragdoll
		Ragdoll* rag_i[50];

		//					-| Texturas y Sprites |-

		Texture txt_ground;
		Texture txt_canon;
		
		Sprite spr_ground;
		Sprite spr_canon;

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
		void UpdateCanon();
		void DoEvents();
		void UpdateCamera();

		//Aux
		void SetUpSprite(b2Body* body, Texture& txt, Sprite& spr);
		void SetZoom(Vector2f zoom);
		void UpdateCameraPos(b2Vec2 pos);
		float deg2rad(float deg);
		float rad2deg(float rad);
		
};

