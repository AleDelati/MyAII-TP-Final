#include "Ragdoll.h"

Ragdoll::Ragdoll(b2World *world, Vector2f pos, float angle) {
	disabled = false;
	// Crea los componentes del ragdoll
	//Torso
	Torso = Box2DHelper::CreateRectangularDynamicBody(world, 1, 2, 1, 1, 0.25);
	Torso->SetTransform(b2Vec2(pos.x, pos.y), deg2rad(angle));

	//Cabeza
	Head = Box2DHelper::CreateRectangularDynamicBody(world, 0.5, 0.5, 0.5f, 1, 0.25);
	Head->SetTransform(Torso->GetWorldCenter() + b2Vec2(0, -1.35), Torso->GetAngle());
	
	//Brazo Izquierdo
	LeftArm = Box2DHelper::CreateRectangularDynamicBody(world, .5, 0.3, 0.5f, 1, 0.25);
	LeftArm->SetTransform(Torso->GetWorldCenter() + b2Vec2(-0.87, -0.83), Torso->GetAngle());

	LowLeftArm = Box2DHelper::CreateRectangularDynamicBody(world, .75, 0.3, 0.5f, 1, 0.25);
	LowLeftArm->SetTransform(Torso->GetWorldCenter() + b2Vec2(-1.6, -0.83), Torso->GetAngle());
	//Brazo Derecho
	RightArm = Box2DHelper::CreateRectangularDynamicBody(world, .5, 0.3, 1, 0.5f, 0.25);
	RightArm->SetTransform(Torso->GetWorldCenter() + b2Vec2(0.87, -0.83), Torso->GetAngle());

	LowRightArm = Box2DHelper::CreateRectangularDynamicBody(world, .75, 0.3, 1, 0.5f, 0.25);
	LowRightArm->SetTransform(Torso->GetWorldCenter() + b2Vec2(1.6, -0.83), Torso->GetAngle());
	//Pierna Izquierda
	LeftLeg = Box2DHelper::CreateRectangularDynamicBody(world, 0.4, 1.5, 1, 0.5f, 0.25);
	LeftLeg->SetTransform(Torso->GetWorldCenter() + b2Vec2(-0.3, 1.85), Torso->GetAngle() + deg2rad(0));

	LowLeftLeg = Box2DHelper::CreateRectangularDynamicBody(world, 0.4, 1.5, 1, 0.5f, 0.25);
	LowLeftLeg->SetTransform(Torso->GetWorldCenter() + b2Vec2(-0.3, 3.45), Torso->GetAngle() + deg2rad(0));
	//Pierna Derecha
	RightLeg = Box2DHelper::CreateRectangularDynamicBody(world, 0.4, 1.5, 1, 0.5f, 0.25);
	RightLeg->SetTransform(Torso->GetWorldCenter() + b2Vec2(0.3, 1.85), Torso->GetAngle() + deg2rad(0));

	LowRightLeg = Box2DHelper::CreateRectangularDynamicBody(world, 0.4, 1.5, 1, 0.5f, 0.25);
	LowRightLeg->SetTransform(Torso->GetWorldCenter() + b2Vec2(0.3, 3.45), Torso->GetAngle() + deg2rad(0));

	//Inicializa los Sprites
	InitSprites();

	//Crea los Joints entre las partes del ragdoll
	
	//Torso - Cabeza
		Box2DHelper::CreateDistanceJoint(world, Torso, Torso->GetWorldCenter() + (b2Vec2(0, -1.0f)), Head, Head->GetWorldCenter() + b2Vec2(0.f, .25f),
		1.0f, 1.0f, 1.0f);

	//Torzo - Brazo Izquierdo
	Box2DHelper::CreateDistanceJoint(world, Torso, Torso->GetWorldCenter() + (b2Vec2(-0.5, -1)), LeftArm,
		LeftArm->GetWorldCenter() + (b2Vec2(0.25, 0)), 1.0f, 1.0f, 1.0f);

	Box2DHelper::CreateDistanceJoint(world, LeftArm, LeftArm->GetWorldCenter() + (b2Vec2(-0.25, 0)), LowLeftArm,
		LowLeftArm->GetWorldCenter() + (b2Vec2(0.375, 0)), 1.0f, 1.0f, 1.0f);
	//Torso - Brazo Derecho
	Box2DHelper::CreateDistanceJoint(world, Torso, Torso->GetWorldCenter() + (b2Vec2(0.5, -1)), RightArm,
		RightArm->GetWorldCenter() + (b2Vec2(-0.25, 0)), 1.0f, 1.0f, 1.0f);

	Box2DHelper::CreateDistanceJoint(world, RightArm, RightArm->GetWorldCenter() + (b2Vec2(0.25, 0)), LowRightArm,
		LowRightArm->GetWorldCenter() + (b2Vec2(-0.375, 0)), 1.0f, 1.0f, 1.0f);

	//Torso - Pierna Izquierda
	Box2DHelper::CreateDistanceJoint(world, Torso, Torso->GetWorldCenter() + (b2Vec2(-0.3, 1)), LeftLeg,
		LeftLeg->GetWorldCenter() + (b2Vec2(0, -0.75)), 1.0f, 1.0f, 1.0f);

	Box2DHelper::CreateDistanceJoint(world, LeftLeg, LeftLeg->GetWorldCenter() + (b2Vec2(0, 0.75)), LowLeftLeg,
		LowLeftLeg->GetWorldCenter() + (b2Vec2(0, -0.75)), 1.0f, 1.0f, 1.0f);
	//Torso - Pierna Derecha
	Box2DHelper::CreateDistanceJoint(world, Torso, Torso->GetWorldCenter() + (b2Vec2(0.3, 1)), RightLeg,
		RightLeg->GetWorldCenter() + (b2Vec2(0, -0.75)), 1.0f, 1.0f, 1.0f);

	Box2DHelper::CreateDistanceJoint(world, RightLeg, RightLeg->GetWorldCenter() + (b2Vec2(0, 0.75)), LowRightLeg,
		LowRightLeg->GetWorldCenter() + (b2Vec2(0, -0.75)), 1.0f, 1.0f, 1.0f);
}

