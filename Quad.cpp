#include "Quad.h"

Quad::Quad()
{
}

__declspec(align(16))
struct Constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	unsigned int m_time;
};


void Quad::initialize(VertexClass::Vertex v[8], void* shaderByteCode, size_t sizeShader)
{
	for (size_t i = 0; i < 8; i++)
	{
		list[i] = v[i];
	}

	UINT size_list = ARRAYSIZE(list);


	m_vb = GraphicsEngine::get()->createVertexBuffer();
	
	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		1,6,5,
		5,2,1,
		//BOTTOM SIDE
		7,0,3,
		3,4,7,
		//RIGHT SIDE
		3,2,5,
		5,4,3,
		//LEFT SIDE
		7,6,1,
		1,0,7
	};


	m_ib = GraphicsEngine::get()->createIndexBuffer();
	UINT size_index_list = ARRAYSIZE(index_list);

	m_ib->load(index_list, size_index_list);


	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	m_vb->load(list, sizeof(VertexClass::Vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();


	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();

	Constant cc;
	cc.m_time = 0;

	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(Constant));
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
	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(m_ib);


	// FINALLY DRAW THE TRIANGLE
	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(),0, 0);
}

void Quad::release()
{
	m_ib->release();
	m_cb->release();
	m_vb->release();
	m_vs->release();
	m_ps->release();
}

void Quad::update(RECT window)
{
	//m_angle += 0.1 * EngineTime::getTimerValue();
	Constant cc;
	cc.m_time = GetTickCount();

	Matrix4x4 temp;
	cc.m_world.setScale(Vector3D(scale[0], scale[1], scale[2]));
	temp.setTranslation(Vector3D(translation[0], translation[1], translation[2]));
	////holder.setScale(Vector3D(scale[0], scale[1], scale[2]));


	temp.setIdentity();
	temp.setRotationZ(EngineTime::getTimerValue());
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationY(EngineTime::getTimerValue());
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationX(EngineTime::getTimerValue());
	cc.m_world *= temp;


	cc.m_view.setIdentity();
	cc.m_proj.setOrthoLH( (window.right - window.left) / 400.0f, 
						  (window.bottom - window.top) / 400.0f, 
						  -4.0f, 4.0f );

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


