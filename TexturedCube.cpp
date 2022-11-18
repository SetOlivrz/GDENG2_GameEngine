#include "TexturedCube.h"
#include <iostream>
#include "DeviceContext.h"
#include "EngineTime.h"
#include "GraphicsEngine.h"
#include "SceneCameraHandler.h"

//Utils* utils = new Utils();
TexturedCube::TexturedCube(string name, void* shaderByteCode, size_t sizeShader) :AGameObject(name)
{
	Vector3D position_list[] =
	{
		{ Vector3D(-0.5f,-0.5f,-0.5f)},
		{ Vector3D(-0.5f,0.5f,-0.5f) },
		{ Vector3D(0.5f,0.5f,-0.5f) },
		{ Vector3D(0.5f,-0.5f,-0.5f)},

		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.5f) },
		{ Vector3D(0.5f,0.5f,0.5f) },
		{ Vector3D(-0.5f,0.5f,0.5f)},
		{ Vector3D(-0.5f,-0.5f,0.5f) }
	};


	Vertex vertex_list_gizmo[] =
	{
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,-0.5f),	Vector3D(1,0,0), Vector3D(0.2f,0,0) },
		{Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(1,0,0), Vector3D(0.2f,0.2f,0) },
		{ Vector3D(0.5f,0.5f,-0.5f),     Vector3D(1,0,0),  Vector3D(0.2f,0.2f,0) },
		{ Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,0,0), Vector3D(0.2f,0,0) },

		//BACK FACE
		{Vector3D(0.5f,-0.5f,0.5f),	Vector3D(1,0,0), Vector3D(0,0.2f,0) },
		{Vector3D(0.5f,0.5f,0.5f),    Vector3D(1,0,0), Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.5f,0.5f,0.5f),     Vector3D(1,0,0),  Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(1,0,0), Vector3D(0,0.2f,0) }
	};


	Vector2D texcoord_list[] =
	{
		{ Vector2D(0.0f,0.0f) },
		{ Vector2D(0.0f,1.0f) },
		{ Vector2D(1.0f,0.0f) },
		{ Vector2D(1.0f,1.0f) }
	};

	TVertex vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{ position_list[0],texcoord_list[1] },
		{ position_list[1],texcoord_list[0] },
		{ position_list[2],texcoord_list[2] },
		{ position_list[3],texcoord_list[3] },

		{ position_list[4],texcoord_list[1] },
		{ position_list[5],texcoord_list[0] },
		{ position_list[6],texcoord_list[2] },
		{ position_list[7],texcoord_list[3] },

		{ position_list[1],texcoord_list[1] },
		{ position_list[6],texcoord_list[0] },
		{ position_list[5],texcoord_list[2] },
		{ position_list[2],texcoord_list[3] },

		{ position_list[7],texcoord_list[1] },
		{ position_list[0],texcoord_list[0] },
		{ position_list[3],texcoord_list[2] },
		{ position_list[4],texcoord_list[3] },

		{ position_list[3],texcoord_list[1] },
		{ position_list[2],texcoord_list[0] },
		{ position_list[5],texcoord_list[2] },
		{ position_list[4],texcoord_list[3] },

		{ position_list[7],texcoord_list[1] },
		{ position_list[6],texcoord_list[0] },
		{ position_list[1],texcoord_list[2] },
		{ position_list[0],texcoord_list[3] }

	};


	//UINT size_list = ARRAYSIZE(vertex_list);


	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		8,9,10,
		10,11,8,
		//BOTTOM SIDE
		12,13,14,
		14,15,12,
		//RIGHT SIDE
		16,17,18,
		18,19,16,
		//LEFT SIDE
		20,21,22,
		22,23,20
	};


	//Index Buffer
	this->indexBuffer = GraphicsEngine::getInstance()->getRenderSystem()->createIndexBuffer(index_list, ARRAYSIZE(index_list));
	//this->indexBuffer->load(index_list, ARRAYSIZE(index_list));

	//Vertex Shader
	GraphicsEngine::getInstance()->getRenderSystem()->compileVertexShader(L"TVertexShader.hlsl", "tvsmain", &shaderByteCode, &sizeShader);
	vertexShader = GraphicsEngine::getInstance()->getRenderSystem()->createVertexShader(shaderByteCode, sizeShader);

	//Vertex Buffer
	this->tVertexBuffer = GraphicsEngine::getInstance()->getRenderSystem()->createTVertexBuffer(vertex_list, sizeof(TVertex), ARRAYSIZE(vertex_list), shaderByteCode, sizeShader);	
	GraphicsEngine::getInstance()->getRenderSystem()->releaseCompiledShader();

	//Pixel Shader
	GraphicsEngine::getInstance()->getRenderSystem()->compilePixelShader(L"TPixelShader.hlsl", "tpsmain", &shaderByteCode, &sizeShader);
	pixelShader = GraphicsEngine::getInstance()->getRenderSystem()->createPixelShader(shaderByteCode, sizeShader);
	GraphicsEngine::getInstance()->getRenderSystem()->releaseCompiledShader();

	//Create constant buffer
	Constant cbData = {};
	cbData.m_time = 0;
	this->constantBuffer = GraphicsEngine::getInstance()->getRenderSystem()->createConstantBuffer(&cbData, sizeof(Constant));

	setAnimSpeed(4);
}

TexturedCube::~TexturedCube()
{

}

void TexturedCube::update(float delta_time)
{

}

void TexturedCube::draw(int width, int height)
{
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

	this->constantBuffer->update(deviceContext, &cc);

	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(vertexShader);
	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(pixelShader);

	//SET TEXTURE
	//GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShaderSamplers(0, 1, samplerState);
	//GraphicsEngine::get()->getImmediateDeviceContext()->setShaderResources(0, 1, this->myTexture);
	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setTexture(pixelShader, this->myTexture);



	//SET DEFAULT BUFFER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	deviceContext->setConstantBuffer(vertexShader, this->constantBuffer);
	deviceContext->setConstantBuffer(pixelShader, this->constantBuffer);

	deviceContext->setIndexBuffer(this->indexBuffer);
	deviceContext->setTVertexBuffer(tVertexBuffer);

	deviceContext->drawIndexedTriangleList(this->indexBuffer->getSizeIndexList(), 0, 0);
}


void TexturedCube::setAnimSpeed(float speed)
{
	this->speed = speed;
}


