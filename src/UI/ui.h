#pragma once

namespace ui
{

	void Initialize(HWND Wnd, ID3D11Device *Device, ID3D11DeviceContext *DeviceContext);
	void HandleInput(HWND Wnd, UINT Msg, WPARAM wParam, LPARAM lParam);
	bool IsMouseDragging();

	void BeginFrame();
	void EndFrame();
}
