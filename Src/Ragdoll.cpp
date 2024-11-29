#include "Ragdoll.h"

Ragdoll::Ragdoll(b2World *world, Vector2f pos, float angle) {

	// Crea los componentes del ragdoll
	//Torso
	Torso = Box2DHelper::CreateRectangularDynamicBody(world, 1, 2, 10, 1, 0.25);
	Torso->SetTransform(b2Vec2(pos.x, pos.y), deg2rad(angle));
	//Torso->SetTransform(b2Vec2(pos.x, pos.y), 0);
	//Cabeza
	Head = Box2DHelper::CreateRectangularDynamicBody(world, 0.5, 0.5, 1, 1, 0.25);
	Head->SetTransform(Torso->GetWorldCenter() + b2Vec2(0, -1.35), Torso->GetAngle());
	//Brazo Izquierdo
	LeftArm = Box2DHelper::CreateRectangularDynamicBody(world, 1, 0.3, 1, 1, 0.25);
	LeftArm->SetTransform(Torso->GetWorldCenter() + b2Vec2(-0.75, -0.5), Torso->GetAngle() + deg2rad(90));

	LowLeftArm = Box2DHelper::CreateRectangularDynamicBody(world, 1, 0.3, 1, 1, 0.25);
	LowLeftArm->SetTransform(Torso->GetWorldCenter() + b2Vec2(-0.75, 0.58), Torso->GetAngle() + deg2rad(90));
	//Brazo Derecho
	RightArm = Box2DHelper::CreateRectangularDynamicBody(world, 1, 0.3, 1, 1, 0.25);
	RightArm->SetTransform(Torso->GetWorldCenter() + b2Vec2(0.75, -0.5), Torso->GetAngle() + deg2rad(90));

	LowRightArm = Box2DHelper::CreateRectangularDynamicBody(world, 1, 0.3, 1, 1, 0.25);
	LowRightArm->SetTransform(Torso->GetWorldCenter() + b2Vec2(0.75, 0.58), Torso->GetAngle() + deg2rad(90));
	//Pierna Izquierda
	LeftLeg = Box2DHelper::CreateRectangularDynamicBody(world, 0.4, 1.5, 1, 1, 0.25);
	LeftLeg->SetTransform(Torso->GetWorldCenter() + b2Vec2(-0.3, 1.85), Torso->GetAngle() + deg2rad(0));

	LowLeftLeg = Box2DHelper::CreateRectangularDynamicBody(world, 0.4, 1.5, 1, 1, 0.25);
	LowLeftLeg->SetTransform(Torso->GetWorldCenter() + b2Vec2(-0.3, 3.45), Torso->GetAngle() + deg2rad(0));
	//Pierna Derecha
	RightLeg = Box2DHelper::CreateRectangularDynamicBody(world, 0.4, 1.5, 1, 1, 0.25);
	RightLeg->SetTransform(Torso->GetWorldCenter() + b2Vec2(0.3, 1.85), Torso->GetAngle() + deg2rad(0));

	LowRightLeg = Box2DHelper::CreateRectangularDynamicBody(world, 0.4, 1.5, 1, 1, 0.25);
	LowRightLeg->SetTransform(Torso->GetWorldCenter() + b2Vec2(0.3, 3.45), Torso->GetAngle() + deg2rad(0));

	//Inicializa los Sprites
	InitSprites();

	//Crea los Joints entre las partes del ragdoll
	/*
	//Torso - Cabeza
	Box2DHelper::CreateDistanceJoint(world, Torso, Torso->GetWorldCenter() + (b2Vec2(0, -1)), Head, Head->GetWorldCenter(),
		0.5, 1, 1);
	
	//Torzo - Brazo Izquierdo
	Box2DHelper::CreateDistanceJoint(world, Torso, Torso->GetWorldCenter() + (b2Vec2(-0.5, -1)), LeftArm,
		LeftArm->GetWorldCenter() + (b2Vec2(0.5, 0)), 50, 1, 1);

	Box2DHelper::CreateDistanceJoint(world, LeftArm, LeftArm->GetWorldCenter() + (b2Vec2(-0.5, 0)), LowLeftArm,
		LowLeftArm->GetWorldCenter() + (b2Vec2(0.5, 0)), 50, 1, 1);
	//Torso - Brazo Derecho
	Box2DHelper::CreateDistanceJoint(world, Torso, Torso->GetWorldCenter() + (b2Vec2(5, -1)), RightArm,
		RightArm->GetWorldCenter() + (b2Vec2(-0.5, 0)), 50, 1, 1);

	Box2DHelper::CreateDistanceJoint(world, RightArm, RightArm->GetWorldCenter() + (b2Vec2(0.5, 0)), LowRightArm,
		LowRightArm->GetWorldCenter() + (b2Vec2(-0.5, 0)), 50, 1, 1);
	//Torso - Pierna Izquierda
	Box2DHelper::CreateDistanceJoint(world, Torso, Torso->GetWorldCenter() + (b2Vec2(-0.3, 1)), LeftLeg,
		LeftLeg->GetWorldCenter() + (b2Vec2(0, -0.75)), 50, 1, 1);

	Box2DHelper::CreateDistanceJoint(world, LeftLeg, LeftLeg->GetWorldCenter() + (b2Vec2(0, 0.75)), LowLeftLeg,
		LowLeftLeg->GetWorldCenter() + (b2Vec2(0, -0.75)), 50, 1, 1);
	//Torso - Pierna Derecha
	Box2DHelper::CreateDistanceJoint(world, Torso, Torso->GetWorldCenter() + (b2Vec2(0.3, 1)), RightLeg,
		RightLeg->GetWorldCenter() + (b2Vec2(0, -0.75)), 50, 1, 1);

	Box2DHelper::CreateDistanceJoint(world, RightLeg, RightLeg->GetWorldCenter() + (b2Vec2(0, 0.75)), LowRightLeg,
		LowRightLeg->GetWorldCenter() + (b2Vec2(0, -0.75)), 50, 1, 1);
		*/
}

