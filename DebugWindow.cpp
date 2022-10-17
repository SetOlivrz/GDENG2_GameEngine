#include "DebugWindow.h"
#include <iostream>
#include <cstdlib>
#include "Utils.h"


DebugWindow::DebugWindow()
{
	
}

DebugWindow::~DebugWindow()
{
}

void DebugWindow::intitialize(HWND hwnd)
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	// Setup Platform/Renderer bindings
	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(GraphicsEngine::get()->m_d3d_device, GraphicsEngine::get()->m_imm_context);
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
}

void DebugWindow::createDisplayData(Quad* objList[] )
{
	// feed inputs to dear imgui, start new frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	//Create Imgui  Window
	ImGui::Begin("Debug Window");

	// check boxes
	ImGui::Text("Objects:");
	ImGui::Checkbox("Quad", &obj1);
	ImGui::Checkbox("Triangle", &obj2);

	if (obj1 && !obj2) // control for obj 1
	{
		TransformSliders(objList[0]);
	}
	else if (obj2 && !obj1) // control for obj 2
	{
		TransformSliders(objList[1]);

	}
	else if (obj1 && obj2) // control for both obj
	{
		TransformSliders(objList[0], objList[1]);
	}
	else
	{
	    ImGui::Text("	\n\nNOTE: PLEASE SELECT A SINGLE OBJECT");
	}


	ImGui::End();

	//Assemble Together Draw Data
	ImGui::Render();
}

void DebugWindow::TransformSliders(Quad* obj)
{
	resetVariables();

	// TRANSLATION
	float translateFactor[2];
	translateFactor[0] = obj->getTranslation().m_x;
	translateFactor[1] = obj->getTranslation().m_y;

	ImGui::Text("");
	ImGui::Text("	  X		    Y");
	ImGui::SliderFloat2(" Position", translateFactor, -1.0, 1.0);

	obj->setTranslation(Vector3D(translateFactor[0], translateFactor[1], 0.0f));

	if (ImGui::Button("Reset###Position"))
	{
		obj->resetPosition();
	}

	// SCALING
	float scaleFactor[2];
	scaleFactor[0] = obj->getScale().m_x;
	scaleFactor[1] = obj->getScale().m_y;
	ImGui::SliderFloat2(" Scale", scaleFactor, 0.0, 2);

	obj->setScale(Vector3D(scaleFactor[0], scaleFactor[1], 0.0f));

	if (ImGui::Button("Reset###Scale"))
	{
		obj->resetScale();
	}
}

void DebugWindow::TransformSliders(Quad* quad, Quad* tri)
{
	float posF[2];
	posF[0] = posFactor.m_x;
	posF[1] = posFactor.m_y;

	ImGui::Text("");
	ImGui::Text("	  X		    Y");
	ImGui::SliderFloat2(" Position", posF, -1.0, 1.0);

	posFactor = Vector3D(posF[0], posF[1], 0);

	 //MULTIPLE TRANSLATION
	 //copy if not equal (has changes) 
	if (!sum[0].isEqual(quad->getTranslation()))
	{
		tempPos[0] = quad->getTranslation();
	}

	if (!sum[1].isEqual(tri->getTranslation()))
	{
		tempPos[1] = tri->getTranslation();
	}
	// add slider factor to temp
	 sum[0] = posFactor + tempPos[0];
	 sum[1] = posFactor + tempPos[1];

	// equate sum to actual translate
	quad->setTranslation(sum[0]);
	tri->setTranslation(sum[1]);


	// MULTIPLE SCALING
	float scalF[2];
	scalF[0] = scalFactor.m_x;
	scalF[1] = scalFactor.m_y;

	ImGui::Text("");
	ImGui::Text("	  X		    Y");
	ImGui::SliderFloat2(" Scale", scalF, 0.0, 2.0);

	scalFactor = Vector3D(scalF[0], scalF[1], 0);

	// copy if not equal (has changes) 
	if (!sum[2].isEqual(quad->getScale()))
	{
		tempScal[0] = quad->getScale();
	}

	if (!sum[3].isEqual(tri->getScale()))
	{
		tempScal[1]= tri->getScale();
	}

	// add slider factor to temp
	sum[2] = scalFactor + tempScal[0];
	sum[3] = scalFactor + tempScal[1];

	// equate sum to actual translate
	quad->setScale(sum[2]);
	tri->setScale(sum[3]);

}

void DebugWindow::resetVariables()
{
	posFactor.zero();
	scalFactor.zero();
	for (int i = 0; i < 4; i++)
	{
		sum[i].zero();
	}
}

void DebugWindow::renderWindow()
{

	//Render Draw Data
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
