#include "UIManager.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "EditorScreen.h"
#include "ColorPickerScreen.h"
#include "CreditScreen.h"

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

	ColorPickerScreen* colorPicker = new ColorPickerScreen();
	this->uiTable[uiNames.COLOR_PICKER_SCREEN] = colorPicker;
	this->uiList.push_back(colorPicker);

	CreditScreen* creditScreen = new CreditScreen();

	//creditScreen->my_image_height = this->my_image_height;
	//creditScreen->my_image_width = this->my_image_width;
	//creditScreen->my_texture = this->my_texture;

	this->uiTable[uiNames.CREDITS_SCREEN] = creditScreen;
	this->uiList.push_back(creditScreen);
}

UIManager::~UIManager()
{
}
