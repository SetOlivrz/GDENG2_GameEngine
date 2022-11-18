#pragma once
#include <d3d11.h>
#include "Prerequisites.h"
#include "RenderSystem.h"
#include "TextureManager.h"
#include "MeshManager.h"


class GraphicsEngine
{
private:
	//Initialize the GraphicsEngine and DirectX 11 Device
	GraphicsEngine();
	//Release all the resources loaded
	~GraphicsEngine();
public:
	RenderSystem* getRenderSystem();
	TextureManager* getTextureManager();
	MeshManager* getMeshManager();
	void getVertexMeshLayoutShaderByteCodeAndSize(void** byte_code, size_t* size);
public:
	static GraphicsEngine* getInstance();
	static void create();
	static void release();
private:
	RenderSystem* renderSystem = nullptr;
	TextureManager* textureManager = nullptr;
	MeshManager* meshManager = nullptr;
	static GraphicsEngine* engineInstance;

	unsigned char m_mesh_layout_byte_code[1024];
	size_t m_mesh_layout_size = 0;
};
