#include "Camera.h"
#include "InputSystem.h"

Camera::Camera(string name) : AGameObject(name)
{
	this->forwardDirection = Vector3D(1.0f, 0.0f, 1.0f);
	this->backwardDirection = Vector3D(-1.0f, 0.0f, -1.0f);

	this->setPosition(0.0f, 0.0f, -4.0f);
	//this->worldCameraMatrix.setTranslation(this->getLocalPosition());
	this->updateViewMatrix();
	InputSystem::getInstance()->addListener(this);
}

Camera::~Camera()
{
	InputSystem::getInstance()->removeListener(this);
}

void Camera::update(float deltaTime)
{
	Vector3D localPos = this->getLocalPosition();
	float x = localPos.m_x;
	float y = localPos.m_y;
	float z = localPos.m_z;
	float moveSpeed = 10.0f;

	if (InputSystem::getInstance()->isKeyDown('W')) {
		z += deltaTime * moveSpeed;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('S')) {
		z -= deltaTime * moveSpeed;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('A')) {
		x += deltaTime * moveSpeed;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
		std::cout << "x:" << x <<"\n";

	}
	else if (InputSystem::getInstance()->isKeyDown('D')) {
		x -= deltaTime * moveSpeed;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
		std::cout <<  " y: " << y << "\n";

	}
}

Matrix4x4 Camera::getViewMatrix()
{
	return this->localMatrix;
}

void Camera::onKeyDown(int key)
{
}

void Camera::onKeyUp(int key)
{
}

void Camera::onMouseMove(const Point deltaPos)
{
	if (this->mouseDown) 
	{
		Vector3D localRot = this->getLocalRotation();
		float x = localRot.m_x;
		float y = localRot.m_y;
		float z = localRot.m_z;

		float speed = 0.005f;
		x += deltaPos.m_y * speed;
		y += deltaPos.m_x * speed;

		this->setRotation(x, y, z);
		this->updateViewMatrix();
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
	std::cout << "Right mouse downnn! \n";

}

void Camera::onRightMouseUp(const Point deltaPos)
{
	this->mouseDown = false;
	std::cout << "Right mouse yppp! \n";

}

void Camera::updateViewMatrix()
{
	Matrix4x4 worldCam; 
	worldCam.setIdentity();

	Matrix4x4 temp; 
	temp.setIdentity();

	Vector3D localRot = this->getLocalRotation();

	temp.setRotationX(localRot.m_x);
	worldCam *= temp;

	temp.setRotationY(localRot.m_y);
	worldCam *= temp;

	temp.setTranslation(this->getLocalPosition());
	worldCam *= temp;

	worldCam.inverse();
	this->localMatrix = worldCam;
}

void Camera::draw(int width, int height)
{
}
