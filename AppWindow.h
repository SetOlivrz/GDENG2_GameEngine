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
#include "InputListener.h"
#include "Matrix4x4.h"

#include "Cube.h"
#include "Plane.h"
#include "Frustum.h"
#include "Gizmo.h"

#include <vector>

class GraphicsEngine;

class AppWindow : public Window, public InputListener
{

public:
	AppWindow();
	~AppWindow();

	void update();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;	

	virtual void onFocus() override;
	virtual void onKillFocus() override;

	
	// Inherited via InputListener
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	// Inherited via InputListener
	virtual void onMouseMove(const Point deltaPos) override;
	virtual void onLeftMouseDown(const Point deltaPos) override;
	virtual void onLeftMouseUp(const Point deltaPos) override;
	virtual void onRightMouseDown(const Point deltaPos) override;
	virtual void onRightMouseUp(const Point deltaPos) override;
private:
	SwapChain* m_swap_chain;
	VertexBuffer* m_vb;
	VertexShader* m_vs;
	PixelShader* m_ps;
	ConstantBuffer* m_cb;
	
	DebugWindow debugWindow;

	Cube* cube;
	Gizmo* cameraGizmo;

	Frustum* fustrum;


	std::vector<Cube*> CubeList;

	unsigned long m_old_time = 0;
	float m_delta_time = 0;
	float m_angle = 0;

	Camera* camObj;
	Camera* sceneCamera;
	bool isUsingCameraObj = false;


private:
	friend class GraphicsEngine;


	

};