#pragma once
#include "AGameObject.h"
#include "Camera.h"

class Sphere : public AGameObject
{
public:
	Sphere(string name, void* shaderByteCode, size_t sizeShader);
	~Sphere();

	void update(float deltaTime) override;
	void draw(int width, int height) override;
	void setAnimation(float speed, float interval, bool isSpeeding, float rotFactor);

	float m_scale_cube = 1;
	float m_forward = 0.0f;
	float m_rightward = 0.0f;

private:

	float ticks = 0.0f;
	float deltaPos = 0.0f;
	float deltaTime = 0.0f;
	float speed = 1.0f;

	Camera* cam;

	Matrix4x4 m_world_cam;
	Matrix4x4 world_cam;

	bool isIncreasing = false;
	float rotFactor = 0.0f;
	float animationInterval = 0.0f;


};
