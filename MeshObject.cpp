#include "MeshObject.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "EngineTime.h"
#include "SceneCameraHandler.h"

#include "SwapChain.h"

MeshObject::MeshObject(string name, void* shaderByteCode, size_t sizeShader, Mesh* mesh) :AGameObject(name)
{
	this->meshData = mesh;
	//m_world_cam.setTranslation(Vector3D(0, 0, -2));
	//m_world_cam = SceneCameraHandler::getInstance()->getSceneCameraViewMatrix();
	//world_cam = SceneCameraHandler::getInstance()->getSceneCameraWorldCamMatrix();

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


	// INDEX BUFFER
	indexBuffer = meshData->getIndexBuffer();
	//indexBuffer->load(index_list, ARRAYSIZE(index_list));

	// VERTEX SHADER
	GraphicsEngine::getInstance()->getRenderSystem()->compileVertexShader(L"TVertexShader.hlsl", "tvsmain", &shaderByteCode, &sizeShader);
	vertexShader = GraphicsEngine::getInstance()->getRenderSystem()->createVertexShader(shaderByteCode, sizeShader);

	// VERTEX BUFFER
	vertexBuffer = meshData->getVertexBuffer();
	//vertexBuffer->load(quadList, sizeof(Vertex), ARRAYSIZE(quadList), shaderByteCode, sizeShader);

	GraphicsEngine::getInstance()->getRenderSystem()->releaseCompiledShader();

	// PIXEL SHADER
	GraphicsEngine::getInstance()->getRenderSystem()->compilePixelShader(L"TPixelShader.hlsl", "tpsmain", &shaderByteCode, &sizeShader);
	pixelShader = GraphicsEngine::getInstance()->getRenderSystem()->createPixelShader(shaderByteCode, sizeShader);
	GraphicsEngine::getInstance()->getRenderSystem()->releaseCompiledShader();

	// CONSTANT BUFFER
	Constant cc;
	//cc.m_time = 0;

	constantBuffer = GraphicsEngine::getInstance()->getRenderSystem()->createConstantBuffer(&cc, sizeof(Constant));
}

MeshObject::~MeshObject()
{
	AGameObject::~AGameObject();
}

void MeshObject::update(float deltaTime)
{
	this->ticks += deltaTime;
	this->deltaTime = deltaTime;
}

void MeshObject::draw(int width, int height)
{
	if (ticks >= animationInterval)
	{
		isIncreasing = !isIncreasing;
		ticks = 0;
	}

	if (isIncreasing)
	{
		rotFactor += deltaTime;
	}
	else
	{
		rotFactor -= deltaTime;
	}

	GraphicsEngine* graphEngine = GraphicsEngine::getInstance();
	DeviceContext* deviceContext = GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext();

	Constant cc;
	Matrix4x4 temp;
	temp.setIdentity();

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

	xMatrix.setRotationZ(rotation.m_x);
	yMatrix.setRotationX(rotation.m_y);
	zMatrix.setRotationY(rotation.m_z);

	rotMatrix.setIdentity();

	rotMatrix *= xMatrix;
	rotMatrix *= yMatrix;
	rotMatrix *= zMatrix;

	// APPLICATION
	temp *= scaleMatrix;
	temp *= rotMatrix;
	temp *= translationMatrix;

	cc.worldMatrix = temp;

	//CAMERA
	cc.viewMatrix = SceneCameraHandler::getInstance()->getSceneCameraViewMatrix();

	//cc.projMatrix.setOrthoLH(width / 400.0f, height / 400.0f, -4.0f, 4.0f);
	float aspectRatio = (float)width / (float)height;
	cc.projMatrix.setPerspectiveFovLH(aspectRatio, aspectRatio, 0.1f, 1000.0f);

	constantBuffer->update(GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext(), &cc);

	// SET CONSTANT BUFFER
	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(vertexShader, constantBuffer);
	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(pixelShader, constantBuffer);


	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(vertexShader);
	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(pixelShader);

	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setTexture(pixelShader, this->myTexture);


	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(meshData->getVertexBuffer());
	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(meshData->getIndexBuffer());


	// FINALLY DRAW THE TRIANGLE
	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->drawIndexedTriangleList(meshData->getIndexBuffer()->getSizeIndexList(), 0, 0);
}

void MeshObject::setTexture(Texture* texture)
{
	this->myTexture = texture;
}


