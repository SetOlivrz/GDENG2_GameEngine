#include "Cube.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "EngineTime.h"
#include "SceneCameraHandler.h"

#include "SwapChain.h"

Cube::Cube(string name, void* shaderByteCode, size_t sizeShader) :AGameObject(name)
{
	this->gameObjectType = "Cube";
	//m_world_cam.setTranslation(Vector3D(0, 0, -2));
	m_world_cam = SceneCameraHandler::getInstance()->getSceneCameraViewMatrix();
	world_cam = SceneCameraHandler::getInstance()->getSceneCameraWorldCamMatrix();

	cam = SceneCameraHandler::getInstance()->getSceneCamera();


	//create buffers for drawing. Vertex data that needs to be drawn are temporarily placed here.
	Vertex vertex_list[] = {
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


	//Index Buffer
	this->indexBuffer = GraphicsEngine::getInstance()->getRenderSystem()->createIndexBuffer(index_list, ARRAYSIZE(index_list));

	//Vertex Shader
	GraphicsEngine::getInstance()->getRenderSystem()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
	vertexShader = GraphicsEngine::getInstance()->getRenderSystem()->createVertexShader(shaderByteCode, sizeShader);

	//Vertex Buffer
	this->vertexBuffer = GraphicsEngine::getInstance()->getRenderSystem()->createVertexBuffer(vertex_list, sizeof(Vertex), ARRAYSIZE(vertex_list), shaderByteCode, sizeShader);
	GraphicsEngine::getInstance()->getRenderSystem()->releaseCompiledShader();

	//Pixel Shader
	GraphicsEngine::getInstance()->getRenderSystem()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shaderByteCode, &sizeShader);
	pixelShader = GraphicsEngine::getInstance()->getRenderSystem()->createPixelShader(shaderByteCode, sizeShader);
	GraphicsEngine::getInstance()->getRenderSystem()->releaseCompiledShader();

	//Create constant buffer
	Constant cbData = {};
	cbData.m_time = 0;
	this->constantBuffer = GraphicsEngine::getInstance()->getRenderSystem()->createConstantBuffer(&cbData, sizeof(Constant));

}

Cube::~Cube()
{
	AGameObject::~AGameObject();
}

void Cube::update(float deltaTime)
{
	this->ticks += deltaTime;
	this->deltaTime = deltaTime;
}

void Cube::draw(int width, int height)
{

	GraphicsEngine* graphEngine = GraphicsEngine::getInstance();
	DeviceContext* deviceContext = GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext();

	Constant cc;
	Matrix4x4 temp;
	temp.setIdentity();

	if (!overwriteMatrix)
	{
		//TRANSLATION
		Matrix4x4 translationMatrix;
		translationMatrix.setIdentity();
		translationMatrix.setTranslation(this->getLocalPosition());

		//SCALE
		Matrix4x4 scaleMatrix;
		scaleMatrix.setIdentity();
		scaleMatrix.setScale(this->getLocalScale());

		//ROTATION
		Matrix4x4 xMatrix, yMatrix, zMatrix, rotMatrix;

		xMatrix.setIdentity();
		yMatrix.setIdentity();
		zMatrix.setIdentity();
		Vector3D rotation = this->getLocalRotation();

		xMatrix.setRotationX(rotation.m_x);
		yMatrix.setRotationY(rotation.m_y);
		zMatrix.setRotationZ(rotation.m_z);

		rotMatrix.setIdentity();

		rotMatrix *= xMatrix;
		rotMatrix *= yMatrix;
		rotMatrix *= zMatrix;

		// APPLICATION
		temp *= scaleMatrix;
		temp *= rotMatrix;
		temp *= translationMatrix;

		cc.worldMatrix = temp;
	}
	else
	{
		cc.worldMatrix = this->localMatrix;
	}

	//CAMERA
	cc.viewMatrix = SceneCameraHandler::getInstance()->getSceneCameraViewMatrix();

	//cc.projMatrix.setOrthoLH(width / 400.0f, height / 400.0f, -4.0f, 4.0f);
	float aspectRatio = (float)width / (float)height;
	cc.projMatrix.setPerspectiveFovLH(aspectRatio, aspectRatio, 0.1f, 1000.0f);

	this->constantBuffer->update(deviceContext, &cc);

	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(vertexShader);
	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(pixelShader);

	//SET DEFAULT BUFFER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	deviceContext->setConstantBuffer(vertexShader, this->constantBuffer);
	deviceContext->setConstantBuffer(pixelShader, this->constantBuffer);

	deviceContext->setIndexBuffer(this->indexBuffer);
	deviceContext->setVertexBuffer(this->vertexBuffer);

	deviceContext->drawIndexedTriangleList(this->indexBuffer->getSizeIndexList(), 0, 0);
}

void Cube::setAnimation(float speed, float interval, bool isSpeeding, float rotFactor)
{
	this->rotFactor = rotFactor;
	this->speed = speed;
	this->animationInterval = interval;
	this->isIncreasing = isSpeeding;
}