void Ragdoll::InitSprites() {

	txt_Rag.loadFromFile("Sprites/Ragdoll.png");

	SetUpSprite(Torso, Spr_Torso);

	SetUpSprite(Head, Spr_Head);
	
	SetUpSprite(LeftArm, Spr_LeftArm);

	SetUpSprite(LowLeftArm, Spr_LowLeftArm);

	SetUpSprite(RightArm, Spr_RightArm);

	SetUpSprite(LowRightArm, Spr_LowRightArm);

	SetUpSprite(LeftArm, Spr_LeftArm);

	SetUpSprite(LowLeftArm, Spr_LowLeftArm);

	SetUpSprite(LeftLeg, Spr_LeftLeg);

	SetUpSprite(LowLeftLeg, Spr_LowLeftLeg);

	SetUpSprite(RightLeg, Spr_RightLeg);

	SetUpSprite(LowRightLeg, Spr_LowRightLeg);


}

void Ragdoll::Draw(RenderWindow& wnd) {

	Spr_Torso.setPosition(Torso->GetPosition().x, Torso->GetPosition().y);
	wnd.draw(Spr_Torso);

	Spr_Head.setPosition(Head->GetPosition().x, Head->GetPosition().y);
	wnd.draw(Spr_Head);

	Spr_LeftArm.setPosition(LeftArm->GetPosition().x, LeftArm->GetPosition().y);
	wnd.draw(Spr_LeftArm);

	Spr_LowLeftArm.setPosition(LowLeftArm->GetPosition().x, LowLeftArm->GetPosition().y);
	wnd.draw(Spr_LowLeftArm);

	Spr_RightArm.setPosition(RightArm->GetPosition().x, RightArm->GetPosition().y);
	wnd.draw(Spr_RightArm);

	Spr_LowRightArm.setPosition(LowRightArm->GetPosition().x, LowRightArm->GetPosition().y);
	wnd.draw(Spr_LowRightArm);

	Spr_LeftLeg.setPosition(LeftLeg->GetPosition().x, LeftLeg->GetPosition().y);
	wnd.draw(Spr_LeftLeg);

	Spr_LowLeftLeg.setPosition(LowLeftLeg->GetPosition().x, LowLeftLeg->GetPosition().y);
	wnd.draw(Spr_LowLeftLeg);

	Spr_RightLeg.setPosition(RightLeg->GetPosition().x, RightLeg->GetPosition().y);
	wnd.draw(Spr_RightLeg);

	Spr_LowRightLeg.setPosition(LowRightLeg->GetPosition().x, LowRightLeg->GetPosition().y);
	wnd.draw(Spr_LowRightLeg);

}

// Aux

void Ragdoll::SetUpSprite(b2Body* body, Sprite& spr) {

	spr.setTexture(txt_Rag);

	spr.setOrigin(txt_Rag.getSize().x / 2.0f, txt_Rag.getSize().y / 2.0f);
	spr.setPosition(body->GetPosition().x, body->GetPosition().y);
	//spr.setRotation(rad2deg(body->GetAngle()));

	b2AABB dimension;
	dimension.upperBound = b2Vec2(-FLT_MAX, -FLT_MAX);
	dimension.lowerBound = b2Vec2(FLT_MAX, FLT_MAX);
	for (b2Fixture* f = body->GetFixtureList(); f != NULL; f = f->GetNext()) {
		dimension = f->GetAABB(0);
	}
	
	spr.setScale(dimension.GetExtents().x * 2 / txt_Rag.getSize().x, dimension.GetExtents().y * 2 / txt_Rag.getSize().y);

}

float Ragdoll::deg2rad(float deg) {

	float pi = 3.14f;
	return deg * pi / 180;

}

float Ragdoll::rad2deg(float rad) {

	float pi = 3.14f;
	return rad / pi * 180;

}