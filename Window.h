#pragma once
#include <Windows.h>


class Window
{
	public:
		Window();


		//Initialize window
		bool init();
		bool broadcast();

		//Release window
		bool release();
		bool isRun();

		//event
		virtual void onCreate() =0;
		virtual void onUpdate() = 0;
		virtual void onDestroy();

		~Window();


	protected: 
		HWND m_hwnd;
		bool m_is_run;

};

