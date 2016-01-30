#include "unifox_engine.h"

class GameState
{

};

LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, Msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	using window = ufo::window<GameState>;

	window::Instance().SetWindow(hInstance, WndProc, L"test", { 0, 0, 500, 500 });
	window::Instance().Initialize2D();
	return window::Instance().Run();
}