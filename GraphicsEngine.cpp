#include "GraphicsEngine.h"

GraphicsEngine::GraphicsEngine()
{
}

bool GraphicsEngine::init()
{
	//driver types best - worst
	D3D_DRIVER_TYPE driver_types[] =
	{
		D3D_DRIVER_TYPE_HARDWARE, // GPU
		D3D_DRIVER_TYPE_WARP,     // CPU
		D3D_DRIVER_TYPE_REFERENCE
	};

	// get size of vector array drivers
	UINT num_driver_types = ARRAYSIZE(driver_types);

	//indicate which feature of d11 we want to use 
	D3D_FEATURE_LEVEL feature_levels[] =
	{
		D3D_FEATURE_LEVEL_11_0
	};
	 
	// get size of vector array drivers
	UINT num_feature_levels = ARRAYSIZE(feature_levels);

	HRESULT res = 0;

	// loop that scans the driver types
	for (UINT driver_type_index = 0; driver_type_index < num_driver_types;)
	{
		res = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL, feature_levels,
			num_feature_levels, D3D11_SDK_VERSION, &m_d3d_device, &m_feature_level, &m_imm_context);

		// break the loop when device creation succeeds
		if (SUCCEEDED(res))
		{
			break;
		}

		++driver_type_index;
	}

	// if failed creation return false
	if (FAILED(res))
	{
		return false;
	}

    return true;
}

bool GraphicsEngine::release()
{
	//release all resources created
	m_imm_context->Release();
	m_d3d_device->Release();
	return true;
}

GraphicsEngine::~GraphicsEngine()
{
}

GraphicsEngine* GraphicsEngine::get()
{
	//return the same address of an instabnce
	static GraphicsEngine engine;
	return &engine;
}
