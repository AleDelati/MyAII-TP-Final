#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "SFMLRenderer.h"

#include "LevelManager.h"
#include "UI_Manager.h"
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

		Vector2i mouse_Pos;
		Vector2f mouse_PosCoord;

		LevelManager *lvl_Manager;
		UI_Manager *ui_Manager;

		//					-| Box2D |-
		b2World* phyWorld;
		SFMLRenderer* debugRender;

		// Suelo, laterales y techo
		b2Body* borders[4];

		// Cañon
		b2Body* canon;
		b2Body* canonBase;

		// Ragdolls
		int rag_Count, rag_ReadyToDraw;
		bool rag_Instantiated[50];

		Ragdoll* rag_i[50];

		//					-| Texturas y Sprites |-

		Texture txt_UpDown_Edge, txt_SideEdge;
		Texture txt_canon, txt_canonBase;
		
		Sprite spr_UpDown_Edge[2], spr_Side_Edge[2];
		Sprite spr_canon, spr_canonBase;

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
		void CheckCollisions();
		void UpdateCanon();
		void DoEvents();
		void UpdateCamera();

		//Aux
		void SetUpSprite(b2Body *body, Texture &txt, Sprite &spr);
		void SetZoom(Vector2f zoom);
		void UpdateCameraPos(b2Vec2 pos);
		void ResetRagdolls();
		float deg2rad(float deg);
		float rad2deg(float rad);
		
};

