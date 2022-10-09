#pragma once

#include "Window.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"

#include "VertexShader.h"
#include "PixelShader.h"

#include "VertexClass.h"
#include "Matrix4x4.h"

class Quad
{

public:
	Quad();
	void initialize(VertexClass::vertex list[4], void* shaderByteCode, size_t sizeShader);
	~Quad();

private:
	VertexClass::vertex list[4];
	VertexBuffer* m_vb;
	VertexShader* m_vs;
	PixelShader* m_ps;
	ConstantBuffer* m_cb;

	unsigned long m_old_time = 0;
	float m_delta_time = 0;
	float m_angle = 0;
public:
	void drawQuad();
	void release();
	void update(RECT window);

	void resetPosition();
	void resetScale();


	float translation[3]= {0.0,0.0, 0.0};
	float scale[3] = { 1.0, 1.0, 1.0 };

};
