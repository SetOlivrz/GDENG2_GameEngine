#include "CreditScreen.h"
#include "imgui.h"
#include "UIManager.h"
#include <iostream>

bool CreditScreen::isOpen = false;

CreditScreen::CreditScreen() : AUIScreen("ColorPickerScreen")
{

}

CreditScreen::~CreditScreen()
{
	AUIScreen::~AUIScreen();

}

void CreditScreen::drawUI()
{
	if (isOpen)
	{
		//Create Imgui  Window
		ImGui::Begin("Credits");


		ImGui::Image((void*)UIManager::getInstance()->my_texture, ImVec2(UIManager::getInstance()->my_image_width, UIManager::getInstance()->my_image_height));
		// check boxes
		ImGui::Text("About:");
		ImGui::Text("Editor: v.1.");
		ImGui::Text("Developer: Setiel Olivarez");
		ImGui::Text("Acknowledgements:");
		ImGui::BulletText("Sir Neil Patrick Del Gallego");
		ImGui::BulletText("PardCode (https://www.youtube.com/c/PardCode)");
		ImGui::BulletText("imGui (https://github.com/ocornut/imgui.git)");

		ImGui::End();
	}
}
