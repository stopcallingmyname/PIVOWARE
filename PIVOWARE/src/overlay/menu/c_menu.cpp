#include "includes.h"

std::unique_ptr<CMenu> g_pMenu;

CMenu::CMenu()
	: m_pConfigsList(std::make_unique<CConfigsList>())
	, m_bIsOpened(true) {
	CUtils::logger("m_pConfigsList [INIT]");
}

CMenu::~CMenu() {
	m_pConfigsList.reset();
}

bool CMenu::IsOpened() {
	return m_bIsOpened;
}

void CMenu::Open() {
	if (!m_bIsOpened)
		m_bIsOpened = true;
}

void CMenu::Close() {
	if (m_bIsOpened)
		m_bIsOpened = false;
}

void CMenu::Toggle() {
	m_bIsOpened ? Close() : Open();
}

int page = 0;
static float tab_alpha = 0.f; /* */ static float tab_add; /* */ static int active_tab = 0;

void CMenu::Draw() {
	if (!m_bIsOpened)
		return;

	ImGui::GetBackgroundDrawList()->AddRectFilled({ 0, 0 }, ImVec2(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)), IM_COL32(0, 0, 0, 80));

	ImGuiStyle* style = &ImGui::GetStyle();

	ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f), ImGuiCond_Once, ImVec2(0.5f, 0.5f));
	ImGui::SetNextWindowSize(properties::background::size);

	ImGui::Begin("PIVOWARE", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBringToFrontOnFocus);

	const ImVec2& pos = ImGui::GetWindowPos();
	const ImVec2& region = ImGui::GetContentRegionMax();
	const ImVec2& spacing = style->ItemSpacing;

	static float color[4] = { 124 / 255.f, 103 / 255.f, 255 / 255.f, 1.f };
	properties::accent_color = { color[0], color[1], color[2], 1.f };

	ImGui::GetBackgroundDrawList()->AddRectFilled(pos, pos + properties::background::size, ImGui::GetColorU32(properties::background::filling_color), properties::background::rounding);
	ImGui::GetBackgroundDrawList()->AddRectFilled(pos, pos + ImVec2(200.f, properties::background::size.y), ImGui::GetColorU32(properties::tab::border_color), properties::background::rounding, ImDrawFlags_RoundCornersLeft);
	ImGui::GetBackgroundDrawList()->AddLine(pos + ImVec2(200.f, 0.f), pos + ImVec2(200.f, properties::background::size.y), ImGui::GetColorU32(properties::background::stroke_color), 1.f);
	ImGui::GetBackgroundDrawList()->AddRect(pos, pos + properties::background::size, ImGui::GetColorU32(properties::background::stroke_color), properties::background::rounding);

	ImGui::SetCursorPos(ImVec2(10, 10));
	ImGui::BeginGroup();

	std::vector<std::vector<std::string>> tab_columns = {
		{ "c", "b", "f", "o", "e" },
		{ "Aimbot", "Visuals", "Skins", "Configs", "Settings" },
		{ "Shooting is more accur...", "Changing the look and...", "Changing characters, w...", "Function customization...", "Changing the paramet..." },
		{ "Have you switched to the Aimbot tab? You're just crazy!", "Have you switched to the Visuals tab, do you want to get banned?", "You switched to the skins tab, why do you need self-deception??", "You switched over.. And yes, to hell with it, come up with a script yourself.", "You switched over.. And yes, to hell with it, come up with a script yourself." }
	};

	for (int i = 0; i < tab_columns[0].size(); ++i) {

		if (ImGui::Edited::Tab(page == i, tab_columns[0][i].c_str(), tab_columns[1][i].c_str(), tab_columns[2][i].c_str(), ImVec2(180, 50))) {
			//notificationSystem.AddNotification(tab_columns[3][i], 1000);
			page = i;
		}

	}

	ImGui::EndGroup();

	tab_alpha = ImLerp(tab_alpha, (page == active_tab) ? 1.f : 0.f, 15.f * ImGui::GetIO().DeltaTime);
	if (tab_alpha < 0.01f && tab_add < 0.01f) active_tab = page;

	ImGui::SetCursorPos(ImVec2(200, 100 - (tab_alpha * 100)));

	ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab_alpha * style->Alpha);
	{
		switch (active_tab) {
		case 0:
		{
			break;
		}
		case 1:
		{
			static int selected_visuals_type = 0;
			const char* visuals_type[3]{ "Enemy", "Local", "World" };
			const char* skybox_type[4]{ "Default", "Day", "Night", "Wireframe" };

			ImGui::Edited::BeginChild("##Container" + selected_visuals_type, ImVec2((properties::background::size.x - 200) / 2, properties::background::size.y), NULL);
			{
				ImGui::TextColored(ImColor(ImGui::GetColorU32(properties::elements::text_color)), "Select");
				ImGui::Edited::Combo("Type", "Select type", &selected_visuals_type, visuals_type, IM_ARRAYSIZE(visuals_type), 1);
			}
			ImGui::Edited::EndChild();

			switch (selected_visuals_type) {
			case 0:
			{
				ImGui::Edited::BeginChild("##Container" + selected_visuals_type, ImVec2((properties::background::size.x - 200) / 2, properties::background::size.y), NULL);
				{
					ImGui::TextColored(ImColor(ImGui::GetColorU32(properties::elements::text_color)), "Enemy Tab");
				}
				ImGui::Edited::EndChild();

				ImGui::SameLine(0, 0);

				ImGui::Edited::BeginChild("##ContainerSecond" + selected_visuals_type, ImVec2((properties::background::size.x - 200) / 2, properties::background::size.y), NULL);
				{
					ImGui::TextColored(ImColor(ImGui::GetColorU32(properties::elements::text_color)), "Enemy Second Tab");
				}
				ImGui::Edited::EndChild();
				break;
			}
			case 1:
			{
				ImGui::Edited::BeginChild("##Container" + selected_visuals_type, ImVec2((properties::background::size.x - 200) / 2, properties::background::size.y), NULL);
				{
					ImGui::TextColored(ImColor(ImGui::GetColorU32(properties::elements::text_color)), "General");
					ImGui::Edited::Checkbox("Enabled", "Active visuals", &g_Cvars.visuals.local.enable);

					ImGui::TextColored(ImColor(ImGui::GetColorU32(properties::elements::text_color)), "Miscellaneous");
					ImGui::Edited::Checkbox("Shooting Through Walls", "Allows shooting through walls", &g_Cvars.visuals.local.shootig_through_walls);

					if (g_Cvars.visuals.local.enable) {
						ImGui::TextColored(ImColor(ImGui::GetColorU32(properties::elements::text_color)), "Material Properties");
						ImGui::Edited::ColorEdit4(xorstr_("Color"), xorstr_("Change chams color"), g_Cvars.visuals.local.chams_color.data());
					}
				}
				ImGui::Edited::EndChild();

				ImGui::SameLine(0, 0);

				ImGui::Edited::BeginChild("##ContainerSecond" + selected_visuals_type, ImVec2((properties::background::size.x - 200) / 2, properties::background::size.y), NULL);
				{
					ImGui::TextColored(ImColor(ImGui::GetColorU32(properties::elements::text_color)), "Local Second Tab");
				}
				ImGui::Edited::EndChild();
				break;
			}
			case 2:
			{
				ImGui::Edited::BeginChild("##Container" + selected_visuals_type, ImVec2((properties::background::size.x - 200) / 2, properties::background::size.y), NULL);
				{
					ImGui::TextColored(ImColor(ImGui::GetColorU32(properties::elements::text_color)), "General");
					ImGui::Edited::Checkbox("Enabled", "Active visuals", &g_Cvars.visuals.world.enable);

					ImGui::TextColored(ImColor(ImGui::GetColorU32(properties::elements::text_color)), "Environment");
					ImGui::Edited::Checkbox("Fog", "Enable or disable fog in the game", &g_Cvars.visuals.world.fog);
					ImGui::Edited::Combo("Skybox", "Replace current skybox", &g_Cvars.visuals.world.skybox, skybox_type, IM_ARRAYSIZE(skybox_type), 1);

					if (g_Cvars.visuals.world.skybox == 3) {
						ImGui::TextColored(ImColor(ImGui::GetColorU32(properties::elements::text_color)), "Material Properties");
						ImGui::Edited::ColorEdit4(xorstr_("Color"), xorstr_("Change wireframe color"), g_Cvars.visuals.world.wireframe_color.data());
					}
				}
				ImGui::Edited::EndChild();
				
				ImGui::SameLine(0, 0);

				ImGui::Edited::BeginChild("##ContainerSecond" + selected_visuals_type, ImVec2((properties::background::size.x - 200) / 2, properties::background::size.y), NULL);
				{
					ImGui::TextColored(ImColor(ImGui::GetColorU32(properties::elements::text_color)), "World Second Tab");
				}
				ImGui::Edited::EndChild();
				break;
			}
			default:
				break;
			}

			break;
		}
		case 2:
		{
			break;
		}
		case 3:
		{
			ImGui::Edited::BeginChild("##Container3", ImVec2((properties::background::size.x - 200) / 2, properties::background::size.y), NULL);
			{
				m_pConfigsList->RefreshConfigsList();

				ImGui::TextColored(ImColor(ImGui::GetColorU32(properties::elements::text_color)), "Config");

				static char m_cConfigName[25] = { "" };
				ImGui::InputTextEx("v", "Config name", m_cConfigName, 25, ImVec2(ImGui::GetContentRegionMax().x - style->WindowPadding.x, 40), NULL);

				if (ImGui::Edited::Button(xorstr_("Load"), ImVec2(ImGui::GetContentRegionMax().x - style->WindowPadding.x, 40))) {
					if (!m_pConfigsList->m_vConfigsList.empty()) {
						m_pConfigManager->Load(m_pConfigsList->GetFocusConfig());
						m_pConfigsList->RefreshConfigsList();
					}
				}

				if (ImGui::Edited::Button(xorstr_("Save"), ImVec2(ImGui::GetContentRegionMax().x - style->WindowPadding.x, 40))) {
					if (strlen(m_cConfigName) > 0) {
						m_pConfigManager->Save(m_cConfigName);

						m_pConfigsList->RefreshConfigsList();
						m_pConfigsList->SetFocusConfig(m_cConfigName);
					} else {
						CUtils::logger("Config name cannot be empty!"); //TODO: notification
					}
				}
			}
			ImGui::Edited::EndChild();
			break;
		}
		case 4:
		{
			break;
		}
		default:
			break;
		}

		ImGui::PopStyleVar();
	}

	ImGui::End();
}

