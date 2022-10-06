#include "Quad.h"

Quad::Quad()
{
}

void Quad::initialize(VertexClass::vertex v[4], void* shaderByteCode, size_t sizeShader)
{
	for (size_t i = 0; i < 4; i++)
	{
		list[i] = v[i];
	}

	UINT size_list = ARRAYSIZE(list);

	vb = GraphicsEngine::get()->createVertexBuffer();

	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);

	vs = GraphicsEngine::get()->createVertexShader(shaderByteCode, sizeShader);
	vb->load(list, sizeof(VertexClass::vertex), size_list, shaderByteCode, sizeShader);

	GraphicsEngine::get()->releaseCompiledShader();

	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shaderByteCode, &sizeShader);
	ps = GraphicsEngine::get()->createPixelShader(shaderByteCode, sizeShader);
	GraphicsEngine::get()->releaseCompiledShader();
}

Quad::~Quad()
{
}

void Quad::drawQuad()
{
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(ps);


	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(vb);

	// FINALLY DRAW THE TRIANGLE
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(vb->getSizeVertexList(), 0);
}

void Quad::release()
{
	vb->release();
	vs->release();
	ps->release();
}


