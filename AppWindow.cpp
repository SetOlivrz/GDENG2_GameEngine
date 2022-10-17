#include "AppWindow.h"
#include <Windows.h>
#include <iostream>

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
	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	VertexClass::vertex quad_list[] =
	{
		//X - Y - Z
		{Vector3D(-0.2f,-0.2f,0.0f),    Vector3D(-0.32f,-0.11f,0.0f),   Vector3D(0,0,0), Vector3D(0,1,0) }, // POS1
		{Vector3D(-0.2f,0.2f,0.0f),     Vector3D(-0.11f,0.78f,0.0f),   Vector3D(1,1,0), Vector3D(0,1,1) }, // POS2
		{ Vector3D(0.2f,-0.2f,0.0f),     Vector3D(0.75f,-0.73f,0.0f), Vector3D(0,0,1),  Vector3D(1,0,0) },// POS2
		{ Vector3D(0.2f,0.2f,0.0f),     Vector3D(0.88f,0.77f,0.0f),    Vector3D(1,1,1), Vector3D(0,0,1) }
	};

	VertexClass::vertex triangle_list[] =
	{
		//X - Y - Z
		{Vector3D(-0.7f,-0.2f,0.0f),    Vector3D(-0.32f,-0.11f,0.0f),   Vector3D(0,0,0), Vector3D(0,1,0) }, // POS1
		{Vector3D(-0.7f,0.2f,0.0f),     Vector3D(-0.11f,0.78f,0.0f),   Vector3D(1,1,0), Vector3D(0,1,1) }, // POS2
		{ Vector3D(0.7f,-0.2f,0.0f),     Vector3D(0.75f,-0.73f,0.0f), Vector3D(0,0,1),  Vector3D(1,0,0) },// POS2
	};

	//Debug Window
	debugWindow.intitialize(Window::m_hwnd);

	//quad
	quad.initialize(quad_list, nullptr, 0);
	quad.setScale(Vector3D(1, 1, 1));
	quad.setTranslation(Vector3D(0, 0, 0));

	// triangle
	triangle.initialize(triangle_list, nullptr, 0);
	triangle.setScale(Vector3D(1, 1, 1));
	triangle.setTranslation(Vector3D(0, 0, 0));

	objectList[0] = &quad;
	objectList[1] = &triangle;
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0.3f, 0.4f, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	// Primitives
	quad.update(this->getClientWindowRect());
	triangle.update(this->getClientWindowRect());

	quad.drawQuad();
	triangle.drawQuad();

	// Debug Window
	debugWindow.createDisplayData(objectList);
	debugWindow.renderWindow();

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	quad.release();
	triangle.release();
	m_swap_chain->release();
	GraphicsEngine::get()->release();
}