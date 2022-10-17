#pragma once
#include "AGameObject.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"

#include "VertexShader.h"
#include "PixelShader.h"

class Plane : public AGameObject
{
public:
	Plane(string name, void* shaderByteCode, size_t sizeShader);
	~Plane();

	void update(float deltaTime) override;
	void draw(int width, int height) override;
	void setAnimation(float speed, float interval, bool isSpeeding);



private:
	VertexBuffer* vertexBuffer;
	ConstantBuffer* constantBuffer;

	VertexShader* vertexShader;
	PixelShader* pixelShader;

	float ticks = 0.0f;
	float deltaTime = 0.0f;
	float speed = 1.0f;
	bool isIncreasing = false;
	float rotation = 5.0f;
	float animationInterval = 0.0f;
};
