#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Box2DHelper.h"

using namespace sf;

class Ragdoll {
	
public:

	Ragdoll(b2World *world, Vector2f pos, float angle);
	~Ragdoll();

	void InitSprites();
	void Draw(RenderWindow &wnd);
	void ApplyForce(Vector2f mouse_p);

	void Disable(Vector2f Pos);
	void Reset(Vector2f pos);

	// Aux
	b2Vec2 GetPosition();

	void SetUpSprite(b2Body *body, Sprite &spr);

	float deg2rad(float deg);
	float rad2deg(float rad);

private:
	bool disabled;

	b2Body* Torso;
	b2Body* Head;
	b2Body* LeftArm;
	b2Body* LowLeftArm;
	b2Body* RightArm;
	b2Body* LowRightArm;
	b2Body* LeftLeg;
	b2Body* LowLeftLeg;
	b2Body* RightLeg;
	b2Body* LowRightLeg;

	// Texturas y Sprites
	Texture txt_Rag;

	Sprite Spr_Torso;
	Sprite Spr_Head;
	Sprite Spr_LeftArm;
	Sprite Spr_LowLeftArm;
	Sprite Spr_RightArm;
	Sprite Spr_LowRightArm;
	Sprite Spr_LeftLeg;
	Sprite Spr_LowLeftLeg;
	Sprite Spr_RightLeg;
	Sprite Spr_LowRightLeg;

};