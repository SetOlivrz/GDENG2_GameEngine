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
	ImGui_ImplDX11_Init(GraphicsEngine::getInstance()->getRenderSystem()->getDevice(), GraphicsEngine::getInstance()->getRenderSystem()->getDeviceContext());
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
}

void DebugWindow::createDisplayData( )
{
	// feed inputs to dear imgui, start new frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	//Create Imgui  Window
	ImGui::Begin("Credits");

	// check boxes
	ImGui::Text("About:");
	ImGui::Text("Editor: v.1.");
	ImGui::Text("Developer: Setiel Olivarez");
	ImGui::Text("Acknowledgements:");
	ImGui::BulletText("Sir Neil Patrick Del Gallego");
	ImGui::BulletText("PardCode (https://www.youtube.com/c/PardCode)");
	ImGui::BulletText("imGui (https://github.com/ocornut/imgui.git)");


	ImGui::End();

	//Assemble Together Draw Data
	ImGui::Render();
}

void DebugWindow::TransformSliders(Quad* obj)
{
	Utils::resetArr3(posFactor);
	Utils::resetArr3(scalFactor);
	Utils::resetArr3(sumA);
	Utils::resetArr3(sumB);
	Utils::resetArr3(sumC);
	Utils::resetArr3(sumD);

	/*ImGui::Text("");
	ImGui::Text("	  X		    Y");
	ImGui::SliderFloat2(" Position", obj->translation, -1.0, 1.0);
	if (ImGui::Button("Reset###Position"))
	{
		obj->resetPosition();
	}

	ImGui::SliderFloat2(" Scale", obj->scale, 0.0, 2);

	if (ImGui::Button("Reset###Scale"))
	{
		obj->resetScale();
	}*/
}

void DebugWindow::TransformSliders(Quad* quad, Quad* tri)
{

	//ImGui::Text("");
	//	ImGui::Text("	  X		    Y");
	//ImGui::SliderFloat2(" Position", posFactor, -1.0, 1.0);

	//// MULTIPLE TRANSLATION
	//// copy if not equal (has changes) 
	//if (!Utils::isEqual(sumA, quad->translation))
	//{
	//	Utils::copyArr3(quad->translation, tempPosA);
	//}

	//if (!Utils::isEqual(sumB, tri->translation))
	//{
	//	Utils::copyArr3(tri->translation, tempPosB);
	//}
	//// add slider factor to temp
	//Utils::addArr3(posFactor, tempPosA, sumA);
	//Utils::addArr3(posFactor, tempPosB, sumB);

	//// equate sum to actual translate
	//Utils::copyArr3(sumA, quad->translation);
	//Utils::copyArr3(sumB, tri->translation);


	//// MULTIPLE SCALING
	//ImGui::Text("");
	//ImGui::Text("	  X		    Y");
	//ImGui::SliderFloat2(" Scale", scalFactor, 0.0, 2.0);

	//// copy if not equal (has changes) 
	//if (!Utils::isEqual(sumC, quad->scale))
	//{
	//	Utils::copyArr3(quad->scale, tempScalA);
	//}

	//if (!Utils::isEqual(sumD, tri->scale))
	//{
	//	Utils::copyArr3(tri->scale, tempScalB);
	//}
	//// add slider factor to temp
	//Utils::addArr3(scalFactor, tempScalA, sumC);
	//Utils::addArr3(scalFactor, tempScalB, sumD);

	//// equate sum to actual translate
	//Utils::copyArr3(sumC, quad->scale);
	//Utils::copyArr3(sumD, tri->scale);

}

void DebugWindow::renderWindow()
{

	//Render Draw Data
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
