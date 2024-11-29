#include "Actor.h"

Actor::Actor(b2Body* body, RectangleShape* fig) : bdy_actor(body), fig_actor(fig) {

	position = body->GetPosition();
	
	dimensions.upperBound = b2Vec2(-FLT_MAX, -FLT_MAX);
	dimensions.lowerBound = b2Vec2(FLT_MAX, FLT_MAX);
	for (b2Fixture* f = bdy_actor->GetFixtureList(); f != NULL; f = f->GetNext()) {
		dimensions = f->GetAABB(0);
	}

	fig_actor->setOrigin(fig_actor->getSize().x / 2.0f, fig_actor->getSize().y / 2.0f);

	fig_actor->setSize({dimensions.GetExtents().x * 2, dimensions.GetExtents().y * 2});

	fig_actor->setPosition(position.x, position.y);

}

// Actualiza y Dibuja
void Actor::Draw(RenderWindow& wnd) {

	position = bdy_actor->GetPosition();
	fig_actor->setPosition(position.x, position.y);
	fig_actor->setRotation(rad2deg(bdy_actor->GetAngle()));

	wnd.draw(*fig_actor);

}

float Actor::rad2deg(float rad) {
	return rad * 180 / 3.14f;
}