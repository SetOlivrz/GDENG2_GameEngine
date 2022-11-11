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
	void createDisplayData();
	void TransformSliders(Quad* obj);
	void TransformSliders(Quad* obj1,Quad* obj2);

	void renderWindow();

private:
	friend class GraphicsEngine;

	bool obj1 = false;
	bool obj2 = false;

	float posFactor[3] = {};
	float scalFactor[3] = {};

	float sumA[3] = {};
	float sumB[3] = {};

	float sumC[3] = {};
	float sumD[3] = {};


	float multiScale = 1.0f;
	float scaleSum[3] = {};

	float tempPosA[3] = { 0,0,0 };
	float tempPosB[3] = { 0,0,0 };

	float tempScalA[3] = { 0,0,0 };
	float tempScalB[3] = { 0,0,0 };








};

