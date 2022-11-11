#pragma once
#include "AUIScreen.h"
#include "PixelShader.h"

class UIManager;
class EditorScreen : public AUIScreen
{
private:
	EditorScreen();
	~EditorScreen();

	virtual void drawUI() override;
	friend class UIManager;

public: 
	int my_image_width = 0;
	int my_image_height = 0;
	ID3D11ShaderResourceView* my_texture = NULL;
};

