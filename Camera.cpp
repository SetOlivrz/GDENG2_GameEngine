#include "Camera.h"
#include "InputSystem.h"
#include "EngineTime.h"

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
}

void Camera::update(float deltaTime)
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

Matrix4x4 Camera::getViewMatrix()
{
	return this->cam_view_matrix;
}

Matrix4x4 Camera::getWorldCamMatrix()
{
	return this->cam_view_matrix;
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
	if (this->mouseDown) 
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
	cam_view_matrix.setIdentity();
	temp.setIdentity();
	temp.setRotationX(this->getLocalRotation().m_x);
	cam_view_matrix *= temp;

	temp.setIdentity();
	temp.setRotationY(this->getLocalRotation().m_y);
	cam_view_matrix *= temp;


	// UPDATE FOR CAM TRANSLATION
	Vector3D new_pos = this->localMatrix.getTranslation() + (cam_view_matrix.getZDirection() * (this->forward * 0.1f));
	new_pos = new_pos + (cam_view_matrix.getYDirection() * (this->upward * 0.1f));
	new_pos = new_pos + (cam_view_matrix.getXDirection() * (this->rightward * 0.1f));

	cam_view_matrix.setTranslation(new_pos);
	cam_view_matrix.setTranslation(new_pos);

	//update local matrix
	this->localMatrix = cam_view_matrix;

	// application
	cam_view_matrix.inverse();

	//std::cout << "x: "<<this->getLocalPosition().m_x <<" y: "<< this->getLocalPosition().m_y<<" z: "<<this->getLocalPosition().m_z <<"\n";
}

void Camera::draw(int width, int height)
{
}
