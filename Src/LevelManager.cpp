#include "LevelManager.h"

LevelManager::LevelManager(b2World *wrld, int lvl) {
	world = wrld;

	current_lvl = lvl;
	last_lvl = 5;

	di_Blocks_GravSc = 2.0f;

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
		di_Blocks[i]->SetGravityScale(di_Blocks_GravSc);		// Para personalizar como afecta la gravedad a los bloques dinamicos
	}

	// Inicializa las plataformas
	for (int i = 0; i < 10; i++) {
		platforms[i] = Box2DHelper::CreateRectangularDynamicBody(world, 13.5f, 5, 0.05f, 1.0f, 0.25f);
		platforms[i]->SetGravityScale(0);
	}
}

void LevelManager::InitSprites() {
	// Inicializa los sprites
	txt_st_Blocks.loadFromFile("Sprites/lvl_Sprites/lvl_st_Block.png");
	for (int i = 0; i < 100; i++) { SetUpSprite(st_Blocks[i], txt_st_Blocks, spr_st_Blocks[i]); }

	txt_di_Blocks.loadFromFile("Sprites/lvl_Sprites/lvl_di_Block.png");
	for (int i = 0; i < 25; i++) { SetUpSprite(di_Blocks[i], txt_di_Blocks, spr_di_Blocks[i]); }

	txt_lvl_Exit.loadFromFile("Sprites/lvl_Sprites/lvl_Exit.png");
	spr_lvl_Exit.setTexture(txt_lvl_Exit);
	spr_lvl_Exit.setOrigin(txt_lvl_Exit.getSize().x / 2, txt_lvl_Exit.getSize().y / 2);
	spr_lvl_Exit.setScale(Vector2f(.2997f, .2997f));

	txt_platform.loadFromFile("Sprites/lvl_Sprites/lvl_Platform.png");
	for (int i = 0; i < 10; i++){ SetUpSprite(platforms[i], txt_platform, spr_platforms[i]); }

}

void LevelManager::LoadLevel(int lvl) {

	switch (lvl) {
	case 0:
		lvl_0();
		break;
	case 1:
		lvl_1();
		break;
	case 2:
		lvl_2();
		break;
	case 3:
		lvl_3();
		break;
	case 4:
		lvl_4();
		break;
	case 5:
		lvl_5();
		break;
	}
	
}

void LevelManager::ChangeLevel(int lvl) {
	ClearLevel();
	LoadLevel(lvl);
	current_lvl = lvl;
}

void LevelManager::ClearLevel() {
	next_st = 0, next_di = 0;

	//Bloques estaticos
	for (int i = 0; i < 100; i++) { st_Blocks[i]->SetTransform(b2Vec2(25, -50), 0); }

	//Bloques dinamicos
	for (int i = 0; i < 25; i++) {
		di_Blocks[i]->SetGravityScale(0);
		di_Blocks[i]->SetLinearVelocity(b2Vec2(0, 0));
		di_Blocks[i]->SetTransform(b2Vec2(75, -50), 0);
	}

	//Plataformas
	for (int i = 0; i < 10; i++) {
		platforms[i]->SetGravityScale(0);
		platforms[i]->SetLinearVelocity(b2Vec2(0, 0));
		platforms[i]->SetTransform(b2Vec2(90, -50), 0);
	}

	// Destruye los joints creados en los niveles

	//Bloques estaticos
	for (int i = 0; i < 100; i++) {
		if (st_Blocks[i]->GetJointList() != nullptr) {
			world->DestroyJoint(st_Blocks[i]->GetJointList()->joint);
		}
	}

	//Bloques dinamicos
	for (int i = 0; i < 25; i++) {
		if (di_Blocks[i]->GetJointList() != nullptr) {
			world->DestroyJoint(di_Blocks[i]->GetJointList()->joint);
		}
	}

	//Plataformas
	for (int i = 0; i < 10; i++) {
		if (platforms[i]->GetJointList() != nullptr) {
			world->DestroyJoint(platforms[i]->GetJointList()->joint);
		}
	}

	//Salida
	spr_lvl_Exit.setPosition(Vector2f(0, -50));
}

void LevelManager::NextLevel() {
	if (current_lvl + 1 <= last_lvl) { ChangeLevel(current_lvl + 1); }
	else { ChangeLevel(0); }
}

void LevelManager::ResetLevel() {
	ChangeLevel(current_lvl);
}

