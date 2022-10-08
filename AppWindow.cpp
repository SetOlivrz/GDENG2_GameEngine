#include "AppWindow.h"


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

	VertexClass::vertex quadA_Vertices[] =
	{
		//RECTANGLE          RAINBOW
		//X - Y - Z          R-G-B
		{ -0.5f,0.1f, 0.0f,   1,0,0}, // LL
		{ -0.5f, 0.5f, 0.0f,    0,1,0}, // UL
		{ -0.1f,0.1f, 0.0f,   0,0,1},// LR
		{ -0.1f, 0.5f, 0.0f,    1,1,0} // UR
	};

	VertexClass::vertex quadB_vertices[] =
	{
		//X - Y - Z          R-G-B
		{ 0.1f, 0.1f,0.0f,   1,1,0}, // LL
		{ 0.1f, 0.5f,0.0f,   0,1,0}, // UL
		{ 0.5f, 0.1f,0.0f,   0,1,0},  // LR
		{ 0.5f, 0.5f,0.0f,   1,1,0}  // uR
	};

	VertexClass::vertex quadC_Vertices[] =
	{
		//X - Y - Z             R-G-B
		{ -0.5f, -0.5f, 0.0f,   1,0,0}, // LL
		{ -0.5f, -0.1f, 0.0f,   1,0,1}, // UL
		{ 0.5f, -0.5f, 0.0f,   1,0,0},// LR
		{ 0.5f, -0.1f, 0.0f,   1,0,1} // UR
	};


	quadA.initialize(quadA_Vertices, nullptr, 0);
	quadB.initialize(quadB_vertices, nullptr, 0);
	quadC.initialize(quadC_Vertices, nullptr, 0);
	
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

	// draw quads
	quadA.drawQuad();
	quadB.drawQuad();
	quadC.drawQuad();

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	// release quads
	quadA.release();
	quadB.release();
	quadC.release();
	m_swap_chain->release();
	GraphicsEngine::get()->release();
}