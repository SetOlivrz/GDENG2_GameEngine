#pragma once
#include "AGameObject.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"

#include "VertexShader.h"
#include "PixelShader.h"

class Cube : public AGameObject
{
public:
	Cube(string name, void* shaderByteCode, size_t sizeShader);
	~Cube();

	void update(float deltaTime) override;
	void draw(int width, int height) override;
	void setAnimation(float speed, float interval, bool isSpeeding);

	void resetPosition();

	void resetScale();

	void setScale(Vector3D v);
	void setTranslation(Vector3D v);
	void setRotation(Vector3D v);

	Vector3D getScale();
	Vector3D getTranslation();
	Vector3D getRotation();

	float m_scale_cube = 1;
	float m_forward = 0.0f;
	float m_rightward = 0.0f;
	Matrix4x4 m_world_cam;

private:
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	ConstantBuffer* constantBuffer;

	VertexShader* vertexShader;
	PixelShader* pixelShader;

	Vector3D translation = Vector3D(0, 0, 0);
	Vector3D scale = Vector3D(1, 1, 1);
	Vector3D rotation = Vector3D(0, 0, 0);

	float ticks = 0.0f;
	float deltaTime = 0.0f;
	float speed = 1.0f;
	bool isIncreasing = false;
	//float rotation = 5.0f;
	float animationInterval = 0.0f;


};
