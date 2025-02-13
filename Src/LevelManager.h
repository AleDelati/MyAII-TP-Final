#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Box2DHelper.h"

using namespace sf;

class LevelManager {

public:

	LevelManager(b2World *wrld, int lvl);
	void InitBlocks();
	void InitSprites();

	void LoadLevel(int lvl);
	void ChangeLevel(int lvl);
	void ClearLevel();
	void NextLevel();
	void ResetLevel();
	void DrawLevel(RenderWindow &wnd);

	void lvl_0(); // Menu
	void lvl_1();
	void lvl_2();
	void lvl_3();
	void lvl_4();
	void lvl_5();
	void lvl_6();

	// Aux
	void SetUpSprite(b2Body *body, Texture &txt, Sprite &spr);
	FloatRect GetExitBounds();
	int GetCurrentLevel();
	float deg2rad(float deg);
	float rad2deg(float rad);

	void PlaceLine(b2Vec2 pos, int lenght, String dir, String block_Type);
	void PlaceBlock(b2Vec2 pos, String block_Type);

private:

	int current_lvl, last_lvl, next_st, next_di;
	float di_Blocks_GravSc = 2.0f;

	//
	b2World *world;
	b2Body *st_Blocks[100];
	b2Body *di_Blocks[25];
	b2DistanceJoint *d_joints[50];
	b2RevoluteJoint *r_joints[10];
	b2PrismaticJoint *p_joints[10];

	b2Body *platforms[10];

	// Texturas y Sprites
	Texture txt_st_Blocks;
	Texture txt_di_Blocks;
	Texture txt_platform;
	Texture txt_lvl_Exit;

	Sprite spr_st_Blocks[100];
	Sprite spr_di_Blocks[25];
	Sprite spr_platforms[10];
	Sprite spr_lvl_Exit;

};