#include "Camera.h"
#include "InputSystem.h"
#include "EngineTime.h"

Camera::Camera(string name) : AGameObject(name)
{
	this->forwardDirection = Vector3D(1.0f, 0.0f, 1.0f);
	this->backwardDirection = Vector3D(-1.0f, 0.0f, -1.0f);

	this->setPosition(0.0f, 0.0f, -2.0f);
	this->localMatrix.setTranslation(this->localPosition);
	//this->worldCameraMatrix.setTranslation(this->getLocalPosition());
	InputSystem::getInstance()->addListener(this);
}

Camera::~Camera()
{
	InputSystem::getInstance()->removeListener(this);
}

void Camera::update(float deltaTime)
{
	//Vector3D localPos = this->getLocalPosition();
	//float x = localPos.m_x;
	//float y = localPos.m_y;
	//float z = localPos.m_z;
	//float moveSpeed = 10.0f;

	//Vector3D v = Vector3D(x, y, z);

	if (InputSystem::getInstance()->isKeyDown('W')) {
		//v.m_z += deltaTime * moveSpeed;
		//v = v + localMatrix.getZDirection();
		//this->setPosition(v);
		//this->updateViewMatrix();
		forward = 1;
		std::cout << "S\n";

	}
	else if (InputSystem::getInstance()->isKeyDown('S')) {
	/*	v.m_z -= deltaTime * moveSpeed;
		v = v + localMatrix.getZDirection();
		this->setPosition(v);
		this->updateViewMatrix();*/
		forward = -1;
		std::cout << "S \n";


	}
	else if (InputSystem::getInstance()->isKeyDown('A')) {
		/*v.m_x += deltaTime * moveSpeed;
		v = v + localMatrix.getXDirection();
		this->setPosition(v);
		this->updateViewMatrix();
		std::cout << "x:" << x <<"\n";*/
		rightward = -1;
		std::cout << "A! \n";



	}
	else if (InputSystem::getInstance()->isKeyDown('D')) {
		/*v.m_x -= deltaTime * moveSpeed;
		v = v + localMatrix.getXDirection();
		this->setPosition(v);
		this->updateViewMatrix();
		std::cout <<  " y: " << y << "\n";*/
		rightward = 1;
		std::cout << "D\n";



	}
}

Matrix4x4 Camera::getViewMatrix()
{
	return this->localMatrix;
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
}

void Camera::onMouseMove(const Point deltaPos)
{
	if (this->mouseDown) 
	{
		/*Vector3D localRot = this->getLocalRotation();
		float x = localRot.m_x;
		float y = localRot.m_y;
		float z = localRot.m_z;

		float speed = 0.005f;
		x += deltaPos.m_y * speed;
		y += deltaPos.m_x * speed;

		this->setRotation(x, y, z);
		this->updateViewMatrix();*/

		/*int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
		int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);*/

		Vector3D v = this->getLocalRotation();

		v.m_x += (deltaPos.m_y  * EngineTime::getDeltaTime() * 0.1f);
		v.m_y += (deltaPos.m_x * EngineTime::getDeltaTime() * 0.1f);


		this->setRotation(v);

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
	std::cout << "Right mouse downnn! \n";

}

void Camera::onRightMouseUp(const Point deltaPos)
{
	this->mouseDown = false;
	std::cout << "Right mouse yppp! \n";

}

void Camera::updateViewMatrix()
{
	/*Matrix4x4 worldCam; 
	worldCam.setIdentity();

	Matrix4x4 temp; 
	temp.setIdentity();

	Vector3D localRot = this->getLocalRotation();

	temp.setRotationX(localRot.m_x);
	worldCam *= temp;

	temp.setRotationY(localRot.m_y);
	worldCam *= temp;

	temp.setTranslation(Vector3D(this->getLocalPosition()));
	worldCam *= temp;

	worldCam.inverse();
	this->localMatrix = worldCam;*/
}

void Camera::draw(int width, int height)
{
}
