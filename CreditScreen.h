#pragma once
#include "AUIScreen.h"


class UIManager;
class CreditScreen : public AUIScreen
{
private:
	CreditScreen();
	~CreditScreen();

	virtual void drawUI() override;
	friend class UIManager;

public:
	static bool isOpen;
};


