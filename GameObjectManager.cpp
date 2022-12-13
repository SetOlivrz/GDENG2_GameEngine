#include "GameObjectManager.h"
#include "GraphicsEngine.h"
#include "UIManager.h"
#include "TexturedCube.h"
#include "Plane.h"
#include "PhysicsComponent.h"
#include "Sphere.h"
#include "Capsule.h"
#include <iostream>

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}

void GameObjectManager::initialize()
{
	width = UIManager::WINDOW_WIDTH;
	height = UIManager::WINDOW_HEIGHT;
}

void GameObjectManager::createPhysicsCube()
{
	Cube* cube = new Cube("PhysicsCube", shaderByteCode, sizeShader);
	//cube->myTexture = GraphicsEngine::getInstance()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\wood.jpg");
	objList.push_back((cube));

	cube->attachComponent(new PhysicsComponent("PhysicsComponent", cube));
	cube->hasRigidBody = true;
	cube->rbType = "Dynamic";
}

void GameObjectManager::createCube()
{
	Cube* cube = new Cube("Cube", shaderByteCode, sizeShader);
	//cube->myTexture = GraphicsEngine::getInstance()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\wood.jpg");
	objList.push_back((cube));
}

void GameObjectManager::createCube(string name, string hasRigid, string rbType, Vector3D position, Vector3D scale, Vector3D rotation)
{
	Cube* cube = new Cube(name, shaderByteCode, sizeShader);
	cube->setPosition(position);
	cube->setScale(scale);
	cube->setRotation(rotation);
	objList.push_back((cube));

	PhysicsComponent* physicsComp = new PhysicsComponent("PhysicsComponent", cube);
	
	if (rbType == "Static")
	{
		physicsComp->setToStatic();
	}
	else if (rbType == "Dynamic")
	{
		physicsComp->setToDynamic();

	}
	else if (rbType == "Kinematic")
	{
		physicsComp->setToKinematic();
	}
	else 
	{
		cout << "rbtype not found \n";
	}

	cube->attachComponent(new PhysicsComponent("PhysicsComponent", cube));

	if (hasRigid == "1")
	{
		cube->hasRigidBody = true;
	}
	else
	{
		cube->hasRigidBody = false;
	}
	cube->rbType = rbType;
}

void GameObjectManager::createPlane(string name, string hasRigid, string rbType, Vector3D position, Vector3D scale, Vector3D rotation)
{
	Plane* plane = new Plane(name, shaderByteCode, sizeShader);
	plane->setPosition(position);
	plane->setScale(scale);
	plane->setRotation(rotation);
	objList.push_back((plane));

	PhysicsComponent* physicsComp = new PhysicsComponent("PhysicsComponent", plane);

	if (rbType == "Static")
	{
		physicsComp->setToStatic();
	}
	else if (rbType == "Dynamic")
	{
		physicsComp->setToDynamic();

	}
	else if (rbType == "Kinematic")
	{
		physicsComp->setToKinematic();
	}
	else
	{
		cout << "rbtype not found \n";
	}

	plane->attachComponent(new PhysicsComponent("PhysicsComponent", plane));

	if (hasRigid == "1")
	{
		plane->hasRigidBody = true;
	}
	else
	{
		plane->hasRigidBody = false;
	}
	plane->rbType = rbType;
}

void GameObjectManager::createSphere(string name, string hasRigid, string rbType, Vector3D position, Vector3D scale, Vector3D rotation)
{
	Sphere* sphere = new Sphere(name, shaderByteCode, sizeShader);
	sphere->setPosition(position);
	sphere->setScale(scale);
	sphere->setRotation(rotation);
	objList.push_back((sphere));

	PhysicsComponent* physicsComp = new PhysicsComponent("PhysicsComponent", sphere);

	if (rbType == "Static")
	{
		physicsComp->setToStatic();
	}
	else if (rbType == "Dynamic")
	{
		physicsComp->setToDynamic();

	}
	else if (rbType == "Kinematic")
	{
		physicsComp->setToKinematic();
	}
	else
	{
		cout << "rbtype not found \n";
	}

	sphere->attachComponent(new PhysicsComponent("PhysicsComponent", sphere));

	if (hasRigid == "1")
	{
		sphere->hasRigidBody = true;
	}
	else
	{
		sphere->hasRigidBody = false;
	}
	sphere->rbType = rbType;
}

