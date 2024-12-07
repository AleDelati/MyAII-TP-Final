#include "LevelManager.h"

LevelManager::LevelManager(b2World *wrld, int lvl) {
	world = wrld;
	current_lvl = lvl;
	last_lvl = 1;

	InitBlocks();
	InitSprites();
	
	ChangeLevel(lvl);
}

void LevelManager::InitBlocks() {
	// Inicializa los bloques estaticos
	for (int i = 0; i < 100; i++) {
		st_Blocks[i] = Box2DHelper::CreateRectangularStaticBody(world, 5, 5, 0.5f);
	}
	
	// Inicializa los bloques dinamicos
	for (int i = 0; i < 25; i++) {
		di_Blocks[i] = Box2DHelper::CreateRectangularDynamicBody(world, 5, 5, 0.05f, 1.0f, 0.25f);
		di_Blocks[i]->SetGravityScale(2);		// Para personalizar como afecta la gravedad a los bloques dinamicos
	}
}

void LevelManager::InitSprites() {
	txt_st_Blocks.loadFromFile("Sprites/lvl_Sprites/lvl_st_Block.png");
	for (int i = 0; i < 100; i++) { SetUpSprite(st_Blocks[i], txt_st_Blocks, spr_st_Blocks[i]); }

	txt_di_Blocks.loadFromFile("Sprites/lvl_Sprites/lvl_di_Block.png");
	for (int i = 0; i < 25; i++) { SetUpSprite(di_Blocks[i], txt_di_Blocks, spr_di_Blocks[i]); }
}

void LevelManager::LoadLevel(int lvl) {

	switch (lvl) {
	case 0:
		lvl_0();
		break;
	case 1:
		lvl_1();
		break;
	}

}

void LevelManager::ChangeLevel(int lvl) {
	ClearLevel();
	LoadLevel(lvl);
	current_lvl = lvl;
}

void LevelManager::ClearLevel() {
	//Bloques estaticos
	for (int i = 0; i < 100; i++) { st_Blocks[i]->SetTransform(b2Vec2(0, -50), 0); }

	//Bloques dinamicos
	for (int i = 0; i < 25; i++) {
		di_Blocks[i]->SetLinearVelocity(b2Vec2(0, 0));
		di_Blocks[i]->SetTransform(b2Vec2(0, -50), 0);
	}
}

void LevelManager::NextLevel() {
	if (current_lvl + 1 <= last_lvl) { ChangeLevel(current_lvl + 1); }
	else { ChangeLevel(0); }
}

void LevelManager::ResetLevel() {
	ChangeLevel(current_lvl);
}

void LevelManager::DrawLevel(RenderWindow &wnd) {
	// Dibuja los bloques estaticos
	for (int i = 0; i < 100; i++) {
		spr_st_Blocks[i].setPosition(st_Blocks[i]->GetPosition().x, st_Blocks[i]->GetPosition().y);
		spr_st_Blocks[i].setRotation(rad2deg(st_Blocks[i]->GetAngle()));
		wnd.draw(spr_st_Blocks[i]);
	}

	// Dibuja los bloques dinamicos
	for (int i = 0; i < 25; i++) {
		spr_di_Blocks[i].setPosition(di_Blocks[i]->GetPosition().x, di_Blocks[i]->GetPosition().y);
		spr_di_Blocks[i].setRotation(rad2deg(di_Blocks[i]->GetAngle()));
		wnd.draw(spr_di_Blocks[i]);
	}
}

//					| Levels |
void LevelManager::lvl_0() {
	
	//Bloques estaticos
	PlaceLine(b2Vec2(50, 92), 0, 7, "Up", "st");
	PlaceLine(b2Vec2(50, 32), 7, 6, "Up", "st");

	//Bloques dinamicos
	PlaceLine(b2Vec2(50, 57), 0, 5, "Up", "di");

}

void LevelManager::lvl_1() {

	//Bloques estaticos
	PlaceLine(b2Vec2(50, 92), 0, 19, "Up", "st");

}

//					| AUX |

void LevelManager::SetUpSprite(b2Body *body, Texture &txt, Sprite &spr) {

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

float LevelManager::deg2rad(float deg) {

	float pi = 3.14f;
	return deg * pi / 180;

}

float LevelManager::rad2deg(float rad) {

	float pi = 3.14f;
	return rad / pi * 180;

}

// Crea lineas de bloques para facilitar la construccion de niveles
void LevelManager::PlaceLine(b2Vec2 pos, int from, int lenght, String dir, String block_Type) {

	if (block_Type == "st" || block_Type == "St") {		//Bloques estaticos
		st_Blocks[from]->SetTransform(pos, 0);

		if (dir == "Up" || dir == "up") {
			for (int i = from + 1; i < from + lenght; i++) {
				st_Blocks[i]->SetTransform(st_Blocks[i - 1]->GetPosition() + b2Vec2(0, -5), 0);
			}
		}
		else if (dir == "Down" || dir == "down") {
			for (int i = from + 1; i < from + lenght; i++) {
				st_Blocks[i]->SetTransform(st_Blocks[i - 1]->GetPosition() + b2Vec2(0, 5), 0);
			}
		}
		else if (dir == "Left" || dir == "left") {
			for (int i = from + 1; i < from + lenght; i++) {
				st_Blocks[i]->SetTransform(st_Blocks[i - 1]->GetPosition() + b2Vec2(-5, 0), 0);
			}
		}
		else if (dir == "Right" || dir == "right") {
			for (int i = from + 1; i < from + lenght; i++) {
				st_Blocks[i]->SetTransform(st_Blocks[i - 1]->GetPosition() + b2Vec2(5, 0), 0);
			}
		}
	}
	else if (block_Type == "di" || block_Type == "Di") {	//Bloques dinamicos
		di_Blocks[from]->SetTransform(pos, 0);

		if (dir == "Up" || dir == "up") {
			for (int i = from + 1; i < from + lenght; i++) {
				di_Blocks[i]->SetTransform(di_Blocks[i - 1]->GetPosition() + b2Vec2(0, -5), 0);
			}
		}
		else if (dir == "Down" || dir == "down") {
			for (int i = from + 1; i < from + lenght; i++) {
				di_Blocks[i]->SetTransform(di_Blocks[i - 1]->GetPosition() + b2Vec2(0, 5), 0);
			}
		}
		else if (dir == "Left" || dir == "left") {
			for (int i = from + 1; i < from + lenght; i++) {
				di_Blocks[i]->SetTransform(di_Blocks[i - 1]->GetPosition() + b2Vec2(-5, 0), 0);
			}
		}
		else if (dir == "Right" || dir == "right") {
			for (int i = from + 1; i < from + lenght; i++) {
				di_Blocks[i]->SetTransform(di_Blocks[i - 1]->GetPosition() + b2Vec2(5, 0), 0);
			}
		}
	}

}