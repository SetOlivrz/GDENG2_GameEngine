#pragma once
#include "AComponent.h"
#include <reactphysics3d/reactphysics3d.h>
using namespace reactphysics3d;
class PhysicsComponent : public AComponent
{
public:
	PhysicsComponent(String name, AGameObject* owner);
	~PhysicsComponent();
	void perform(float deltaTime) override;

	RigidBody* getRigidBody();

	void setToStatic();

	void setToKinematic();

	void setToDynamic();

	void updateRigidBody();

private:
	float mass = 50.f; //in kilograms
	RigidBody* rigidBody;
};