void LevelManager::DrawLevel(RenderWindow &wnd) {

	// Dibuja la salida
	wnd.draw(spr_lvl_Exit);

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

	// Dibuja las plataformas
	for (int i = 0; i < 10; i++) {
		spr_platforms[i].setPosition(platforms[i]->GetPosition().x, platforms[i]->GetPosition().y);
		spr_platforms[i].setRotation(rad2deg(platforms[i]->GetAngle()));
		wnd.draw(spr_platforms[i]);
	}
}

//					| Levels |
void LevelManager::lvl_0() {
	
	//Bloques estaticos
	PlaceLine(b2Vec2(97, 51), 5, "Left", "st");

	//Salida
	spr_lvl_Exit.setPosition(Vector2f(87.5, 44));
	
}

void LevelManager::lvl_1() {

	//Bloques estaticos
	PlaceLine(b2Vec2(50, 92), 7, "Up", "st");
	PlaceLine(b2Vec2(50, 32), 6, "Up", "st");

	//Bloques dinamicos

	//Salida
	spr_lvl_Exit.setPosition(Vector2f(75, 90));
	
}

void LevelManager::lvl_2() {

	//Bloques estaticos
	PlaceLine(b2Vec2(50, 92), 7, "Up", "st");
	PlaceLine(b2Vec2(50, 32), 6, "Up", "st");

	//Bloques dinamicos
	PlaceLine(b2Vec2(50, 57), 5, "Up", "di");

	//Salida
	spr_lvl_Exit.setPosition(Vector2f(75, 90));

}

void LevelManager::lvl_3() {

	//Bloques estaticos
	PlaceLine(b2Vec2(25, 92), 4, "Up", "st");
	PlaceLine(b2Vec2(25, 52), 10, "Up", "st");
	PlaceLine(b2Vec2(75, 92), 14, "Up", "st");

	//Bloques dinamicos
	PlaceLine(b2Vec2(25, 72), 4, "Up", "di");
	PlaceLine(b2Vec2(75, 22), 4, "Up", "di");

	//Salida
	spr_lvl_Exit.setPosition(Vector2f(88.5, 90));

}

void LevelManager::lvl_4() {

	//Bloques estaticos
	PlaceLine(b2Vec2(62.9f, 73), 2, "Right", "st");
	PlaceLine(b2Vec2(97.0f, 73), 1, "Right", "st");
	PlaceLine(b2Vec2(62.9f, 73), 5, "Down", "st");

	//Bloques dinamicos
	PlaceLine(b2Vec2(72.9f, 73), 5, "Right", "di");

	//Joints
	d_joints[0] = Box2DHelper::CreateDistanceJoint(world, st_Blocks[1], st_Blocks[1]->GetWorldCenter() + b2Vec2(2.5f, 0), di_Blocks[0], di_Blocks[0]->GetWorldCenter() + b2Vec2(-2.5f, 0), 0.5f, 20, 0.75f);
	d_joints[6] = Box2DHelper::CreateDistanceJoint(world, di_Blocks[3], di_Blocks[3]->GetWorldCenter() + b2Vec2(2.5f, 0), st_Blocks[2], st_Blocks[2]->GetWorldCenter() + b2Vec2(-2.5f, 0), 0.5f, 20, 0.75f);
	for (int i = 0; i < 4; i++) {
		d_joints[i + 1] = Box2DHelper::CreateDistanceJoint(world, di_Blocks[i], di_Blocks[i]->GetWorldCenter() + b2Vec2(2.5f, 0), di_Blocks[i + 1], di_Blocks[i + 1]->GetWorldCenter() + b2Vec2(-2.5f, 0), 0.5f, 20, 0.75f);
	}
	
	//Salida
	spr_lvl_Exit.setPosition(Vector2f(81.0f, 90));

}

