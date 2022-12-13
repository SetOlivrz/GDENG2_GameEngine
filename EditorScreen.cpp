#include "EditorScreen.h"
#include "imgui.h"
#include "UIManager.h"
#include "ColorPickerScreen.h"
#include "CreditScreen.h"
#include "GameObjectManager.h"
#include "HierarchyScreen.h"
#include "InspectorScreen.h"
#include "SceneControlsScreen.h"
#include "SceneWriterAndReader.h"

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
        if (ImGui::BeginMenu("Files"))
        {
            if (ImGui::MenuItem("Save File As JSON"))
            {
                SceneWriterAndReader* sceneWriter = new SceneWriterAndReader();
                sceneWriter->writeToFile();
            }
            if (ImGui::MenuItem("Load Saved File"))
            {
                SceneWriterAndReader* sceneReader = new SceneWriterAndReader();
                sceneReader->readFromEngineFile();
            }
            if (ImGui::MenuItem("Load From Unity"))
            {
                SceneWriterAndReader* sceneReader = new SceneWriterAndReader();
                sceneReader->readFromUnityFile();

            }

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("GameObject"))
        {
            if (ImGui::MenuItem("Spawn Cube"))
            {
                GameObjectManager::get()->createPhysicsCube();
            }
            if (ImGui::MenuItem("Spawn Sphere"))
            {
                GameObjectManager::get()->createPhysicsSphere();
            }
            if (ImGui::MenuItem("Spawn Capsule"))
            {
                GameObjectManager::get()->createPhysicsCapsule();
            }
            if (ImGui::MenuItem("Spawn Cubes"))
            {
                GameObjectManager::get()->createPhysicsCubes();

            }
            if (ImGui::MenuItem("Spawn Plane"))
            {
                GameObjectManager::get()->createPlane();

            }
            ImGui::EndMenu();
        }
     
        if (ImGui::BeginMenu("Windows"))
        {
            if (ImGui::MenuItem("Heirarchy")) { HierarchyScreen::isOpen = true; }
            if (ImGui::MenuItem("Inspector")) { InspectorScreen::isOpen = true; }
            if (ImGui::MenuItem("Scene Controls")) { SceneControlsScreen::isOpen = true; }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
       
    }
}