void GameObjectManager::createCapsule(string name, string hasRigid, string rbType, Vector3D position, Vector3D scale, Vector3D rotation)
{
	Capsule* capsule = new Capsule(name, shaderByteCode, sizeShader);
	capsule->setPosition(position);
	capsule->setScale(scale);
	capsule->setRotation(rotation);
	objList.push_back((capsule));

	PhysicsComponent* physicsComp = new PhysicsComponent("PhysicsComponent", capsule);

	if (rbType == "Static")
	{
		physicsComp->setToStatic();
	}
	else if (rbType == "Dynamic")
	{
		physicsComp->setToDynamic();

	}
	else if (rbType == "Kinematic")
	{
		physicsComp->setToKinematic();
	}
	else
	{
		cout << "rbtype not found \n";
	}

	capsule->attachComponent(new PhysicsComponent("PhysicsComponent", capsule));

	if (hasRigid == "1")
	{
		capsule->hasRigidBody = true;
	}
	else
	{
		capsule->hasRigidBody = false;
	}
	capsule->rbType = rbType;
}


void GameObjectManager::createPhysicsSphere()
{
	Sphere* sphere = new Sphere("PhysicsSphere", shaderByteCode, sizeShader);
	//cube->myTexture = GraphicsEngine::getInstance()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\wood.jpg");
	objList.push_back((sphere));

	sphere->attachComponent(new PhysicsComponent("PhysicsComponent", sphere));
	sphere->hasRigidBody = true;
	sphere->rbType = "Dynamic";
}

void GameObjectManager::createPhysicsCapsule()
{
	Capsule* capsule = new Capsule ("PhysicsCapsule", shaderByteCode, sizeShader);
	//cube->myTexture = GraphicsEngine::getInstance()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\wood.jpg");
	objList.push_back((capsule));

	capsule->attachComponent(new PhysicsComponent("PhysicsComponent", capsule));
	capsule->hasRigidBody = true;
	capsule->rbType = "Dynamic";
}


void GameObjectManager::createPhysicsCubes()
{
	for (size_t i = 0; i < 10; i++)
	{
		Cube* cube = new Cube("texturedCube", shaderByteCode, sizeShader);
		//cube->myTexture = GraphicsEngine::getInstance()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\wood.jpg");

		cube->attachComponent(new PhysicsComponent("PhysicsComponent", cube));
		objList.push_back((cube));
		cube->hasRigidBody = true;
		cube->rbType = "Dynamic";
	}
}

void GameObjectManager::createPlane()
{
	Plane* plane = new Plane("Plane", shaderByteCode, sizeShader);
	plane->setPosition(1.0, -5.0, 1.0f);
	plane->setScale(50, 1, 50);

	PhysicsComponent* physicsComp = new PhysicsComponent("PhysicsComponent", plane);
	physicsComp->setToStatic();
	plane->attachComponent(physicsComp);
	objList.push_back((plane));
	plane->hasRigidBody = true;
	plane->rbType = "Static";

}
void GameObjectManager::changePosition(int i, float x, float y, float z)
{

}


void GameObjectManager::mergeSelected()
{
	
}

void GameObjectManager::instantiateMergedActor(int i)
{

}

void GameObjectManager::enableBox(int index, bool isEnable)
{
}

void GameObjectManager::changeBoxScale(int i, float x, float y, float z)
{
}

void GameObjectManager::initalizePlayerStart()
{

}

void GameObjectManager::updateObjects()
{
	//Draw Selected Objects
	for (int i = 0; i < objList.size(); i++)
	{
			objList[i]->draw(width, height);
	}
}

GameObjectManager* GameObjectManager::get()
{
	static GameObjectManager gOManager;
	return &gOManager;
}

vector<AGameObject*> GameObjectManager::getAllObjects()
{
	return this->objList;
}

void GameObjectManager::selectObject(AGameObject* obj)
{
	if (this->selectedObject != nullptr)
	{
		//	RESET PREV SELECTED OBJECT
		obj->isSelected = false;
	}

	obj->isSelected = true;
	this->selectedObject = obj;
}

void GameObjectManager::createObjectFromFile(string name, string type, string hasRigid, string rbType, Vector3D position, Vector3D scale, Vector3D rotation)
{
	if (type == "Cube") {
		createCube(name, hasRigid, rbType, position, scale, rotation);
	}
	else if (type == "Plane")
	{
		createPlane(name, hasRigid, rbType, position, scale, rotation);

	}
	else if (type == "Sphere")
	{
		createSphere(name, hasRigid, rbType, position, scale, rotation);

	}
	else if (type == "Capsule")
	{
		createCapsule(name, hasRigid, rbType, position, scale, rotation);

	}
	else
	{
		cout << "TYPE NOT FOUND";
	}
}

