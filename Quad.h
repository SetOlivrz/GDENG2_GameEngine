#pragma once

#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "VertexClass.h"
class Quad
{

public:
	Quad();
	void initialize( VertexClass::vertex list[4], void* shaderByteCode, size_t sizeShader);
	~Quad();

private:
	VertexClass::vertex list[4];
	VertexBuffer* vb;
	VertexShader* vs;
	PixelShader* ps;
public:
	void update();
	void drawQuad();
	void release();
};

