#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "VertexClass.h"
#include "DebugWindow.h"
#include "Quad.h"
#include "Cube.h"
#include "Plane.h"

#include <vector>

class GraphicsEngine;

class AppWindow : public Window
{

public:
	AppWindow();
	~AppWindow();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
private:
	SwapChain* m_swap_chain;
	VertexBuffer* m_vb;
	VertexShader* m_vs;
	PixelShader* m_ps;
	ConstantBuffer* m_cb;
	
	DebugWindow debugWindow;

	Plane* plane[1];
	Cube* cube[1];


	std::vector<Cube*> CubeList;

	unsigned long m_old_time = 0;
	float m_delta_time = 0;
	float m_angle = 0;

private:
	friend class GraphicsEngine;
};