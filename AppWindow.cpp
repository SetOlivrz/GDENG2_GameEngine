#include "AppWindow.h"
#include <Windows.h>
#include <iostream>
#include "Utils.h"
#include "InputSystem.h"


class GraphicsEngine;

AppWindow::AppWindow()
{
}


AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	Window::onCreate();
	InputSystem::get()->addListener(this);

	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);


	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;
	//for (int i = 0; i <100 ; i++)
	//{
	//	float x = Utils::randFloatInterval(-0.75, 0.75);
	//	float y = Utils::randFloatInterval(-0.75, 0.75);;


	//	Cube *cubeObj =  new Cube("Cube", shaderByteCode, sizeShader);
	//	cubeObj->setPosition(x,y, 0.0f);
	//	cubeObj->setAnimation(Utils::randFloatInterval(1.0, 3.0), Utils::randFloatInterval(2.0, 5.0), true );
	//	this->CubeList.push_back(cubeObj);
	//}

	Plane* planeObj = new Plane ("Plane", shaderByteCode, sizeShader);
	planeObj->setPosition(0.0, 0.0, 0.0f);
	planeObj->setAnimation(1, 20, true);
	plane[0] = planeObj;

	Cube* cubeObj = new Cube("Cube", shaderByteCode, sizeShader);
	cubeObj->setPosition(0.0, 0.0, 0.0f);
	cubeObj->setAnimation(1,20, true);
	cube[0] = cubeObj;




}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	InputSystem::get()->update();

	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0, 0.1f, 0.2f, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	/*for (int i = 0; i < CubeList.size(); i++)
	{
		CubeList[i]->update(EngineTime::getDeltaTime());
	}

	for (int i = 0; i < CubeList.size(); i++)
	{
		CubeList[i]->draw(rc.right - rc.left, rc.bottom - rc.top);
	}*/

	//plane[0]->update(EngineTime::getDeltaTime());
	cube[0]->update(EngineTime::getDeltaTime());

	//plane[0]->draw(rc.right - rc.left, rc.bottom - rc.top);
	cube[0]->draw(rc.right - rc.left, rc.bottom - rc.top);




	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();
	GraphicsEngine::get()->release();
}

void AppWindow::onKeyDown(int key)
{
	Vector3D v = cube[0]->getRotation();

	if (key == 'W')
	{
		cube[0]->setRotation(Vector3D( v.m_x+ 3.14f * EngineTime::getDeltaTime(),v.m_y,v.m_z));
	}
	else if (key == 'S')
	{
		cube[0]->setRotation(Vector3D(v.m_x - 3.14f * EngineTime::getDeltaTime(), v.m_y, v.m_z));
	}
	else if (key == 'A')
	{
		cube[0]->setRotation(Vector3D(v.m_x, v.m_y + 3.14 *EngineTime::getDeltaTime(), v.m_z));

	}
	else if (key == 'D')
	{
		cube[0]->setRotation(Vector3D(v.m_x, v.m_y - 3.14 * EngineTime::getDeltaTime(), v.m_z));
	}
}

void AppWindow::onKeyUp(int key)
{
}
