#pragma once
#include "AUIScreen.h"

class UIManager;
class ColorPickerScreen : public AUIScreen
{
private:
	ColorPickerScreen();
	~ColorPickerScreen();

	virtual void drawUI() override;
	friend class UIManager;

public:
	static bool isOpen;
};


