#include "AppWindow.h"
#include <Windows.h>
#include <iostream>
#include "Utils.h"
#include "InputSystem.h"


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
	Constant cc;

	Matrix4x4 world_cam;
	Matrix4x4 temp;;

	cc.worldMatrix.setIdentity();
	world_cam.setIdentity();

	temp.setIdentity();
	temp.setRotationX(cube[0]->getRotation().m_x);
	world_cam *= temp;

	temp.setIdentity();
	temp.setRotationY(cube[0]->getRotation().m_y);
	world_cam *= temp;

	temp.setTranslation(Vector3D(0,0,-2));


	//Vector3D new_pos = world_cam.getTranslation() + world_cam.getZDirection() * (m_forward * 0.1f);

	//new_pos = new_pos + world_cam.getXDirection() * (m_rightward * 0.1f);

	//world_cam.setTranslation(new_pos);

	//m_world_cam = world_cam;


	world_cam.inverse();




	cc.viewMatrix = world_cam;
	cc.projMatrix.setOrthoLH
	(
		(this->getClientWindowRect().right - this->getClientWindowRect().left)/300.0f,
		(this->getClientWindowRect().bottom - this->getClientWindowRect().top)/300.0f,
		-4.0f,
		4.0f
	);

	int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
	int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);


	//cc.projMatrix.setPerspectiveFovLH(1.57f, ((float)width / (float)height), 0.1f, 100.0f);


	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
}

void AppWindow::onCreate()
{
	Window::onCreate();
	InputSystem::get()->addListener(this);
	InputSystem::get()->showCursor(false);

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
	//update();
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

void AppWindow::onFocus()
{
	InputSystem::get()->addListener(this);
}

void AppWindow::onKillFocus()
{
	InputSystem::get()->removeListener(this);
}

void AppWindow::onKeyDown(int key)
{
	Vector3D v = cube[0]->getRotation();

	if (key == 'W')
	{
		//cube[0]->setRotation(Vector3D( v.m_x+ 3.14f * EngineTime::getDeltaTime(),v.m_y,v.m_z));
		cube[0]->m_forward = 1.0f;
	}
	else if (key == 'S')
	{
		//cube[0]->setRotation(Vector3D(v.m_x - 3.14f * EngineTime::getDeltaTime(), v.m_y, v.m_z));
		cube[0]->m_forward = -1.0f;

	}
	else if (key == 'A')
	{
		//cube[0]->setRotation(Vector3D(v.m_x, v.m_y + 3.14 *EngineTime::getDeltaTime(), v.m_z));
		cube[0]->m_rightward = -1.0f;

	}
	else if (key == 'D')
	{
		//cube[0]->setRotation(Vector3D(v.m_x, v.m_y - 3.14 * EngineTime::getDeltaTime(), v.m_z));
		cube[0]->m_rightward = 1.0f;

	}
}

void AppWindow::onKeyUp(int key)
{
	cube[0]->m_forward = 0.0f;
	cube[0]->m_rightward = 0.0f;


}
void AppWindow::onMouseMove(const Point& mouse_pos)
{
	int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
	int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);

	Vector3D v = cube[0]->getRotation();

	v.m_x += (mouse_pos.m_y - (height / 2.0f)) * EngineTime::getDeltaTime() * 0.1f;
	v.m_y += (mouse_pos.m_x - (width / 2.0f)) * EngineTime::getDeltaTime() * 0.1f;


	cube[0]->setRotation(v);

	InputSystem::get()->setCursorPosition(Point((int)(width / 2.0f), (int)(height / 2.0f)));

}

void AppWindow::onLeftMouseDown(const Point& mouse_pos)
{
	cube[0]->setScale(Vector3D(0.5, 0.5, 0.5));
}

void AppWindow::onLeftMouseUp(const Point& mouse_pos)
{
	cube[0]->setScale(Vector3D(1.0, 1.0, 1.0));

}

void AppWindow::onRightMouseDown(const Point& mouse_pos)
{
	cube[0]->setScale(Vector3D(2.0, 2.0, 2.0));

	//m_scale_cube = 2.0f;
}

void AppWindow::onRightMouseUp(const Point& mouse_pos)
{
	cube[0]->setScale(Vector3D(1.0, 1.0, 1.0));

	//m_scale_cube = 1.0f;
}