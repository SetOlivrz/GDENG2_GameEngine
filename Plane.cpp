#include "Plane.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "EngineTime.h"

#include "SwapChain.h"

Plane::Plane(string name, void* shaderByteCode, size_t sizeShader) :AGameObject(name)
{
	//create buffers for drawing. Vertex data that needs to be drawn are temporarily placed here.
	Vertex quadList[] = {
		//X, Y, Z
		//FRONT FACE
		{Vector3D(-0.5f,-0.0f,1),    Vector3D(0,1,1), Vector3D(0.2f,0,0) },
		{Vector3D(-0.5f,0.0f,-1),     Vector3D(0,1,1), Vector3D(0.2f,0.2f,0) },
		{Vector3D(0.5f,-0.0f,1),      Vector3D(1,0,1), Vector3D(0.2f,0.2f,0) },
		{Vector3D(0.5f,0.0,-1),     Vector3D(0,1,1), Vector3D(0.2f,0,0) },
	};

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

Plane::~Plane()
{
	this->vertexBuffer->release();
	this->constantBuffer->release();
	this->pixelShader->release();
	this->vertexShader->release();
	AGameObject::~AGameObject();
}

void Plane::update(float deltaTime)
{
	this->ticks += deltaTime;
	this->deltaTime = deltaTime;
}

void Plane::draw(int width, int height)
{
	if (ticks >= animationInterval)
	{
		isIncreasing = !isIncreasing;
		ticks = 0;
	}

	if (isIncreasing)
	{
		rotation += deltaTime;
	}
	else
	{
		rotation -= deltaTime;
	}

	GraphicsEngine* graphEngine = GraphicsEngine::get();
	DeviceContext* deviceContext = GraphicsEngine::get()->getImmediateDeviceContext();

	Constant cc;
	//cc.m_time = GetTickCount();

	// SCALE
	Matrix4x4 temp;
	cc.worldMatrix.setScale(Vector3D(1, 1, 1));

	// ROTATION Z
	temp.setIdentity();
	temp.setRotationZ(rotation * speed);
	cc.worldMatrix *= temp;

	// ROTATION Y
	temp.setIdentity();
	temp.setRotationY(rotation * speed);
	cc.worldMatrix *= temp;

	// ROTATION X
	temp.setIdentity();
	temp.setRotationX(rotation * speed);
	cc.worldMatrix *= temp;

	// TRANSLATION
	temp.setIdentity();
	temp.setTranslation(this->localPosition);

	// APPLICATION
	cc.worldMatrix *= temp;

	cc.viewMatrix.setIdentity();
	cc.projMatrix.setOrthoLH(width / 400.0f, height / 400.0f, -4.0f, 4.0f);

	constantBuffer->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);

	// SET CONSTANT BUFFER
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(vertexShader, constantBuffer);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(pixelShader, constantBuffer);

	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(vertexShader);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(pixelShader);


	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(vertexBuffer);

	// FINALLY DRAW THE TRIANGLE
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(vertexBuffer->getSizeVertexList(), 0);
}

void Plane::setAnimation(float speed, float interval, bool isSpeeding)
{
	this->speed = speed;
	this->animationInterval = interval;
	this->isIncreasing = isSpeeding;
}

