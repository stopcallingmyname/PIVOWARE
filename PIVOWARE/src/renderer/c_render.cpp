#include "includes.h"

CRender::CRender() {}
CRender::~CRender() {}

static void BeginScene()
{
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4());
	ImGui::PushStyleColor(ImGuiCol_Border, ImVec4());
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2());

	ImGui::SetNextWindowPos(ImVec2(), ImGuiCond_Always);
	ImGui::SetNextWindowSize(GImGui->IO.DisplaySize, ImGuiCond_Always);

	ImGui::Begin(xorstr_("##renderscene"), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoFocusOnAppearing);

	ImGui::PopStyleColor(2);
	ImGui::PopStyleVar();
}

static void EndScene()
{
	GImGui->CurrentWindow->DrawList->PushClipRectFullScreen();

	ImGui::End();
}

void CRender::RenderScene(std::function<void()> render_function) {
	BeginScene();

	render_function();

	EndScene();
}

std::unique_ptr<CRender> g_pRender;