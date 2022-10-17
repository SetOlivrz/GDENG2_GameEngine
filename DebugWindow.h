#pragma once

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "GraphicsEngine.h"
#include "Quad.h"
class DebugWindow
{
public: 
	DebugWindow();
	~DebugWindow();

	void intitialize(HWND hwnd);
	void createDisplayData(Quad* quad[]);
	void TransformSliders(Quad* obj);
	void TransformSliders(Quad* obj1,Quad* obj2);
	void resetVariables();


	void renderWindow();

private:
	friend class GraphicsEngine;

	bool obj1 = false;
	bool obj2 = false;

	Vector3D posFactor;
	Vector3D scalFactor;
	Vector3D sum[4];
	Vector3D tempPos[2];
	Vector3D tempScal[2];
};