Ragdoll::~Ragdoll() {
	Torso->GetWorld()->DestroyBody(Torso);
	Head->GetWorld()->DestroyBody(Head);
	LeftArm->GetWorld()->DestroyBody(LeftArm);
	LowLeftArm->GetWorld()->DestroyBody(LowLeftArm);
	RightArm->GetWorld()->DestroyBody(RightArm);
	LowRightArm->GetWorld()->DestroyBody(LowRightArm);
	LeftLeg->GetWorld()->DestroyBody(LeftLeg);
	LowLeftLeg->GetWorld()->DestroyBody(LowLeftLeg);
	RightLeg->GetWorld()->DestroyBody(RightLeg);
	LowRightLeg->GetWorld()->DestroyBody(LowRightLeg);
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

	if (!disabled) {
		Spr_Torso.setPosition(Torso->GetPosition().x, Torso->GetPosition().y);
		Spr_Torso.setRotation(rad2deg(Torso->GetAngle()));
		wnd.draw(Spr_Torso);

		Spr_Head.setPosition(Head->GetPosition().x, Head->GetPosition().y);
		Spr_Head.setRotation(rad2deg(Head->GetAngle()));
		wnd.draw(Spr_Head);

		Spr_LeftArm.setPosition(LeftArm->GetPosition().x, LeftArm->GetPosition().y);
		Spr_LeftArm.setRotation(rad2deg(LeftArm->GetAngle()));
		wnd.draw(Spr_LeftArm);

		Spr_LowLeftArm.setPosition(LowLeftArm->GetPosition().x, LowLeftArm->GetPosition().y);
		Spr_LowLeftArm.setRotation(rad2deg(LowLeftArm->GetAngle()));
		wnd.draw(Spr_LowLeftArm);

		Spr_RightArm.setPosition(RightArm->GetPosition().x, RightArm->GetPosition().y);
		Spr_RightArm.setRotation(rad2deg(RightArm->GetAngle()));
		wnd.draw(Spr_RightArm);

		Spr_LowRightArm.setPosition(LowRightArm->GetPosition().x, LowRightArm->GetPosition().y);
		Spr_LowRightArm.setRotation(rad2deg(LowRightArm->GetAngle()));
		wnd.draw(Spr_LowRightArm);

		Spr_LeftLeg.setPosition(LeftLeg->GetPosition().x, LeftLeg->GetPosition().y);
		Spr_LeftLeg.setRotation(rad2deg(LeftLeg->GetAngle()));
		wnd.draw(Spr_LeftLeg);

		Spr_LowLeftLeg.setPosition(LowLeftLeg->GetPosition().x, LowLeftLeg->GetPosition().y);
		Spr_LowLeftLeg.setRotation(rad2deg(LowLeftLeg->GetAngle()));
		wnd.draw(Spr_LowLeftLeg);

		Spr_RightLeg.setPosition(RightLeg->GetPosition().x, RightLeg->GetPosition().y);
		Spr_RightLeg.setRotation(rad2deg(RightLeg->GetAngle()));
		wnd.draw(Spr_RightLeg);

		Spr_LowRightLeg.setPosition(LowRightLeg->GetPosition().x, LowRightLeg->GetPosition().y);
		Spr_LowRightLeg.setRotation(rad2deg(LowRightLeg->GetAngle()));
		wnd.draw(Spr_LowRightLeg);
	}
}

void Ragdoll::ApplyForce(Vector2f mouse_p) {
	Torso->ApplyForceToCenter(b2Vec2(mouse_p.x * 250, mouse_p.y * 250), false);
}

