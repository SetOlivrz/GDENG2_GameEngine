#include "GameObjectManager.h"
#include "GraphicsEngine.h"
#include "UIManager.h"
#include "TexturedCube.h"
#include "Plane.h"
#include "PhysicsComponent.h"
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

void GameObjectManager::createCube()
{
	TexturedCube* cube = new TexturedCube("textured Cube", shaderByteCode, sizeShader);
	cube->myTexture = GraphicsEngine::getInstance()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\wood.jpg");

	cube->setPosition(1.0, 1.0, 1.0f);
	cube->setScale(3, 3, 3);
	cube->attachComponent(new PhysicsComponent("PhysicsComponent", cube));
	
	objList.push_back((cube));

}

void GameObjectManager::createCubes()
{
	for (size_t i = 0; i < 10; i++)
	{
		TexturedCube* cube = new TexturedCube("textured Cube", shaderByteCode, sizeShader);
		cube->myTexture = GraphicsEngine::getInstance()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\wood.jpg");
		cube->setPosition(1.0, 1.0, 1.0f);
		cube->setScale(2, 2, 2);
		cube->attachComponent(new PhysicsComponent("PhysicsComponent", cube));
		objList.push_back((cube));
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
