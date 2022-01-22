#include <map>

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

#include "../Input/dinput8.h"


namespace ui
{
	bool Initialized = false;
	bool InFrame = false;



    void Initialize(HWND Wnd, ID3D11Device *Device, ID3D11DeviceContext *DeviceContext)
    {
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		//io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleFonts;
		//io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.MouseDrawCursor = true;

		ImGui_ImplWin32_Init(Wnd);
        ImGui_ImplDX11_Init(Device, DeviceContext);

		ImGui::StyleColorsDark();
		ImGui::GetStyle().ChildRounding = 0.0f;
		ImGui::GetStyle().FrameRounding = 0.0f;
		ImGui::GetStyle().GrabRounding = 0.0f;
		ImGui::GetStyle().PopupRounding = 0.0f;
		ImGui::GetStyle().ScrollbarRounding = 0.0f;
		ImGui::GetStyle().WindowRounding = 0.0f;

		Initialized = true;
    }

    void HandleInput(HWND Wnd, UINT Msg, WPARAM wParam, LPARAM lParam)
    {
		ImGui_ImplWin32_WndProcHandler(Wnd, Msg, wParam, lParam);
    }

	bool IsMouseDragging()
	{
		if (!Initialized)
			return false;

		return ImGui::IsMouseDragging(ImGuiMouseButton_Left);
	}

	void BeginFrame()
	{
		ZoneScopedN("ui::BeginFrame");

		InFrame = true;
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		// Draw a fullscreen overlay that renders over the game but not other menus
		ImGui::SetNextWindowPos(ImVec2(-1000.0f, -1000.0f));
		ImGui::SetNextWindowSize(ImVec2(1.0f, 1.0f));
		ImGui::Begin("##InvisiblePreOverlay", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoNav);
		ImGui::GetWindowDrawList()->PushClipRectFullScreen();
	}

    void EndFrame()
    {
		ZoneScopedN("ui::EndFrame");

		if (!InFrame)
			return;

		// ##InvisiblePreOverlay
		ImGui::GetWindowDrawList()->PopClipRect();
		ImGui::End();

		// Finally present everything to the screen
        ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
    }
}
