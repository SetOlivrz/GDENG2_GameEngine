#include "EditorScreen.h"
#include "imgui.h"
#include "UIManager.h"
#include "ColorPickerScreen.h"
#include "CreditScreen.h"

EditorScreen::EditorScreen() : AUIScreen("EditorScreen")
{

}

EditorScreen::~EditorScreen()
{
    AUIScreen::~AUIScreen();
}

void EditorScreen::drawUI()
{
    bool* p_open = new bool;
    *p_open = true;

    ImGui::SetNextWindowSize(ImVec2(UIManager::WINDOW_WIDTH, UIManager::WINDOW_HEIGHT));
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Tools"))
        {

            if (ImGui::MenuItem("Open Color Picker")) 
            { 
                ColorPickerScreen::isOpen = true;
            }

            if (ImGui::MenuItem("About"))
            {
                CreditScreen::isOpen = true;
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}
