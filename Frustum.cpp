#include "Frustum.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "EngineTime.h"
#include "SceneCameraHandler.h"
#include "Utils.h"

#include "SwapChain.h"

Frustum::Frustum(string name, void* shaderByteCode, size_t sizeShader) :AGameObject(name)
{
	cam = SceneCameraHandler::getInstance()->getSceneCamera();


	//create buffers for drawing. Vertex data that needs to be drawn are temporarily placed here.
	Vertex fustrumList[] = {
		//X, Y, Z
		//FRONT FACE
		{Vector3D(-1.0f,-1.0f,-1.0f),     Vector3D(1,1,1), Vector3D(1,1,1) },
		{Vector3D(-1.0f,1.0f,-1.0f),      Vector3D(1,1,1), Vector3D(1,1,1) },
		{Vector3D(1.0f,1.0f,-1.0f),       Vector3D(1,1,1), Vector3D(1,1,1) },
		{Vector3D(1.0f,-1.0f,-1.0f),      Vector3D(1,1,1), Vector3D(1,1,1) },

		//BACK FACE
		{Vector3D(1.0f,-1.0f,1.0f),       Vector3D(1,1,1), Vector3D(1,1,1) },
		{Vector3D(1.0f,1.0f,1.0f),        Vector3D(1,1,1), Vector3D(1,1,1) },
		{Vector3D(-1.0f,1.0f,1.0f),       Vector3D(1,1,1), Vector3D(1,1,1) },
		{Vector3D(-1.0f,-1.0f,1.0f),      Vector3D(1,1,1), Vector3D(1,1,1) },
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
	vertexBuffer->load(fustrumList, sizeof(Vertex), ARRAYSIZE(fustrumList), shaderByteCode, sizeShader);

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

Frustum::~Frustum()
{
	this->vertexBuffer->release();
	this->indexBuffer->release();
	this->constantBuffer->release();
	this->pixelShader->release();
	this->vertexShader->release();
	AGameObject::~AGameObject();
}

void Frustum::update(float deltaTime)
{
	this->ticks += deltaTime;
	this->deltaTime = deltaTime;
}

void Frustum::draw(int width, int height)
{
	camera->getFOV();
	// setting up camera
	static float FOV = Utils::radToDeg(camera->getFOV());
	float fovRadians = FOV / 180 * 3.14;
	static float nearZ = 1.0f;
	static float farZ = 10.0f;

	float nearHeight = 2 * tan(fovRadians / 2) * nearZ;
	float farHeight = 2 * tan(fovRadians / 2) * (farZ-nearZ)/2;
	float nearWidth = nearHeight * camera->getAspectRatio();
	float farWidth = farHeight * camera->getAspectRatio();


#pragma region Frustum initialize

	Vector3D nearBL = Vector3D(-(nearWidth * 0.5), (-nearHeight * 0.5), nearZ/2);
	Vector3D nearBR = Vector3D((nearWidth * 0.5), (-nearHeight * 0.5), nearZ/2);
	Vector3D nearTL = Vector3D((-nearWidth * 0.5), (nearHeight * 0.5), nearZ/2);
	Vector3D nearTR = Vector3D((nearWidth * 0.5), (nearHeight * 0.5), nearZ/2);

	Vector3D farBL = Vector3D(-(farWidth * 0.5), (-farHeight * 0.5), (farZ-nearZ)/2);
	Vector3D farBR = Vector3D((farWidth * 0.5), (-farHeight * 0.5), (farZ-nearZ) /2);
	Vector3D farTL = Vector3D((-farWidth * 0.5), (farHeight * 0.5), (farZ-nearZ) /2);
	Vector3D farTR = Vector3D((farWidth * 0.5), (farHeight * 0.5), (farZ-nearZ) /2);


	//create buffers for drawing. Vertex data that needs to be drawn are temporarily placed here.
	Vertex fustrumList[] = {
		//X, Y, Z
		//FRONT FACE
		{nearBL, Vector3D(1,1,1), Vector3D(1,1,1) },//NBL
		{nearTL, Vector3D(1,1,1), Vector3D(1,1,1) },//NTL
		{nearTR, Vector3D(1,1,1), Vector3D(1,1,1) },//NTR
		{nearBR, Vector3D(1,1,1), Vector3D(1,1,1) },//NBR

		//BACK FACE
		{farBR, Vector3D(1,1,1), Vector3D(1,1,1) },//FBR
		{farTR, Vector3D(1,1,1), Vector3D(1,1,1) },//FTR
		{farTL, Vector3D(1,1,1), Vector3D(1,1,1) },//FTL
		{farBL, Vector3D(1,1,1), Vector3D(1,1,1) },//FBL
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

	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;

	// INDEX BUFFER
	//indexBuffer = GraphicsEngine::get()->createIndexBuffer();
	indexBuffer->load(index_list, ARRAYSIZE(index_list));

	// VERTEX SHADER
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
	vertexShader = GraphicsEngine::get()->createVertexShader(shaderByteCode, sizeShader);

	// VERTEX BUFFER
	//vertexBuffer = GraphicsEngine::get()->createVertexBuffer();
	vertexBuffer->load(fustrumList, sizeof(Vertex), ARRAYSIZE(fustrumList), shaderByteCode, sizeShader);

	GraphicsEngine::get()->releaseCompiledShader();

	// PIXEL SHADER
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shaderByteCode, &sizeShader);
	pixelShader = GraphicsEngine::get()->createPixelShader(shaderByteCode, sizeShader);
	GraphicsEngine::get()->releaseCompiledShader();

	// CONSTANT BUFFER
	Constant cc;
	cc.m_time = 0;

	//constantBuffer = GraphicsEngine::get()->createConstantBuffer();
	constantBuffer->load(&cc, sizeof(Constant));

#pragma endregion Frustum initalize


	GraphicsEngine* graphEngine = GraphicsEngine::get();
	DeviceContext* deviceContext = GraphicsEngine::get()->getImmediateDeviceContext();

	//Constant cc;
	Matrix4x4 temp;
	temp.setIdentity();


	float fov = camera->getFOV();
	float asp = camera->getAspectRatio();
	float zNear = camera->getNearZ();
	float zFar = camera->getFarZ();
	float zRange = zNear - zFar;
	float tanHalfFOV = tanf(camera->getFOV()/2);

	cc.worldMatrix.setIdentity();

	//TRANSLATION
	Matrix4x4 translationMatrix;
	translationMatrix.setIdentity();
	Vector3D pos = camera->getLocalPosition();
	translationMatrix.setTranslation(Vector3D(pos.m_x,pos.m_y,pos.m_z+(zNear/2)));

	//SCALE
	Matrix4x4 scaleMatrix;
	scaleMatrix.setIdentity();
	//scaleMatrix.setScale(Vector3D(1.0f/(tanHalfFOV * asp), (1.0f/tanHalfFOV), (zFar-zNear)));

	//ROTATION
	Matrix4x4 xMatrix, yMatrix, zMatrix, rotMatrix;

	xMatrix.setIdentity();
	yMatrix.setIdentity();
	zMatrix.setIdentity();
	Vector3D rotation = camera->getLocalRotation();

	xMatrix.setRotationZ(rotation.m_z);
	yMatrix.setRotationX(rotation.m_x);
	zMatrix.setRotationY(rotation.m_y);

	rotMatrix.setIdentity();

	rotMatrix *= xMatrix;
	rotMatrix *= yMatrix;
	rotMatrix *= zMatrix;

	// APPLICATION
	//temp *= scaleMatrix;
	temp *= rotMatrix;
	temp *= translationMatrix;
	cc.worldMatrix = temp;


	//CAMERA
	cc.viewMatrix = SceneCameraHandler::getInstance()->getSceneCameraWorldCamMatrix();
	cam = SceneCameraHandler::getInstance()->getSceneCamera();
	//cc.projMatrix.setOrthoLH(width / 400.0f, height / 400.0f, -4.0f, 4.0f);
	cc.projMatrix.setPerspectiveFovLH(cam->getFOV(), cam->getAspectRatio(), cam->getNearZ(), cam->getFarZ());
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

void Frustum::setAnimation(float speed, float interval, bool isSpeeding, float rotFactor)
{
	this->rotFactor = rotFactor;
	this->speed = speed;
	this->animationInterval = interval;
	this->isIncreasing = isSpeeding;
}
