#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

using namespace sf;

class Actor {

public:
	
	Actor(b2Body* body, Sprite sprite);
	void Draw(RenderWindow& wnd);

	float rad2deg(float rad);

private:

	Sprite spr_actor;
	b2Body* bdy_actor;

	b2Vec2 position;

};