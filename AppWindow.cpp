#include "AppWindow.h"
#include <Windows.h>
#include <iostream>
#include "Utils.h"
#include "InputSystem.h"
#include "SceneCameraHandler.h"


class GraphicsEngine;



_declspec(align(16)) //make CBData a size of 16-bytes.
struct Constant {
	Matrix4x4 worldMatrix;
	Matrix4x4 viewMatrix;
	Matrix4x4 projMatrix;
	//unsigned int m_time; //size of only 4 bytes. this won't align in GPU device because device requires 16 bytes.
	float m_time;
};

AppWindow::AppWindow()
{
}


AppWindow::~AppWindow()
{
}

void AppWindow::update()
{
	
}

void AppWindow::onCreate()
{
	Window::onCreate();

	InputSystem::initialize();
	SceneCameraHandler::initialize();

	InputSystem::getInstance()->addListener(this);
	//InputSystem::getInstance()->showCursor(false);

	// ENGINE
	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);


	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;
	/*for (int i = 0; i <15 ; i++)
	{
		if (i < 6)
		{
			float space = 0.34;
			Plane* card = new Plane("card", shaderByteCode, sizeShader);
			card->setPosition(i * space, 0, 0);
			card->setScale(0.7, 1, 0);
			if (i % 2 == 0)
			{
				card->setRotation(20, 90, 0);
			}
			else
			{
				card->setRotation(20, -90, 0);
			}
			this->CardList.push_back(card);

		}
		else if (i>= 6 && i <8)
		{
			
			float pos_offset = .34;
			Plane* card = new Plane("card", shaderByteCode, sizeShader);
			card->setPosition((i - 6) + pos_offset, 0.47, 0);
			card->setScale(0.7, 1, 0);
			card->setRotation(90, 90, 0);
			this->CardList.push_back(card);

		}
		else if (i >= 8 && i < 12)
		{
			float pos_offset = .34;
			float space = 0.34;
			Plane* card = new Plane("card", shaderByteCode, sizeShader);
			card->setPosition(((i-8) * space)+pos_offset , 0.94, 0);
			card->setScale(0.7, 1, 0);
			if (i % 2 == 0)
			{
				card->setRotation(20, 90, 0);
			}
			else
			{
				card->setRotation(20, -90, 0);
			}
			this->CardList.push_back(card);
		}
		else if (i == 12)
		{

			float pos_offset = 0.85;
			Plane* card = new Plane("card", shaderByteCode, sizeShader);
			card->setPosition((i - 12) + pos_offset, 1.41, 0);
			card->setScale(0.7, 1, 0);
			card->setRotation(90, 90, 0);
			this->CardList.push_back(card);
		}
		else
		{
			float pos_offset = 0.68;
			float space = 0.34;
			Plane* card = new Plane("card", shaderByteCode, sizeShader);
			card->setPosition(((i - 13) * space) + pos_offset, .94*2, 0);
			card->setScale(0.7, 1, 0);
			if (i % 2 == 1)
			{
				card->setRotation(20, 90, 0);
			}
			else
			{
				card->setRotation(20, -90, 0);
			}
			this->CardList.push_back(card);
		}
	}*/

	Plane* planeObj = new Plane ("Plane", shaderByteCode, sizeShader);
	planeObj->setPosition(0.0, 0.0, 0.0f);
	planeObj->setScale(10, 10, 0);
	planeObj->setRotation(90, 0, 0);


	planeObj->setAnimation(1, 20, true,1);
	plane[0] = planeObj;

	Cube* cubeObj = new Cube("Cube", shaderByteCode, sizeShader);
	cubeObj->setPosition(0.0, 0.9, 0.0f);
	cubeObj->setAnimation(1,20, false,1);
	CubeList.push_back(cubeObj);

	Cube* cubeObj1 = new Cube("Cube", shaderByteCode, sizeShader);
	cubeObj1->setPosition(-1.5, 2.0, 0.0f);
	cubeObj1->setAnimation(1, 20, false, 1);
	CubeList.push_back(cubeObj1);

	Cube* cubeObj2 = new Cube("Cube", shaderByteCode, sizeShader);
	cubeObj2->setPosition(-1.5, 3.0, -2.0f);
	cubeObj2->setAnimation(1, 20, false, 1);
	CubeList.push_back(cubeObj2);


}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	InputSystem::getInstance()->update();

	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0, 0.1f, 0.2f, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	//UPDATE CAMERA
	SceneCameraHandler::getInstance()->update();



	//UPDATE PRIMITIVES
	//for (int i = 0; i < CardList.size(); i++)
	//{
	//	CardList[i]->update(EngineTime::getDeltaTime());
	//}

	//for (int i = 0; i < CardList.size(); i++)
	//{
	//	CardList[i]->draw(rc.right - rc.left, rc.bottom - rc.top);
	//}

	for (int i = 0; i < CubeList.size(); i++)
	{
		CubeList[i]->update(EngineTime::getDeltaTime());
	}

	for (int i = 0; i < CubeList.size(); i++)
	{
		CubeList[i]->draw(rc.right - rc.left, rc.bottom - rc.top);
	}


	//cube[0]->update(EngineTime::getDeltaTime());
	//cube[0]->draw(rc.right - rc.left, rc.bottom - rc.top);

	plane[0]->update(EngineTime::getDeltaTime());
	plane[0]->draw(rc.right - rc.left, rc.bottom - rc.top);

	m_swap_chain->present(true);

}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();
	GraphicsEngine::get()->release();
}