void Ragdoll::Disable() {
	disabled = true;

	//Torso
	Torso->SetTransform(b2Vec2(0, -200), 0);
	Torso->SetLinearVelocity(b2Vec2(0, 0));
	Torso->SetGravityScale(0);
	//Cabeza
	Head->SetTransform(Torso->GetWorldCenter() + b2Vec2(0, -1.35), Torso->GetAngle());
	Head->SetLinearVelocity(b2Vec2(0, 0));
	Head->SetGravityScale(0);
	//Brazo izquierdo
	LeftArm->SetTransform(Torso->GetWorldCenter() + b2Vec2(-0.87, -0.83), Torso->GetAngle());
	LeftArm->SetLinearVelocity(b2Vec2(0, 0));
	LeftArm->SetGravityScale(0);
	LowLeftArm->SetTransform(Torso->GetWorldCenter() + b2Vec2(-1.6, -0.83), Torso->GetAngle());
	LowLeftArm->SetLinearVelocity(b2Vec2(0, 0));
	LowLeftArm->SetGravityScale(0);
	//Brazo derecho
	RightArm->SetTransform(Torso->GetWorldCenter() + b2Vec2(0.87, -0.83), Torso->GetAngle());
	RightArm->SetLinearVelocity(b2Vec2(0, 0));
	RightArm->SetGravityScale(0);
	LowRightArm->SetTransform(Torso->GetWorldCenter() + b2Vec2(1.6, -0.83), Torso->GetAngle());
	LowRightArm->SetLinearVelocity(b2Vec2(0, 0));
	LowRightArm->SetGravityScale(0);
	//Pierna izquierda
	LeftLeg->SetTransform(Torso->GetWorldCenter() + b2Vec2(-0.3, 1.85), Torso->GetAngle() + deg2rad(0));
	LeftLeg->SetLinearVelocity(b2Vec2(0, 0));
	LeftLeg->SetGravityScale(0);
	LowLeftLeg->SetTransform(Torso->GetWorldCenter() + b2Vec2(-0.3, 3.45), Torso->GetAngle() + deg2rad(0));
	LowLeftLeg->SetLinearVelocity(b2Vec2(0, 0));
	LowLeftLeg->SetGravityScale(0);
	//Pierna derecha
	RightLeg->SetTransform(Torso->GetWorldCenter() + b2Vec2(0.3, 1.85), Torso->GetAngle() + deg2rad(0));
	RightLeg->SetLinearVelocity(b2Vec2(0, 0));
	RightLeg->SetGravityScale(0);
	LowRightLeg->SetTransform(Torso->GetWorldCenter() + b2Vec2(0.3, 3.45), Torso->GetAngle() + deg2rad(0));
	LowRightLeg->SetLinearVelocity(b2Vec2(0, 0));
	LowRightLeg->SetGravityScale(0);
}

void Ragdoll::Reset(Vector2f pos) {
	disabled = false;

	//Torso
	Torso->SetTransform(b2Vec2(pos.x, pos.y), 0);
	Torso->SetGravityScale(1);
	//Cabeza
	Head->SetTransform(Torso->GetWorldCenter() + b2Vec2(0, -1.35), Torso->GetAngle());
	Head->SetGravityScale(0);
	//Brazo izquierdo
	LeftArm->SetTransform(Torso->GetWorldCenter() + b2Vec2(-0.87, -0.83), Torso->GetAngle());
	LeftArm->SetGravityScale(0);
	LowLeftArm->SetTransform(Torso->GetWorldCenter() + b2Vec2(-1.6, -0.83), Torso->GetAngle());
	LowLeftArm->SetGravityScale(0);
	//Brazo derecho
	RightArm->SetTransform(Torso->GetWorldCenter() + b2Vec2(0.87, -0.83), Torso->GetAngle());
	RightArm->SetGravityScale(0);
	LowRightArm->SetTransform(Torso->GetWorldCenter() + b2Vec2(1.6, -0.83), Torso->GetAngle());
	LowRightArm->SetGravityScale(0);
	//Pierna izquierda
	LeftLeg->SetTransform(Torso->GetWorldCenter() + b2Vec2(-0.3, 1.85), Torso->GetAngle() + deg2rad(0));
	LeftLeg->SetGravityScale(0);
	LowLeftLeg->SetTransform(Torso->GetWorldCenter() + b2Vec2(-0.3, 3.45), Torso->GetAngle() + deg2rad(0));
	LowLeftLeg->SetGravityScale(0);
	//Pierna derecha
	RightLeg->SetTransform(Torso->GetWorldCenter() + b2Vec2(0.3, 1.85), Torso->GetAngle() + deg2rad(0));
	RightLeg->SetGravityScale(0);
	LowRightLeg->SetTransform(Torso->GetWorldCenter() + b2Vec2(0.3, 3.45), Torso->GetAngle() + deg2rad(0));
	LowRightLeg->SetGravityScale(0);
}

//					| AUX |

b2Vec2 Ragdoll::GetPosition() {
	return Torso->GetPosition();
}

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