#pragma once
#include "AGameObject.h"
#include "InputListener.h"
#include "Vector3D.h"


class Camera : public AGameObject, public InputListener
{
public:
	Camera(string name);
	~Camera();

	void update(float deltaTime) override;
	Matrix4x4 getViewMatrix();
	Matrix4x4 getWorldCamMatrix();


	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	virtual void onMouseMove(const Point deltaPos) override;
	virtual void onLeftMouseDown(const Point deltaPos) override;
	virtual void onLeftMouseUp(const Point deltaPos) override;
	virtual void onRightMouseDown(const Point deltaPos) override;
	virtual void onRightMouseUp(const Point deltaPos) override;

	float forward = 0;
	float rightward = 0;

private:
	void updateViewMatrix();

	Matrix4x4 world_cam;

	float ticks = 0.0f;
	float mouseDown = false;


	// Inherited via AGameObject
	virtual void draw(int width, int height) override;

	Vector3D forwardDirection;
	Vector3D backwardDirection;

};

