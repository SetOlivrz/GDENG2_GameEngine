#include "PhysicsComponent.h"
#include <iostream>
#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"
#include "AGameObject.h"
#include "Vector3D.h"

using namespace reactphysics3d;
PhysicsComponent::PhysicsComponent(String name, AGameObject* owner) : AComponent(name, AComponent::ComponentType::Physics, owner)
{
	//whenever a new physics component is initialized. Register to physics system
	BaseComponentSystem::getInstance()->getPhysicsSystem()->registerComponent(this);
	PhysicsCommon* physicsCommon = BaseComponentSystem::getInstance()->getPhysicsSystem()->getPhysicsCommon();
	PhysicsWorld* physicsWorld = BaseComponentSystem::getInstance()->getPhysicsSystem()->getPhysicsWorld();

	// Create a rigid body in the world
	Transform transform;

	//scale
	Vector3D scale = this->getOwner()->getLocalScale();
	//position
	Vector3D pos = this->getOwner()->getLocalPosition();
	transform.setPosition(Vector3(pos.m_x, pos.m_y, pos.m_z));
	//rotation
	Vector3D rot = this->getOwner()->getLocalRotation();
	transform.setOrientation(Quaternion::fromEulerAngles(Vector3(rot.m_x, rot.m_y, rot.m_z)));

	// create a boxshape
	BoxShape* boxShape = physicsCommon->createBoxShape(Vector3(scale.m_x , scale.m_y+3 , scale.m_z )); //half extent
	this->rigidBody = physicsWorld->createRigidBody(transform);
	this->rigidBody->addCollider(boxShape, transform);
	this->rigidBody->updateMassPropertiesFromColliders();
	this->rigidBody->setMass(this->mass);
	this->rigidBody->setType(BodyType::DYNAMIC);

	transform = this->rigidBody->getTransform();
	float matrix[16];
	//transform.getOpenGLMatrix(matrix);

	Vector3 new_pos = transform.getPosition();
	Quaternion new_rot = transform.getOrientation();

	this->getOwner()->setPosition(Vector3D(new_pos.x, new_pos.y, new_pos.z));
	this->getOwner()->setRotation(Vector3D(new_rot.x, new_rot.y, new_rot.z));
	this->getOwner()->attachComponent(this);
}

PhysicsComponent::~PhysicsComponent()
{
	AComponent::~AComponent();
	BaseComponentSystem::getInstance()->getPhysicsSystem()->unregisterComponent(this);
}

void PhysicsComponent::perform(float deltaTime)
{
	const Transform transform = this->rigidBody->getTransform();
	//float matrix[16];
	//transform.getOpenGLMatrix(matrix);

	Vector3 new_pos = transform.getPosition();
	Quaternion new_rot = transform.getOrientation();
	this->getOwner()->setRotation(Vector3D(new_rot.x, new_rot.y, new_rot.z));
	this->getOwner()->setPosition(Vector3D(new_pos.x, new_pos.y, new_pos.z));
}

RigidBody* PhysicsComponent::getRigidBody()
{
	return this->rigidBody;

}

void PhysicsComponent::setToStatic()
{
	this->rigidBody->setType(BodyType::STATIC);
}

void PhysicsComponent::setToKinematic()
{
	this->rigidBody->setType(BodyType::KINEMATIC);
}

void PhysicsComponent::setToDynamic()
{
	this->rigidBody->setType(BodyType::DYNAMIC);
}