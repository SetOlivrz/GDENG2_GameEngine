#include "Cube.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "EngineTime.h"

#include "SwapChain.h"

Cube::Cube(string name, void* shaderByteCode, size_t sizeShader) :AGameObject(name)
{
	//create buffers for drawing. Vertex data that needs to be drawn are temporarily placed here.
	Vertex quadList[] = {
		//X, Y, Z
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,0,.5), Vector3D(0.2f,0,0) },
		{Vector3D(-0.5f,0.5f,-0.5f),     Vector3D(1,.5,1), Vector3D(0.2f,0.2f,0) },
		{Vector3D(0.5f,0.5f,-0.5f),      Vector3D(1,.5,.5), Vector3D(0.2f,0.2f,0) },
		{Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,0,.5), Vector3D(0.2f,0,0) },

		//BACK FACE
		{Vector3D(0.5f,-0.5f,0.5f),      Vector3D(1,0,1), Vector3D(0,0.2f,0) },
		{Vector3D(0.5f,0.5f,0.5f),       Vector3D(1,.5,.5), Vector3D(0,0.2f,0.2f) },
		{Vector3D(-0.5f,0.5f,0.5f),      Vector3D(1,0,.5), Vector3D(0,0.2f,0.2f) },
		{Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(1,.5,1), Vector3D(0,0.2f,0) },
	};

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

	// INDEX BUFFER
	indexBuffer = GraphicsEngine::get()->createIndexBuffer();
	indexBuffer->load(index_list, ARRAYSIZE(index_list));

	// VERTEX SHADER
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
	vertexShader = GraphicsEngine::get()->createVertexShader(shaderByteCode, sizeShader);

	// VERTEX BUFFER
	vertexBuffer = GraphicsEngine::get()->createVertexBuffer();
	vertexBuffer->load(quadList, sizeof(Vertex), ARRAYSIZE(quadList), shaderByteCode, sizeShader);

	GraphicsEngine::get()->releaseCompiledShader();

	// PIXEL SHADER
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shaderByteCode, &sizeShader);
	pixelShader = GraphicsEngine::get()->createPixelShader(shaderByteCode, sizeShader);
	GraphicsEngine::get()->releaseCompiledShader();

	// CONSTANT BUFFER
	Constant cc;
	cc.m_time = 0;

	constantBuffer = GraphicsEngine::get()->createConstantBuffer();
	constantBuffer->load(&cc, sizeof(Constant));
}

Cube::~Cube()
{
	this->vertexBuffer->release();
	this->indexBuffer->release();
	this->constantBuffer->release();
	this->pixelShader->release();
	this->vertexShader->release();
	AGameObject::~AGameObject();
}

void Cube::update(float deltaTime)
{
	this->ticks += deltaTime;
	this->deltaTime = deltaTime;
}

void Cube::draw(int width, int height)
{
	//if (ticks >= animationInterval)
	//{
	//	isIncreasing = !isIncreasing;
	//	ticks = 0;
	//}

	//if (isIncreasing)
	//{
	//	rotation += deltaTime;
	//}
	//else
	//{
	//	rotation -= deltaTime;
	//}

	GraphicsEngine* graphEngine = GraphicsEngine::get();
	DeviceContext* deviceContext = GraphicsEngine::get()->getImmediateDeviceContext();

	Constant cc;
	//cc.m_time = GetTickCount();

	// SCALE
	Matrix4x4 temp;
	cc.worldMatrix.setScale(Vector3D(.25, .25, .25));

	// ROTATION Z
	temp.setIdentity();
	temp.setRotationZ(0.0);
	cc.worldMatrix *= temp;

	// ROTATION Y
	temp.setIdentity();
	temp.setRotationY(rotation.m_y);
	cc.worldMatrix *= temp;

	// ROTATION X
	temp.setIdentity();
	temp.setRotationX(rotation.m_x);
	cc.worldMatrix *= temp;

	// TRANSLATION
	temp.setIdentity();
	temp.setTranslation(this->localPosition);
	
	// APPLICATION
	cc.worldMatrix *= temp;

	cc.viewMatrix.setIdentity();
	cc.projMatrix.setOrthoLH(width / 400.0f, height/ 400.0f, -4.0f, 4.0f);

	constantBuffer->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);

	// SET CONSTANT BUFFER
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(vertexShader, constantBuffer);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(pixelShader, constantBuffer);

	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(vertexShader);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(pixelShader);


	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(vertexBuffer);
	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(indexBuffer);


	// FINALLY DRAW THE TRIANGLE
	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(indexBuffer->getSizeIndexList(), 0, 0);
}

void Cube::setAnimation(float speed, float interval, bool isSpeeding)
{
	this->speed = speed;
	this->animationInterval = interval;
	this->isIncreasing = isSpeeding;
}


void Cube::resetPosition()
{
	translation = Vector3D(0, 0, 0);
}

void Cube::resetScale()
{
	scale = Vector3D(1, 1, 1);

}

void Cube::setScale(Vector3D v)
{
	this->scale = v;
}

void Cube::setTranslation(Vector3D v)
{
	this->translation = v;

}

void Cube::setRotation(Vector3D v)
{
	this->rotation = v;

}

Vector3D Cube::getScale()
{
	return scale;
}

Vector3D Cube::getTranslation()
{
	return translation;
}

Vector3D Cube::getRotation()
{
	return rotation;
}

