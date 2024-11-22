#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Box2DHelper.h"

using namespace sf;

class Ragdoll {
	
public:

	Ragdoll(b2World *world, Vector2f pos, float angle);
	void Draw(RenderWindow& wnd);
	float deg2rad(float deg);

private:

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

};