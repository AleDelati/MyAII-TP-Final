#include "Ragdoll.h"

Ragdoll::Ragdoll(b2World *world, Vector2f pos, float angle) {

	// Crea los componentes del ragdoll
//Torso
	Torso = Box2DHelper::CreateRectangularDynamicBody(world, 1, 2, 10, 1, 0.25);
	Torso->SetTransform(b2Vec2(pos.x, pos.y), deg2rad(angle));
	//Torso->SetTransform(b2Vec2(pos.x, pos.y), 0);
	//Cabeza
	Head = Box2DHelper::CreateCircularDynamicBody(world, 0.5, 0.5, 1, 0.25);
	Head->SetTransform(Torso->GetWorldCenter() + b2Vec2(0, -1), Torso->GetAngle());
	//Brazo Izquierdo
	LeftArm = Box2DHelper::CreateRectangularDynamicBody(world, 1, 0.3, 1, 1, 0.25);
	LeftArm->SetTransform(Torso->GetWorldCenter() + b2Vec2(-0.75, -0.5), Torso->GetAngle() + deg2rad(90));

	LowLeftArm = Box2DHelper::CreateRectangularDynamicBody(world, 1, 0.3, 1, 1, 0.25);
	LowLeftArm->SetTransform(Torso->GetWorldCenter() + b2Vec2(-0.75, 0.5), Torso->GetAngle() + deg2rad(90));
	//Brazo Derecho
	RightArm = Box2DHelper::CreateRectangularDynamicBody(world, 1, 0.3, 1, 1, 0.25);
	RightArm->SetTransform(Torso->GetWorldCenter() + b2Vec2(0.75, -0.5), Torso->GetAngle() + deg2rad(90));

	LowRightArm = Box2DHelper::CreateRectangularDynamicBody(world, 1, 0.3, 1, 1, 0.25);
	LowRightArm->SetTransform(Torso->GetWorldCenter() + b2Vec2(0.75, 0.5), Torso->GetAngle() + deg2rad(90));
	//Pierna Izquierda
	LeftLeg = Box2DHelper::CreateRectangularDynamicBody(world, 0.4, 1.5, 1, 1, 0.25);
	LeftLeg->SetTransform(Torso->GetWorldCenter() + b2Vec2(-0.3, 1.5), Torso->GetAngle() + deg2rad(0));

	LowLeftLeg = Box2DHelper::CreateRectangularDynamicBody(world, 0.4, 1.5, 1, 1, 0.25);
	LowLeftLeg->SetTransform(Torso->GetWorldCenter() + b2Vec2(-0.3, 3), Torso->GetAngle() + deg2rad(0));
	//Pierna Derecha
	RightLeg = Box2DHelper::CreateRectangularDynamicBody(world, 0.4, 1.5, 1, 1, 0.25);
	RightLeg->SetTransform(Torso->GetWorldCenter() + b2Vec2(0.3, 1.5), Torso->GetAngle() + deg2rad(0));

	LowRightLeg = Box2DHelper::CreateRectangularDynamicBody(world, 0.4, 1.5, 1, 1, 0.25);
	LowRightLeg->SetTransform(Torso->GetWorldCenter() + b2Vec2(0.3, 3), Torso->GetAngle() + deg2rad(0));

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

void Ragdoll::Draw(RenderWindow& wnd) {



}

float Ragdoll::deg2rad(float deg) {

	float pi = 3.14f;
	return deg * pi / 180;

}