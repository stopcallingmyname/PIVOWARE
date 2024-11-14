#pragma once

typedef unsigned int FontFlags;

//class Il2CppVector2;

class CDrawList {
public:
	void AddLine(const ImVec2& a, const ImVec2& b, const ImColor& col);
	//void AddLine(const Il2CppVector2& a, const Il2CppVector2& b, const ImColor& col, float thickness = 1.f);
	void AddRect(const ImVec2& a, const ImVec2& b, const ImColor& col, bool outline = false, float rounding = 0.f, float thickness = 1.f);
	void AddRectCorner(const ImVec2& a, const ImVec2& b, const ImColor& col, bool outline = false);
	void AddRectFilled(const ImVec2& a, const ImVec2& b, const ImColor& col, float rounding = 0.f);
	void AddRectFilledMultiColor(const ImVec2& a, const ImVec2& c, ImColor col_upr_left, ImColor col_upr_right, ImColor col_bot_right, ImColor col_bot_left);
	void AddQuad(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImVec2& d, const ImColor& col, float thickness = 1.f);
	void AddQuadFilled(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImVec2& d, const ImColor& col);
	void AddTriangle(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImColor& col, float thickness = 1.f);
	void AddTriangleFilled(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImColor& col);
	void AddCircle(const ImVec2& centre, float radius, const ImColor& col, int num_segments = 12, float thickness = 1.f);
	void AddCircleFilled(const ImVec2& centre, float radius, const ImColor& col, int num_segments = 12);
	void AddText(const ImVec2& pos, const ImColor& col, FontFlags flags, const char* fmt, ...);
	void AddTextWrapped(const ImVec2& pos, const ImColor& col, float wrap_width, FontFlags flags, const char* fmt, ...);
	void AddImage(ImTextureID user_texture_id, const ImVec2& a, const ImVec2& b, const ImVec2& uv_a = ImVec2(), const ImVec2& uv_b = ImVec2(1, 1), const ImColor& col = ImColor(IM_COL32_WHITE));
};