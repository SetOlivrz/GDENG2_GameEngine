#include "Cube.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "EngineTime.h"
#include "SceneCameraHandler.h"

#include "SwapChain.h"

Cube::Cube(string name, void* shaderByteCode, size_t sizeShader) :AGameObject(name)
{
	//m_world_cam.setTranslation(Vector3D(0, 0, -2));
	m_world_cam = SceneCameraHandler::getInstance()->getSceneCameraViewMatrix();
	cam = SceneCameraHandler::getInstance()->getSceneCamera();


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

	this->setScale(Vector3D(1, 1, 1));
	this->setPosition(Vector3D(0, 0, 0));

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

	GraphicsEngine* graphEngine = GraphicsEngine::get();
	DeviceContext* deviceContext = GraphicsEngine::get()->getImmediateDeviceContext();

	
	Constant cc;
	Matrix4x4 temp;
	cc.worldMatrix.setIdentity();

	Matrix4x4 world_cam;
	world_cam.setIdentity();

	temp.setIdentity();
	temp.setRotationX(cam->getLocalRotation().m_x);
	world_cam *= temp;

	temp.setIdentity();
	temp.setRotationY(cam->getLocalRotation().m_y);
	world_cam *= temp;

	

	Vector3D new_pos = m_world_cam.getTranslation() + (world_cam.getZDirection() * (cam->forward * 0.1f));

	new_pos = new_pos + (world_cam.getXDirection() * (cam->rightward * 0.1f));

	world_cam.setTranslation(new_pos);

	std::cout << "cx: " << new_pos.m_x << " cy: " << new_pos.m_y << " cz:" << new_pos.m_z << " \n";

	std::cout << "x: " << cam->getViewMatrix().getTranslation().m_x << " y: " << cam->getViewMatrix().getTranslation().m_y << " z:" << cam->getViewMatrix().getTranslation().m_z << " \n";
	std::cout << "cx: " << cam->getLocalPosition().m_x << " cy: " << cam->getLocalPosition().m_y << " cz:" << cam->getLocalPosition().m_z << " \n";
	m_world_cam = world_cam;

	

	world_cam.inverse();

	cc.viewMatrix = world_cam;
	//cc.projMatrix.setOrthoLH(width / 400.0f, height / 400.0f, -4.0f, 4.0f);
	float aspectRatio = (float)width / (float)height;
	cc.projMatrix.setPerspectiveFovLH(aspectRatio, aspectRatio, 0.1f, 1000.0f);

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
	//this->animationInterval = interval;
	//this->isIncreasing = isSpeeding;
}
