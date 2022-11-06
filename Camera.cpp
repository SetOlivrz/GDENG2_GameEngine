#include "Camera.h"
#include "InputSystem.h"
#include "EngineTime.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "Utils.h"
#include "SceneCameraHandler.h"


Camera::Camera(string name) : AGameObject(name)
{
	//preset camera values
	this->setPosition(0.0f, 0.0f, -2.0f);
	this->localMatrix.setTranslation(this->localPosition);
	InputSystem::getInstance()->addListener(this);
}

Camera::~Camera()
{
	InputSystem::getInstance()->removeListener(this);
	this->vertexBuffer->release();
	this->indexBuffer->release();
	this->constantBuffer->release();
	this->pixelShader->release();
	this->vertexShader->release();
	AGameObject::~AGameObject();
}

void Camera::update(float deltaTime)
{
	if (isActive)
	{
		// keu input for camerae
		if (InputSystem::getInstance()->isKeyDown('W'))
		{
			forward = 1; //forward
		}
		else if (InputSystem::getInstance()->isKeyDown('S'))
		{
			forward = -1; //backwards
		}
		else if (InputSystem::getInstance()->isKeyDown('A'))
		{
			rightward = -1; //sideward (left)
		}
		else if (InputSystem::getInstance()->isKeyDown('D'))
		{
			rightward = 1; //sidewards (right)
		}
		else if (InputSystem::getInstance()->isKeyDown('E'))
		{
			upward = 1; //upwards
		}
		else if (InputSystem::getInstance()->isKeyDown('Q'))
		{
			upward = -1;//downwards
		}

		updateViewMatrix();
	}
	else
	{
		if (InputSystem::getInstance()->isKeyDown('I'))
		{
			forward = 1; //forward
		}
		else if (InputSystem::getInstance()->isKeyDown('K'))
		{
			forward = -1; //backwards
		}
		else if (InputSystem::getInstance()->isKeyDown('J'))
		{
			rightward = -1; //sideward (left)
		}
		else if (InputSystem::getInstance()->isKeyDown('L'))
		{
			rightward = 1; //sidewards (right)
		}
		else if (InputSystem::getInstance()->isKeyDown('O'))
		{
			upward = 1; //upwards
		}
		else if (InputSystem::getInstance()->isKeyDown('U'))
		{
			upward = -1;//downwards
		}

		updateViewMatrix();
	}
	

}


Matrix4x4 Camera::getVMatrix()
{
	return this->localMatrix;
}

Matrix4x4 Camera::getViewMatrix()
{
	return this->world_cam;
}


void Camera::setCameraStatus(bool flag)
{
	 isActive  = flag;
}

bool Camera::getCameraStatus()
{
	return isActive;
}

void Camera::setFustrumVisibility(bool flag)
{
	isFustrumEnabled = flag;
}

bool Camera::getFustrumVisibility()
{
	return isFustrumEnabled;
}

float Camera::getForward()
{
	return forward;
}

float Camera::getRightward()
{
	return rightward;
}

float Camera::getUpward()
{
	return upward;
}

float Camera::getFOV()
{
	return this->FOV;
}

float Camera::getNearZ()
{
	return this->nearZ;
}

float Camera::getFarZ()
{
	return this->farZ;
}

float Camera::getAspectRatio()
{
	return aspectRatio;
}

void Camera::setFOV(float FOV)
{
	this->FOV = FOV;
}

void Camera::setNearZ(float nz)
{
	this->nearZ = nz;
}

void Camera::setFarZ(float fz)
{
	this->farZ = fz;
}

void Camera::setAspect(float aspectRatio)
{
	this->aspectRatio = aspectRatio;
}


void Camera::onKeyDown(int key)
{
	//if (key == 'W')
	//{
	//	//cube[0]->setRotation(Vector3D( v.m_x+ 3.14f * EngineTime::getDeltaTime(),v.m_y,v.m_z));
	//	forward = 1.0f;
	//}
	//else if (key == 'S')
	//{
	//	//cube[0]->setRotation(Vector3D(v.m_x - 3.14f * EngineTime::getDeltaTime(), v.m_y, v.m_z));
	//	forward = -1.0f;

	//}
	//else if (key == 'A')
	//{
	//	//cube[0]->setRotation(Vector3D(v.m_x, v.m_y + 3.14 *EngineTime::getDeltaTime(), v.m_z));
	//	rightward = -1.0f;

	//}
	//else if (key == 'D')
	//{
	//	//cube[0]->setRotation(Vector3D(v.m_x, v.m_y - 3.14 * EngineTime::getDeltaTime(), v.m_z));
	//	 rightward= 1.0f;

	//}
}

void Camera::onKeyUp(int key)
{
	forward = 0;
	rightward = 0;
	upward = 0;
}

void Camera::onMouseMove(const Point deltaPos)
{
	if (this->mouseDown && this->isActive) 
	{
		Vector3D v = this->getLocalRotation();
		// may add speed factor
		v.m_x += (deltaPos.m_y  * EngineTime::getDeltaTime() * 0.1f);
		v.m_y += (deltaPos.m_x * EngineTime::getDeltaTime() * 0.1f);

		// update rotation
		this->setRotation(v);

		// centering mouse pos
		//InputSystem::get()->setCursorPosition(Point((int)(width / 2.0f), (int)(height / 2.0f)));
	}
}

void Camera::onLeftMouseDown(const Point deltaPos)
{
}

void Camera::onLeftMouseUp(const Point deltaPos)
{
}

void Camera::onRightMouseDown(const Point deltaPos)
{
	this->mouseDown = true;
}

void Camera::onRightMouseUp(const Point deltaPos)
{
	this->mouseDown = false;
}

void Camera::updateViewMatrix()
{
	Constant cc;
	Matrix4x4 temp;
	
	//UPDATE FOR CAM ROTATION
	world_cam.setIdentity();
	temp.setIdentity();
	temp.setRotationX(this->getLocalRotation().m_x);
	world_cam *= temp;

	temp.setIdentity();
	temp.setRotationY(this->getLocalRotation().m_y);
	world_cam *= temp;


	// UPDATE FOR CAM TRANSLATION
	Vector3D new_pos = this->localMatrix.getTranslation() + (world_cam.getZDirection() * (this->forward * 0.1f));
	new_pos = new_pos + (world_cam.getYDirection() * (this->upward * 0.1f));
	new_pos = new_pos + (world_cam.getXDirection() * (this->rightward * 0.1f));

	this->setPosition(new_pos);

	world_cam.setTranslation(new_pos);
	//update local matrix
	this->localMatrix = world_cam;

	// application
	world_cam.inverse();

	//std::cout << "x: "<<this->getLocalPosition().m_x <<" y: "<< this->getLocalPosition().m_y<<" z: "<<this->getLocalPosition().m_z <<"\n";
}

void Camera::draw(int width, int height)
{
}
