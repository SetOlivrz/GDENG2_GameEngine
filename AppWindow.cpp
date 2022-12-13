#include "AppWindow.h"
#include <Windows.h>
#include <iostream>
#include "Utils.h"
#include "InputSystem.h"
#include "SceneCameraHandler.h"
#include "UIManager.h"
#include "PhysicsComponent.h"
#include "PhysicsSystem.h"
#include "BaseComponentSystem.h"
#include"GameObjectManager.h"
#include "EngineBackend.h"
#include "EngineBackend.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


class GraphicsEngine;



_declspec(align(16)) //make CBData a size of 16-bytes.
struct Constant {
	Matrix4x4 worldMatrix;
	Matrix4x4 viewMatrix;
	Matrix4x4 projMatrix;
	//unsigned int m_time; //size of only 4 bytes. this won't align in GPU device because device requires 16 bytes.
	float m_time;
};

AppWindow::AppWindow()
{
}


AppWindow::~AppWindow()
{
}

void AppWindow::update()
{
	
}

void AppWindow::onCreate()
{

	// Create Window
	Window::onCreate();

	//Initialize InputListener
	InputSystem::initialize();
	GraphicsEngine::create();
	GameObjectManager::get()->initialize();

	//Initialize SceneCameraHAndler
	SceneCameraHandler::initialize();

	BaseComponentSystem::initialize();

	InputSystem::getInstance()->addListener(this);

	//Initialize UIManager
	UIManager::getInstance()->initialize(Window::m_hwnd);

	EngineBackend::getInstance()->initialize();

	RECT rc = this->getClientWindowRect();

	//Set swap chain
	swapChain = GraphicsEngine::getInstance()->getRenderSystem()->createSwapChain(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	InputSystem::getInstance()->update();

	//CLEAR THE RENDER TARGET 
	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->clearRenderTargetColor(this->swapChain, 0, 0.3f, 0.4f, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	
	GameObjectManager::get()->updateObjects();
	
	//UPDATE BASED IN ENGINE STATE
	if (EngineBackend::getInstance()->getMode() == EngineBackend::EDITOR)
	{
		//UPDATE PHYSICS
		//BaseComponentSystem::getInstance()->getPhysicsSystem()->updateAllComponents();
	}
	else if (EngineBackend::getInstance()->getMode() == EngineBackend::PLAY)
	{
		//UPDATE PHYSICS
		BaseComponentSystem::getInstance()->getPhysicsSystem()->updateAllComponents();
	}
	else if (EngineBackend::getInstance()->getMode() == EngineBackend::PAUSED)
	{
		if (EngineBackend::getInstance()->insideFrameStep())
		{
			//UPDATE PHYSICS
			//BaseComponentSystem::getInstance()->getPhysicsSystem()->updateAllComponents();

			EngineBackend::getInstance()->endFrameStep();
		}
	}

	//UPDATE CAMERA
	SceneCameraHandler::getInstance()->update();

	UIManager::getInstance()->drawAllUI();


	swapChain->present(true);

}

void AppWindow::onDestroy()
{
	Window::onDestroy();
}

void AppWindow::onFocus()
{
}

void AppWindow::onKillFocus()
{
}

void AppWindow::onKeyDown(int key)
{
	if (key == 'H')
	{
		Vector3D rot;
		float var = ObjectList[3]->getLocalRotation().m_z + 30;
		ObjectList[3]->setRotation(ObjectList[3]->getLocalRotation().m_x, ObjectList[0]->getLocalRotation().m_y, var);
		std::cout << "ROTz: " << var << " \n";


	}
	if (key == 'F') //x
	{
		Vector3D rot;
		float var = ObjectList[0]->getLocalRotation().m_x + 30;
		ObjectList[3]->setRotation(var+1, ObjectList[0]->getLocalRotation().m_y, ObjectList[0]->getLocalRotation().m_z);
		std::cout << "ROTx: " << ObjectList[0]->getLocalRotation().m_x << " \n";

	}
}

void AppWindow::onKeyUp(int key)
{
}

void AppWindow::onMouseMove(const Point deltaPos)
{
	if (isLeftMouseDown)
	{
		Vector3D scale = armadillo->getLocalScale();
		scale.m_x += deltaPos.m_x * EngineTime::getDeltaTime();
		scale.m_y += deltaPos.m_y * EngineTime::getDeltaTime();
		scale.m_z += deltaPos.m_x * EngineTime::getDeltaTime();

		armadillo->setScale(scale);
	}
	

}

void AppWindow::onLeftMouseDown(const Point deltaPos)
{
	//std::cout << "Left mouse down! \n";

	////isLeftMouseDown = true;

}

void AppWindow::onLeftMouseUp(const Point deltaPos)
{
	//std::cout << "Left mouse up! \n";
	//isLeftMouseDown = false;


}

void AppWindow::onRightMouseDown(const Point deltaPos)
{
	//std::cout << "Right mouse down! \n";

	//cube[0]->setScale(Vector3D(2.0, 2.0, 2.0));

	//m_scale_cube = 2.0f;
}

void AppWindow::onRightMouseUp(const Point deltaPos)
{
	//std::cout << "Right mouse upward! \n";

	//cube[0]->setScale(Vector3D(1.0, 1.0, 1.0));

	//m_scale_cube = 1.0f;
}


// Simple helper function to load an image into a DX11 texture with common settings
bool LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
{
	ID3D11Device* g_pd3dDevice = GraphicsEngine::getInstance()->getRenderSystem()->getDevice();
	// Load from disk into a raw RGBA buffer
	int image_width = 0;
	int image_height = 0;
	unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
	if (image_data == NULL)
		return false;

	// Create texture
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = image_width;
	desc.Height = image_height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;

	ID3D11Texture2D* pTexture = NULL;
	D3D11_SUBRESOURCE_DATA subResource;
	subResource.pSysMem = image_data;
	subResource.SysMemPitch = desc.Width * 4;
	subResource.SysMemSlicePitch = 0;
	g_pd3dDevice->CreateTexture2D(&desc, &subResource, &pTexture);

	// Create texture view
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = desc.MipLevels;
	srvDesc.Texture2D.MostDetailedMip = 0;
	g_pd3dDevice->CreateShaderResourceView(pTexture, &srvDesc, out_srv);
	pTexture->Release();

	*out_width = image_width;
	*out_height = image_height;
	stbi_image_free(image_data);

	return true;
}