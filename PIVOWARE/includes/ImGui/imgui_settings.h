class ImFont;
class ImVec4;
class ImColor;

namespace properties {
	inline ImVec4 accent_color = ImColor(112, 110, 215);

	namespace background {
		inline ImVec4 filling_color = ImColor(12, 12, 12);
		inline ImVec4 stroke_color = ImColor(24, 26, 36);

		inline ImVec2 size = ImVec2(900, 515);
		inline float rounding = 6;
	}

	namespace elements {
		inline ImVec4 mark_color = ImColor(255, 255, 255);
		inline ImVec4 stroke_color = ImColor(28, 26, 37);
		inline ImVec4 background_color = ImColor(15, 15, 17);
		inline ImVec4 background_widget_color = ImColor(21, 23, 26);
		inline ImVec4 text_active_color = ImColor(255, 255, 255);
		inline ImVec4 text_hover_color = ImColor(81, 92, 109);
		inline ImVec4 text_color = ImColor(43, 51, 63);

		inline float rounding = 4;
	}

	namespace tab {
		inline ImVec4 tab_active_color = ImColor(22, 22, 30);
		inline ImVec4 border_color = ImColor(14, 14, 15);
	}
}