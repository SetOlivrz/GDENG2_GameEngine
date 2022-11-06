#include "AppWindow.h"
#include <Windows.h>
#include <iostream>
#include "Utils.h"
#include "InputSystem.h"
#include "SceneCameraHandler.h"


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
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);


	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;
	
	// CREATE CAMERAS
	camObj = new Camera("ObjCam");
	sceneCamera = new Camera("SceneCam");

	//UPDATE CAMERA PARAMETERS
	float aspectRatio = (float)(rc.right - rc.left) / (float)(rc.bottom - rc.top);
	static float nearZ = 1.0f;
	static float farZ = 5;

	camObj->setAspect(aspectRatio);
	camObj->setFOV(aspectRatio);
	camObj->setNearZ(nearZ);
	camObj->setFarZ(farZ);

	sceneCamera->setAspect(aspectRatio);
	sceneCamera->setFOV(aspectRatio);
	sceneCamera->setNearZ(1);
	sceneCamera->setFarZ(100);

	// set one camera to camera scene
	SceneCameraHandler::getInstance()->SetSceneCamera(sceneCamera);

	//CREATE CAMERA GIZMO
	cameraGizmo = new Gizmo("CameraGizmo", shaderByteCode, sizeShader);
	cameraGizmo->setPosition(camObj->getLocalPosition().m_x, camObj->getLocalPosition().m_y, camObj->getLocalPosition().m_z);
	cameraGizmo->setScale(.25, .25, .25);

	//CREATE CUBE
	cube = new Cube("Cube", shaderByteCode, sizeShader);
	cube->setPosition(camObj->getLocalPosition().m_x, camObj->getLocalPosition().m_y, camObj->getLocalPosition().m_z);
	cube->setScale(1, 1, 1);

	//CREATE FRUSTUM
	fustrum = new Frustum("Frustum", shaderByteCode, sizeShader);
	fustrum->setPosition(0.0, 0.0, -3.0f);
	fustrum->camera = camObj; // set camera ref
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

	// SWITCH SCENE CAMERA (F KEY)
	if (isUsingCameraObj)
	{
		SceneCameraHandler::getInstance()->SetSceneCamera(camObj);
	}
	else
	{
		SceneCameraHandler::getInstance()->SetSceneCamera(sceneCamera);
		//camObj->update(EngineTime::getDeltaTime());
	}
	//UPDATE SCENE CAMERA
	SceneCameraHandler::getInstance()->update(); 

	Vector3D camPos = camObj->getLocalPosition();
	Vector3D camRot = camObj->getLocalRotation();

	// UPDATE PRIMITIVES
	cube->update(EngineTime::getDeltaTime());
	fustrum->update(EngineTime::getDeltaTime());

	cameraGizmo->setPosition(camPos.m_x, camPos.m_y, camPos.m_z);
	cameraGizmo->setRotation(camRot.m_x, camRot.m_y, camRot.m_z);
	cameraGizmo->update(EngineTime::getDeltaTime());

	// SET RASTERIZER
	GraphicsEngine::get()->getImmediateDeviceContext()->setRasterizeSetState(GraphicsEngine::get()->getRasterizerStateWF());
	if (!isUsingCameraObj)
		fustrum->draw(rc.right - rc.left, rc.bottom - rc.top); 

	// SET RASTERIZER
	GraphicsEngine::get()->getImmediateDeviceContext()->setRasterizeSetState(GraphicsEngine::get()->getRasterizerStateSLD());
	cube->draw(rc.right - rc.left, rc.bottom - rc.top);
	if(!isUsingCameraObj)
		cameraGizmo->draw(rc.right - rc.left, rc.bottom - rc.top);

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
		isUsingCameraObj = !isUsingCameraObj;
		std::cout << "camera Object: " << isUsingCameraObj<< " \n";
	}
	
}

void AppWindow::onKeyUp(int key)
{

}

void AppWindow::onMouseMove(const Point deltaPos)
{

}

void AppWindow::onLeftMouseDown(const Point deltaPos)
{
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
}