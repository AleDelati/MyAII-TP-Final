#include "Actor.h"

Actor::Actor(b2Body* body, Sprite sprite) : bdy_actor(body), spr_actor(sprite) {

	position = bdy_actor->GetPosition();
	
	spr_actor.setOrigin(spr_actor.getTexture()->getSize().x / 2.0f, spr_actor.getTexture()->getSize().y / 2.0f);
	spr_actor.setPosition(position.x, position.y);
	spr_actor.setRotation(rad2deg(bdy_actor->GetAngle()));

	b2AABB dimension;
	dimension.upperBound = b2Vec2(-FLT_MAX, -FLT_MAX);
	dimension.lowerBound = b2Vec2(FLT_MAX, FLT_MAX);
	for (b2Fixture* f = bdy_actor->GetFixtureList(); f != NULL; f = f->GetNext()) {
		dimension = f->GetAABB(0);
	}

	spr_actor.setScale(dimension.GetExtents().x * 2 / spr_actor.getTexture()->getSize().y, dimension.GetExtents().y * 2 / spr_actor.getTexture()->getSize().y);


}

// Actualiza y Dibuja
void Actor::Draw(RenderWindow& wnd) {

	position = bdy_actor->GetPosition();
	spr_actor.setPosition(position.x, position.y);
	spr_actor.setRotation(rad2deg(bdy_actor->GetAngle()));

	wnd.draw(spr_actor);

}

float Actor::rad2deg(float rad) {
	return rad * 180 / 3.14f;
}