void LevelManager::lvl_5() {

	//Left Side
	PlaceLine(b2Vec2(40, 30), 3, "Left", "St");
	PlaceLine(b2Vec2(30, 35), 4, "Down", "St");
	PlaceLine(b2Vec2(40, 65), 7, "Down", "St");
	PlaceLine(b2Vec2(25, 50), 10, "Down", "St");

	//Right Side
	PlaceLine(b2Vec2(60, 30), 3, "Right", "St");
	PlaceLine(b2Vec2(70, 35), 4, "Down", "St");
	PlaceLine(b2Vec2(60, 65), 7, "Down", "St");
	PlaceLine(b2Vec2(75, 50), 10, "Down", "St");

	PlaceBlock(b2Vec2(50, 50), "St");

	platforms[0]->SetTransform(b2Vec2(50, 30), 0);
	r_joints[0] = Box2DHelper::CreateRevoluteJoint(world, st_Blocks[0], b2Vec2(50, 30), platforms[0], deg2rad(-60), deg2rad(60), 1, 10, false, true);

	platforms[1]->SetTransform(b2Vec2(40, 50), 0);
	r_joints[1] = Box2DHelper::CreateRevoluteJoint(world, st_Blocks[0], b2Vec2(40, 50), platforms[1], deg2rad(0), deg2rad(0), -3, 1000, true, false);

	platforms[2]->SetTransform(b2Vec2(60, 50), 0);
	r_joints[2] = Box2DHelper::CreateRevoluteJoint(world, st_Blocks[0], b2Vec2(60, 50), platforms[2], deg2rad(0), deg2rad(0), 3, 1000, true, false);

	//Salida
	spr_lvl_Exit.setPosition(Vector2f(50.0f, 90));
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

FloatRect LevelManager::GetExitBounds() {
	return spr_lvl_Exit.getGlobalBounds();
}

int LevelManager::GetCurrentLevel() {
	return current_lvl;
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
void LevelManager::PlaceLine(b2Vec2 pos, int lenght, String dir, String block_Type) {
	
	while (st_Blocks[next_st]->GetPosition().y > 0 && st_Blocks[next_st]->GetPosition().y < 100) {
		next_st++;
	}

	while (di_Blocks[next_di]->GetGravityScale() != 0) {
		next_di++;
	}

	if (block_Type == "st" || block_Type == "St") {		//Bloques estaticos
		st_Blocks[next_st]->SetTransform(pos, 0);

		if (dir == "Up" || dir == "up") {
			for (int i = next_st + 1; i < next_st + lenght; i++) {
				st_Blocks[i]->SetTransform(st_Blocks[i - 1]->GetPosition() + b2Vec2(0, -5), 0);
			}
		}
		else if (dir == "Down" || dir == "down") {
			for (int i = next_st + 1; i < next_st + lenght; i++) {
				st_Blocks[i]->SetTransform(st_Blocks[i - 1]->GetPosition() + b2Vec2(0, 5), 0);
			}
		}
		else if (dir == "Left" || dir == "left") {
			for (int i = next_st + 1; i < next_st + lenght; i++) {
				st_Blocks[i]->SetTransform(st_Blocks[i - 1]->GetPosition() + b2Vec2(-5, 0), 0);
			}
		}
		else if (dir == "Right" || dir == "right") {
			for (int i = next_st + 1; i < next_st + lenght; i++) {
				st_Blocks[i]->SetTransform(st_Blocks[i - 1]->GetPosition() + b2Vec2(5, 0), 0);
			}
		}
	}
	else if (block_Type == "di" || block_Type == "Di") {	//Bloques dinamicos
		di_Blocks[next_di]->SetTransform(pos, 0);
		for (int i = next_di; i < next_di + lenght; i++) { di_Blocks[i]->SetGravityScale(di_Blocks_GravSc); }

		if (dir == "Up" || dir == "up") {
			for (int i = next_di + 1; i < next_di + lenght; i++) {
				di_Blocks[i]->SetTransform(di_Blocks[i - 1]->GetPosition() + b2Vec2(0, -5), 0);
			}
		}
		else if (dir == "Down" || dir == "down") {
			for (int i = next_di + 1; i < next_di + lenght; i++) {
				di_Blocks[i]->SetTransform(di_Blocks[i - 1]->GetPosition() + b2Vec2(0, 5), 0);
			}
		}
		else if (dir == "Left" || dir == "left") {
			for (int i = next_di + 1; i < next_di + lenght; i++) {
				di_Blocks[i]->SetTransform(di_Blocks[i - 1]->GetPosition() + b2Vec2(-5, 0), 0);
			}
		}
		else if (dir == "Right" || dir == "right") {
			for (int i = next_di + 1; i < next_di + lenght; i++) {
				di_Blocks[i]->SetTransform(di_Blocks[i - 1]->GetPosition() + b2Vec2(5, 0), 0);
			}
		}
	}
}


void LevelManager::PlaceBlock(b2Vec2 Pos, String block_Type) {

	while (st_Blocks[next_st]->GetPosition().y > 0 && st_Blocks[next_st]->GetPosition().y < 100) {
		next_st++;
	}

	while (di_Blocks[next_di]->GetGravityScale() != 0) {
		next_di++;
	}

	if (block_Type == "st" || block_Type == "St") {
		st_Blocks[next_st]->SetTransform(Pos, 0);
	}
	else if (block_Type == "di" || block_Type == "Di") {
		di_Blocks[next_di]->SetTransform(Pos, 0);
	}

}