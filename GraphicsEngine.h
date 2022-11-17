#pragma once
#include <d3d11.h>
#include "TextureManager.h"

class SwapChain;
class DeviceContext;
class VertexBuffer;
class TVertexBuffer;

class ConstantBuffer;
class VertexShader;
class PixelShader;
class AppWindow;
class DebugWindow;
class IndexBuffer;
class Texture;
class Resource;



class GraphicsEngine
{
public:
	GraphicsEngine();
	//Initialize the GraphicsEngine and DirectX 11 Device
	bool init();
	//Release all the resources loaded
	bool release();
	~GraphicsEngine();
public:
	SwapChain* createSwapChain();
	DeviceContext* getImmediateDeviceContext();
	ID3D11Device* getDevice();
	ID3D11DeviceContext* getDeviceContext();
	TextureManager* getTextureManager();


	//Buffers
	VertexBuffer* createVertexBuffer();
	TVertexBuffer* createTVertexBuffer();
	IndexBuffer* createIndexBuffer();
	ConstantBuffer* createConstantBuffer();

	//Shaders
	VertexShader* createVertexShader(const void* shader_byte_code, size_t byte_code_size);
	PixelShader* createPixelShader(const void* shader_byte_code, size_t byte_code_size);
public:
	bool compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	bool compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);

	void releaseCompiledShader();

public:
	static GraphicsEngine* get();

private:
	DeviceContext* m_imm_device_context;
private:
	ID3D11Device* m_d3d_device;
	D3D_FEATURE_LEVEL m_feature_level;
private:
	IDXGIDevice* m_dxgi_device;
	IDXGIAdapter* m_dxgi_adapter;
	IDXGIFactory* m_dxgi_factory;
	ID3D11DeviceContext* m_imm_context;

private:
	ID3DBlob* m_blob = nullptr;
	ID3DBlob* m_vsblob = nullptr;
	ID3DBlob* m_psblob = nullptr;
	ID3D11VertexShader* m_vs = nullptr;
	ID3D11PixelShader* m_ps = nullptr;

	TextureManager* textureManager = nullptr;
private:
	friend class SwapChain;
	friend class VertexBuffer;
	friend class ConstantBuffer;
	friend class VertexShader;
	friend class TVertexBuffer;

	friend class PixelShader;
	friend class AppWindow;
	friend class DebugWindow;
	friend class IndexBuffer;



};