void CMenu::Watermark(const char* cheat_name, const char* nickname, const char* ping) {
	ImGuiContext& g = *GImGui;

	ImGui::PushFont(g_pFontManager->GetFont("Lexend-Bold", 19));

	std::string fpsString = std::to_string(ImGui::GetIO().Framerate) + "fps";

	const float cheat_name_size = ImGui::CalcTextSize(cheat_name).x;
	const float developer_size = ImGui::CalcTextSize(nickname).x;
	const float ping_size = ImGui::CalcTextSize(ping).x;
	const float fps_size = ImGui::CalcTextSize(fpsString.c_str()).x;
	const float bar_size = ImGui::CalcTextSize("|").x;

	const float ibar_size = cheat_name_size + bar_size + developer_size + bar_size + ping_size + fps_size + developer_size + bar_size * 3 + bar_size * 3;

	ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - (ibar_size + 15), 15));
	ImGui::SetNextWindowSize(ImVec2(ibar_size, 45));

	ImGui::Begin(xorstr_("##watermark"), nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration);
	{
		const ImVec2& pos = ImGui::GetWindowPos(), spacing = g.Style.ItemSpacing, region = ImGui::GetContentRegionMax();

		ImGui::GetBackgroundDrawList()->AddRectFilled(pos, pos + region, ImGui::GetColorU32(properties::background::filling_color), properties::elements::rounding);
		ImGui::GetBackgroundDrawList()->AddRect(pos, pos + region, ImGui::GetColorU32(properties::background::stroke_color), properties::elements::rounding);

		const char* info_set[4] = { cheat_name, nickname, ping };

		ImGui::SetCursorPos(ImVec2(spacing.x, (45 - ImGui::CalcTextSize(nickname).y) / 2));
		ImGui::BeginGroup();
		{
			for (int i = 0; i < ARRAYSIZE(info_set); i++) {
				ImGui::TextColored(i < 1 ? ImColor(ImGui::GetColorU32(properties::accent_color)) : ImColor(ImGui::GetColorU32(properties::elements::text_color)), info_set[i]);
				ImGui::SameLine();
				ImGui::TextColored(ImColor(ImGui::GetColorU32(properties::elements::text_color)), "|");
				ImGui::SameLine();
			}
		}
		ImGui::EndGroup();
	}
	ImGui::End();

	ImGui::PopFont();
}
