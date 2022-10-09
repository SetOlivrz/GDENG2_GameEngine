#include "AppWindow.h"
#include <Windows.h>
#include <iostream>


struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
	vec3 position1;
	vec3 color;
	vec3 color1;
};


__declspec(align(16))
struct constant
{
	float m_angle;
};


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

	// Demo 1
	//vertex list[] =
	//{
	//	//X - Y - Z
	//	{-0.75f,-0.85f,0.0f,    -0.3f,-0.0f,0.0f,   0,0,0,  0,1,0 }, // POS1 LL
	//	{-0.85f,0.2f,0.0f,      -0.2f ,0.80f,0.0f,     1,1,0,  0,1,1 }, // POS2 UL
	//	{ 0.2f,-0.25f,0.0f,      0.75f,-0.80f,0.0f,   0,0,1,  1,0,0 },// POS2 LR
	//	{ 0.10f,0.25f,0.0f,      0.80f,0.80f,0.0f,    1,1,1,  0,0,1 } //UR
	//};


	// Demo 2
	vertex list[] =
	{
		//X - Y - Z
		{-0.80f,-0.85f,0.0f,    -0.35f,-0.15f,0.0f,   0,0,0,  0,1,0 }, // POS1 LL
		{-0.90f,0.2f,0.0f,      -0.1f ,0.75f,0.0f,     1,1,0,  0,1,1 }, // POS2 UL
		{ 1.0f,-0.4f,0.0f,      0.0f,-0.70f,0.0f,   0,0,1,  1,0,0 },// POS2 LR
		{ -0.75f,-0.85f,0.0f,      0.80f,0.75f,0.0f,    1,1,1,  0,0,1 } //UR
	};


	std:: cout << "Debug";

	m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(list);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();


	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();

	constant cc;
	cc.m_angle = 0;

	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));


	// Set ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init(Window::m_hwnd);
	ImGui_ImplDX11_Init(GraphicsEngine::get()->m_d3d_device, GraphicsEngine::get()->m_imm_context);
	ImGui::StyleColorsDark();
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

	

	m_angle += 0.1*EngineTime::getTimerValue();
	constant cc;
	cc.m_angle = m_angle;

	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);

	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);


	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	// FINALLY DRAW THE TRIANGLE
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);

	//Start Imgui Frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();

	//Create Imgui TEst Window
	ImGui::Begin("Test");
	ImGui::End();

	//Assemble Together Draw Data
	ImGui::Render();

	//Render Draw Data
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());


	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_vb->release();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();
	GraphicsEngine::get()->release();
}