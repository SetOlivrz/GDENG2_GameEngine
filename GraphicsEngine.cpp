#include "GraphicsEngine.h"
#include "RenderSystem.h"
#include <exception>

GraphicsEngine* GraphicsEngine::engineInstance = nullptr;

GraphicsEngine::GraphicsEngine()
{
	try
	{
		renderSystem = new RenderSystem();
	}
	catch (...) { throw std::exception("RenderSystem not created successfully"); }

	try
	{
		textureManager = new TextureManager();
	}
	catch (...) { throw std::exception("TextureManager not created successfully"); }

	try
	{
		meshManager = new MeshManager();
	}
	catch (...) { throw std::exception("MeshManager not created successfully"); }


	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	renderSystem->compileVertexShader(L"VertexMeshLayoutShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	::memcpy(m_mesh_layout_byte_code, shader_byte_code, size_shader);
	m_mesh_layout_size = size_shader;
	renderSystem->releaseCompiledShader();

}

RenderSystem* GraphicsEngine::getRenderSystem()
{
	return renderSystem;
}

TextureManager* GraphicsEngine::getTextureManager()
{
	return textureManager;
}

MeshManager* GraphicsEngine::getMeshManager()
{
	return meshManager;
}

void GraphicsEngine::getVertexMeshLayoutShaderByteCodeAndSize(void** byte_code, size_t* size)
{
	*byte_code = m_mesh_layout_byte_code;
	*size = m_mesh_layout_size;
}

GraphicsEngine::~GraphicsEngine()
{
	GraphicsEngine::engineInstance = nullptr;
	delete meshManager;
	delete textureManager;
	delete renderSystem;
}

void GraphicsEngine::create()
{
	if (GraphicsEngine::engineInstance) throw std::exception("Graphics Engine already created");
	GraphicsEngine::engineInstance = new GraphicsEngine();
}

void GraphicsEngine::release()
{
	if (!GraphicsEngine::engineInstance) return;
	delete GraphicsEngine::engineInstance;
}

GraphicsEngine* GraphicsEngine::getInstance()
{
	return engineInstance;
}