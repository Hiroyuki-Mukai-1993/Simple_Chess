#include <DxLib.h>
#include"MainManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (DxLib_Init() == -1)	return -1;

	MainManager* main = new MainManager;
	main->MainLoop();
	delete main;

	DxLib_End();

	return 0;
}