#include "UIManager.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "HierarchyScreen.h"
#include "SceneControlsScreen.h"
#include "InspectorScreen.h"
#include "EditorScreen.h"

UIManager* UIManager::sharedInstance = NULL;

UIManager* UIManager::getInstance()
{
	return sharedInstance;
}

void UIManager::initialize(HWND windowHandle)
{
	sharedInstance = new UIManager(windowHandle);
}

void UIManager::destroy()
{
	delete sharedInstance;
}

void UIManager::drawAllUI()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	for (int i = 0; i < this->uiList.size(); i++)
	{
		this->uiList[i]->drawUI();
	}

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

UIManager::UIManager(HWND windowHandle)
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	//Setup Platform/Renderer bindings
	ImGui_ImplWin32_Init(windowHandle);
	ImGui_ImplDX11_Init(GraphicsEngine::getInstance()->getRenderSystem()->getDevice(), GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->getDeviceContext());

	//Populate UI Table (Note: ordering matters)
	UINames uiNames;

	EditorScreen* editorScreen = new EditorScreen();
	this->uiTable[uiNames.EDITOR_SCREEN] = editorScreen;
	this->uiList.push_back(editorScreen);

	HierarchyScreen* hierarchyScreen = new HierarchyScreen();
	this->uiTable[uiNames.HIERARCHY_SCREEN] = hierarchyScreen;
	this->uiList.push_back(hierarchyScreen);

	SceneControlsScreen* sceneControlsScreen = new SceneControlsScreen();
	this->uiTable[uiNames.SCENECONTROLS_SCREEN] = sceneControlsScreen;
	this->uiList.push_back(sceneControlsScreen);

	InspectorScreen* inspectorScreen = new InspectorScreen();
	this->uiTable[uiNames.INSPECTOR_SCREEN] = inspectorScreen;
	this->uiList.push_back(inspectorScreen);
}

UIManager::~UIManager()
{
}
