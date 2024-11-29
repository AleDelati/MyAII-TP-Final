#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

using namespace sf;

class Actor {

public:
	
	Actor(b2Body* body, RectangleShape* fig);
	void Draw(RenderWindow& wnd);

	float rad2deg(float rad);

private:

	b2Body* bdy_actor;
	RectangleShape* fig_actor;

	b2AABB dimensions;
	b2Vec2 position;

};