#include "ColorPickerScreen.h"
#include "imgui.h"
#include "UIManager.h"
#include <iostream>

bool ColorPickerScreen::isOpen = false;

ColorPickerScreen::ColorPickerScreen(): AUIScreen("ColorPickerScreen")
{

}

ColorPickerScreen::~ColorPickerScreen()
{
	AUIScreen::~AUIScreen();

}

void ColorPickerScreen::drawUI()
{
	if (isOpen)
	{
		ImGui::Begin("Color Picker");

		float col[3] = {};
		ImGui::ColorPicker3("Color Picker", col);

		ImGui::End();
	}
}
