#include "AppWindow.h"
#include <Windows.h>
#include <iostream>
#include "Utils.h"
#include "InputSystem.h"
#include "SceneCameraHandler.h"
#include "UIManager.h"

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
	Window::onCreate();

	InputSystem::initialize();
	SceneCameraHandler::initialize();

	InputSystem::getInstance()->addListener(this);
	//InputSystem::getInstance()->showCursor(false);

	// ENGINE
	GraphicsEngine::get()->init();

	UIManager::getInstance()->initialize(Window::m_hwnd);

	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);


	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;
	/*for (int i = 0; i <20 ; i++)
	{
		float x = Utils::randFloatInterval(-5, 5);
		float y = Utils::randFloatInterval(-5, 5);
		float z = Utils::randFloatInterval(-5, 0);

		float sx = Utils::randFloatInterval(0.25, 2);
		float sy = Utils::randFloatInterval(0.25, 2);
		float sz = Utils::randFloatInterval(0.25, 2);



		Cube *cubeObj =  new Cube("Cube", shaderByteCode, sizeShader);
		cubeObj->setPosition(x,y,z);
		cubeObj->setScale(sx,sy,sz);
		cubeObj->setAnimation(Utils::randFloatInterval(1.0, 1.0), Utils::randFloatInterval(2.0, 5.0),true, 1 );
		this->CubeList.push_back(cubeObj);
	}*/

	Plane* planeObj = new Plane ("Plane", shaderByteCode, sizeShader);
	planeObj->setPosition(0.0, 0.0, 0.0f);
	planeObj->setScale(2, 2.0, 0);


	//planeObj->setAnimation(1, 20, true);a
	plane[0] = planeObj;

	Cube* cubeObj = new Cube("Cube", shaderByteCode, sizeShader);
	cubeObj->setPosition(0.0, 0.0, 0.0f);
	//cubeObj->setAnimation(1,20, true);
	cube[0] = cubeObj;


	int width = 0;
	int height = 0;
	ID3D11ShaderResourceView* texture = NULL;
	bool ret = LoadTextureFromFile("C://Users//Setiel Olivarez/Desktop/School/GDENG2/Project/Game Engine/dlsu.png", &texture, &width, &height);
	IM_ASSERT(ret);

	UIManager::getInstance()->my_image_width = width/4;
	UIManager::getInstance()->my_image_height = height/4;
	UIManager::getInstance()->my_texture = texture;



}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	InputSystem::getInstance()->update();

	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0, 0.1f, 0.2f, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);



	//UPDATE PRIMITIVES
	/*for (int i = 0; i < CubeList.size(); i++)
	{
		CubeList[i]->update(EngineTime::getDeltaTime());
	}

	for (int i = 0; i < CubeList.size(); i++)
	{
		CubeList[i]->draw(rc.right - rc.left, rc.bottom - rc.top);
	}*/

	//UPDATE CAMERA
	SceneCameraHandler::getInstance()->update();

	/*cube[0]->update(EngineTime::getDeltaTime());
	cube[0]->draw(rc.right - rc.left, rc.bottom - rc.top);*/

	plane[0]->update(EngineTime::getDeltaTime());
	plane[0]->draw(rc.right - rc.left, rc.bottom - rc.top);

	UIManager::getInstance()->drawAllUI();


	m_swap_chain->present(true);

}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();
	GraphicsEngine::get()->release();
}

void AppWindow::onFocus()
{
	//InputSystem::getInstance()->addListener(this);
}

void AppWindow::onKillFocus()
{
	//InputSystem::getInstance()->removeListener(this);
}

void AppWindow::onKeyDown(int key)
{
	//Vector3D v = cube[0]->getRotation();

	if (key == 'F')
	{
		float var = plane[0]->getLocalRotation().m_z + EngineTime::getDeltaTime();
		plane[0]->setRotation( 0,0, var);
		std::cout << "ROT: "<< plane[0]->getLocalRotation().m_z<<" \n";


	}
	//else if (key == 'S')
	//{
	//	//cube[0]->setRotation(Vector3D(v.m_x - 3.14f * EngineTime::getDeltaTime(), v.m_y, v.m_z));
	//	cube[0]->m_forward = -1.0f;

	//}
	//else if (key == 'A')
	//{
	//	//cube[0]->setRotation(Vector3D(v.m_x, v.m_y + 3.14 *EngineTime::getDeltaTime(), v.m_z));
	//	cube[0]->m_rightward = -1.0f;

	//}
	//else if (key == 'D')
	//{
	//	//cube[0]->setRotation(Vector3D(v.m_x, v.m_y - 3.14 * EngineTime::getDeltaTime(), v.m_z));
	//	cube[0]->m_rightward = 1.0f;

	//}
	
}

void AppWindow::onKeyUp(int key)
{
	/*cube[0]->m_forward = 0.0f;
	cube[0]->m_rightward = 0.0f;*/

}

void AppWindow::onMouseMove(const Point deltaPos)
{
	/*int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
	int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);

	Vector3D v = cube[0]->getRotation();

	v.m_x += (deltaPos.m_y - (height / 2.0f)) * EngineTime::getDeltaTime() * 0.1f;
	v.m_y += (deltaPos.m_x - (width / 2.0f)) * EngineTime::getDeltaTime() * 0.1f;


	cube[0]->setRotation(v);

	InputSystem::getInstance()->setCursorPosition(Point((int)(width / 2.0f), (int)(height / 2.0f)));*/

}

void AppWindow::onLeftMouseDown(const Point deltaPos)
{
	//cube[0]->setScale(Vector3D(0.5, 0.5, 0.5));
	//std::cout << "Left mosssssssssssssssssssssssssssssssssssssssuse down! \n";
	//plane[0]->setRotation(0.0, 0.0, plane[0]->getLocalRotation().m_z + EngineTime::getDeltaTime());

}

void AppWindow::onLeftMouseUp(const Point deltaPos)
{
	//cube[0]->setScale(Vector3D(1.0, 1.0, 1.0));
	std::cout << "Left mouse upward! \n";



}

void AppWindow::onRightMouseDown(const Point deltaPos)
{
	std::cout << "Right mouse down! \n";

	//cube[0]->setScale(Vector3D(2.0, 2.0, 2.0));

	//m_scale_cube = 2.0f;
}

void AppWindow::onRightMouseUp(const Point deltaPos)
{
	std::cout << "Right mouse upward! \n";

	//cube[0]->setScale(Vector3D(1.0, 1.0, 1.0));

	//m_scale_cube = 1.0f;
}


// Simple helper function to load an image into a DX11 texture with common settings
bool LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
{
	ID3D11Device* g_pd3dDevice = GraphicsEngine::get()->getDevice();
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