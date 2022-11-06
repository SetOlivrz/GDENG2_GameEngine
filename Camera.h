#pragma once
#include "AGameObject.h"
#include "InputListener.h"
#include "Vector3D.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"

#include "VertexShader.h"
#include "PixelShader.h"


class Camera : public AGameObject, public InputListener
{
public:
	Camera(string name);
	~Camera();

	void update(float deltaTime) override;
	Matrix4x4 getVMatrix();
	Matrix4x4 getViewMatrix();

	void setCameraStatus(bool flag);
	bool getCameraStatus();

	void setFustrumVisibility(bool flag);
	bool getFustrumVisibility();

	float getForward();
	float getRightward();
	float getUpward();

	float getFOV();
	float getNearZ();
	float getFarZ();
	float getAspectRatio();


	void setFOV(float fov);
	void setNearZ(float nz);
	void setFarZ(float fz);
	void setAspect(float aspectRatio);



	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	virtual void onMouseMove(const Point deltaPos) override;
	virtual void onLeftMouseDown(const Point deltaPos) override;
	virtual void onLeftMouseUp(const Point deltaPos) override;
	virtual void onRightMouseDown(const Point deltaPos) override;
	virtual void onRightMouseUp(const Point deltaPos) override;
private:
	void updateViewMatrix();

	Matrix4x4 world_cam;

	float ticks = 0.0f;
	float mouseDown = false;
	float isActive = false;


	float forward = 0;
	float rightward = 0;
	float upward = 0;

	Camera* cam;

	// Inherited via AGameObject
	virtual void draw(int width, int height) override;

	//FUSTRUM
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	ConstantBuffer* constantBuffer;

	VertexShader* vertexShader;
	PixelShader* pixelShader;

	bool isFustrumEnabled = false;

	float FOV = 0;
	float nearZ = 0;
	float farZ = 0;
	float aspectRatio = 0;
};

