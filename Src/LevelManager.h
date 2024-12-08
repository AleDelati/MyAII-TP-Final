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

	void lvl_0();
	void lvl_1();

	// Aux
	void SetUpSprite(b2Body *body, Texture &txt, Sprite &spr);
	void SetUpSprite(Texture &txt, Sprite &spr);
	float deg2rad(float deg);
	float rad2deg(float rad);

	void PlaceLine(b2Vec2 pos, int from, int lenght, String dir, String block_Type);

private:

	int current_lvl, last_lvl;
	float di_Blocks_GravSc;

	//
	b2World *world;
	b2Body *st_Blocks[100];
	b2Body *di_Blocks[25];

	// Texturas y Sprites
	Texture txt_st_Blocks;
	Texture txt_di_Blocks;
	Texture txt_lvl_Exit;

	Sprite spr_st_Blocks[100];
	Sprite spr_di_Blocks[25];
	Sprite spr_lvl_Exit;

};