void AppWindow::onFocus()
{
	//InputSystem::getInstance()->addListener(this);
}

void AppWindow::onKillFocus()
{
	//InputSystem::getInstance()->removeListener(this);
}

void AppWindow::onKeyDown(int key)
{
	//Vector3D v = cube[0]->getRotation();

	//if (key == 'H')
	//{
	//	Vector3D rot;
	//	float var = plane[0]->getLocalRotation().m_z + 30;
	//	plane[0]->setRotation(plane[0]->getLocalRotation().m_z, plane[0]->getLocalRotation().m_y, var);
	//	std::cout << "ROTz: " << plane[0]->getLocalRotation().m_z << " \n";


	//}
	//if (key == 'F') //x
	//{
	//	Vector3D rot;
	//	float var = plane[0]->getLocalRotation().m_x + 30;
	//	plane[0]->setRotation(var, plane[0]->getLocalRotation().m_y, plane[0]->getLocalRotation().m_z);
	//	std::cout << "ROTx: " << plane[0]->getLocalRotation().m_x << " \n";


	//}
	//if (key == 'G')//y
	//{
	//	Vector3D rot;
	//	float var = plane[0]->getLocalRotation().m_y + 30;
	//	plane[0]->setRotation(plane[0]->getLocalRotation().m_x, var, plane[0]->getLocalRotation().m_z);
	//	std::cout << "ROTy: " << plane[0]->getLocalRotation().m_y << " \n";


	//}
	//else if (key == 'S')
	//{
	//	//cube[0]->setRotation(Vector3D(v.m_x - 3.14f * EngineTime::getDeltaTime(), v.m_y, v.m_z));
	//	cube[0]->m_forward = -1.0f;

	//}
	//else if (key == 'A')
	//{
	//	//cube[0]->setRotation(Vector3D(v.m_x, v.m_y + 3.14 *EngineTime::getDeltaTime(), v.m_z));
	//	cube[0]->m_rightward = -1.0f;

	//}
	//else if (key == 'D')
	//{
	//	//cube[0]->setRotation(Vector3D(v.m_x, v.m_y - 3.14 * EngineTime::getDeltaTime(), v.m_z));
	//	cube[0]->m_rightward = 1.0f;

	//}
	
}

void AppWindow::onKeyUp(int key)
{
	/*cube[0]->m_forward = 0.0f;
	cube[0]->m_rightward = 0.0f;*/

}

void AppWindow::onMouseMove(const Point deltaPos)
{
	/*int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
	int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);

	Vector3D v = cube[0]->getRotation();

	v.m_x += (deltaPos.m_y - (height / 2.0f)) * EngineTime::getDeltaTime() * 0.1f;
	v.m_y += (deltaPos.m_x - (width / 2.0f)) * EngineTime::getDeltaTime() * 0.1f;


	cube[0]->setRotation(v);

	InputSystem::getInstance()->setCursorPosition(Point((int)(width / 2.0f), (int)(height / 2.0f)));*/

}

void AppWindow::onLeftMouseDown(const Point deltaPos)
{
	//cube[0]->setScale(Vector3D(0.5, 0.5, 0.5));
	//std::cout << "Left mosssssssssssssssssssssssssssssssssssssssuse down! \n";
	//plane[0]->setRotation(0.0, 0.0, plane[0]->getLocalRotation().m_z + EngineTime::getDeltaTime());

}

void AppWindow::onLeftMouseUp(const Point deltaPos)
{
	//cube[0]->setScale(Vector3D(1.0, 1.0, 1.0));
	std::cout << "Left mouse upward! \n";



}

void AppWindow::onRightMouseDown(const Point deltaPos)
{
	std::cout << "Right mouse down! \n";

	//cube[0]->setScale(Vector3D(2.0, 2.0, 2.0));

	//m_scale_cube = 2.0f;
}

void AppWindow::onRightMouseUp(const Point deltaPos)
{
	std::cout << "Right mouse upward! \n";

	//cube[0]->setScale(Vector3D(1.0, 1.0, 1.0));

	//m_scale_cube = 1.0f;
}