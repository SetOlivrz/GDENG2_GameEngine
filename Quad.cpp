#include "Quad.h"

Quad::Quad()
{
}

__declspec(align(16))
struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	unsigned int m_time;
};


void Quad::initialize(VertexClass::vertex v[4], void* shaderByteCode, size_t sizeShader)
{
	for (size_t i = 0; i < 4; i++)
	{
		list[i] = v[i];
	}

	UINT size_list = ARRAYSIZE(list);


	m_vb = GraphicsEngine::get()->createVertexBuffer();

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	m_vb->load(list, sizeof(VertexClass::vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();


	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();

	constant cc;
	cc.m_time = 0;

	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));
}

Quad::~Quad()
{
}

void Quad::drawQuad()
{


	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);


	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	// FINALLY DRAW THE TRIANGLE
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
}

void Quad::release()
{
	m_vb->release();
	m_vs->release();
	m_ps->release();
}

void Quad::update(RECT window)
{
	//m_angle += 0.1 * EngineTime::getTimerValue();
	constant cc;
	cc.m_time =GetTickCount();

	Matrix4x4 holder;
	cc.m_world.setScale(Vector3D(scale[0], scale[1], scale[2]));
	holder.setTranslation(Vector3D(translation[0], translation[1], translation[2]));
	//holder.setScale(Vector3D(scale[0], scale[1], scale[2]));

	cc.m_world *= holder;
	cc.m_view.setIdentity();
	cc.m_proj.setOrthoLH( (window.right - window.left) / 400.0f, (window.bottom - window.top) / 400.0f, -4.0f, 4.0f );

	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);




}

void Quad::resetPosition()
{
	for (size_t i = 0; i < 3; i++)
	{
		translation[i] = 0.0f;
	}
}

void Quad::resetScale()
{
	for (size_t i = 0; i < 3; i++)
	{
		scale[i] = 1.0f;
		
	}
	std::cout << "Reset scale";
}


