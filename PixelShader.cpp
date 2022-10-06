#include "PixelShader.h"
#include "GraphicsEngine.h"


PixelShader::PixelShader()
{
}

void PixelShader::release()
{
	ps->Release();
	delete this;
}

bool PixelShader::init(const void* shader_byte_code, size_t byte_code_size)
{
	if (!SUCCEEDED(GraphicsEngine::get()->m_d3d_device->CreatePixelShader(shader_byte_code, byte_code_size, nullptr, &ps)))
		return false;

	return true;
}



PixelShader::~PixelShader()
{
}