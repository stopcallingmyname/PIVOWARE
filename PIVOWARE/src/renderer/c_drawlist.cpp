#include "includes.h"

void CDrawList::AddLine(const ImVec2& a, const ImVec2& b, const ImColor& col) {
	GImGui->CurrentWindow->DrawList->AddRectFilled(a, b + ImVec2(1, 1), col, 1.f);
}

//void CDrawList::AddLine(const Il2CppVector2& a, const Il2CppVector2& b, const ImColor& col, float thickness)
//{
//	GImGui->CurrentWindow->DrawList->AddLine(ImVec2(a.x, a.y), ImVec2(b.x, b.y), col, thickness);
//}

void CDrawList::AddRect(const ImVec2& a, const ImVec2& b, const ImColor& col, bool outline, float rounding, float thickness) {
	if (rounding) {
		GImGui->CurrentWindow->DrawList->AddRect(a, b + ImVec2(1, 1), col, rounding, thickness);
	}
	else {
		AddLine(ImVec2(a.x, a.y), ImVec2(b.x, a.y), col);
		AddLine(ImVec2(b.x, a.y + 1), ImVec2(b.x, b.y), col);
		AddLine(ImVec2(a.x, b.y), ImVec2(b.x - 1, b.y), col);
		AddLine(ImVec2(a.x, a.y + 1), ImVec2(a.x, b.y - 1), col);
	}

	if (outline)
	{
		AddRect(a - ImVec2(1, 1), b + ImVec2(1, 1), col & IM_COL32_A_MASK, false, rounding, thickness);
		AddRect(a + ImVec2(1, 1), b - ImVec2(1, 1), col & IM_COL32_A_MASK, false, rounding, thickness);
	}
}

void CDrawList::AddRectCorner(const ImVec2& a, const ImVec2& b, const ImColor& col, bool outline)
{
	const auto line_w = (b.x - a.x) * 0.25f;
	const auto line_h = (b.y - a.y) * 0.25f;

	AddLine(ImVec2(a.x, a.y + 1), ImVec2(a.x, a.y + line_h), col);
	AddLine(ImVec2(a.x, a.y), ImVec2(a.x + line_w, a.y), col);
	AddLine(ImVec2(b.x - line_w, a.y), ImVec2(b.x, a.y), col);
	AddLine(ImVec2(b.x, a.y + 1), ImVec2(b.x, a.y + line_h), col);
	AddLine(ImVec2(a.x, b.y - line_h), ImVec2(a.x, b.y - 1), col);
	AddLine(ImVec2(a.x, b.y), ImVec2(a.x + line_w, b.y), col);
	AddLine(ImVec2(b.x - line_w, b.y), ImVec2(b.x, b.y), col);
	AddLine(ImVec2(b.x, b.y - line_h), ImVec2(b.x, b.y - 1), col);

	if (outline)
	{
		AddLine(ImVec2(a.x, a.y - 1), ImVec2(a.x + line_w - 1, a.y - 1), col & IM_COL32_A_MASK);
		AddLine(ImVec2(a.x + 2, a.y + 1), ImVec2(a.x + line_w - 1, a.y + 1), col & IM_COL32_A_MASK);
		AddLine(ImVec2(a.x + line_w, a.y - 1), ImVec2(a.x + line_w, a.y + 1), col & IM_COL32_A_MASK);

		AddLine(ImVec2(a.x - 1, a.y - 1), ImVec2(a.x - 1, a.y + line_h - 1), col & IM_COL32_A_MASK);
		AddLine(ImVec2(a.x + 1, a.y + 1), ImVec2(a.x + 1, a.y + line_h - 1), col & IM_COL32_A_MASK);
		AddLine(ImVec2(a.x - 1, a.y + line_h), ImVec2(a.x + 1, a.y + line_h), col & IM_COL32_A_MASK);

		AddLine(ImVec2(a.x - 1, b.y - line_h + 1), ImVec2(a.x - 1, b.y), col & IM_COL32_A_MASK);
		AddLine(ImVec2(a.x + 1, b.y - line_h + 1), ImVec2(a.x + 1, b.y - 1), col & IM_COL32_A_MASK);
		AddLine(ImVec2(a.x - 1, b.y - line_h), ImVec2(a.x + 1, b.y - line_h), col & IM_COL32_A_MASK);

		AddLine(ImVec2(a.x - 1, b.y + 1), ImVec2(a.x + line_w - 1, b.y + 1), col & IM_COL32_A_MASK);
		AddLine(ImVec2(a.x + 2, b.y - 1), ImVec2(a.x + line_w - 1, b.y - 1), col & IM_COL32_A_MASK);
		AddLine(ImVec2(a.x + line_w, b.y - 1), ImVec2(a.x + line_w, b.y + 1), col & IM_COL32_A_MASK);

		AddLine(ImVec2(b.x - line_w + 1, a.y - 1), ImVec2(b.x, a.y - 1), col & IM_COL32_A_MASK);
		AddLine(ImVec2(b.x - line_w + 1, a.y + 1), ImVec2(b.x - 1, a.y + 1), col & IM_COL32_A_MASK);
		AddLine(ImVec2(b.x - line_w, a.y - 1), ImVec2(b.x - line_w, a.y + 1), col & IM_COL32_A_MASK);

		AddLine(ImVec2(b.x + 1, a.y - 1), ImVec2(b.x + 1, a.y + line_h - 1), col & IM_COL32_A_MASK);
		AddLine(ImVec2(b.x - 1, a.y + 2), ImVec2(b.x - 1, a.y + line_h - 1), col & IM_COL32_A_MASK);
		AddLine(ImVec2(b.x - 1, a.y + line_h), ImVec2(b.x + 1, a.y + line_h), col & IM_COL32_A_MASK);

		AddLine(ImVec2(b.x + 1, b.y - line_h + 1), ImVec2(b.x + 1, b.y + 1), col & IM_COL32_A_MASK);
		AddLine(ImVec2(b.x - 1, b.y - line_h + 1), ImVec2(b.x - 1, b.y - 1), col & IM_COL32_A_MASK);
		AddLine(ImVec2(b.x - 1, b.y - line_h), ImVec2(b.x + 1, b.y - line_h), col & IM_COL32_A_MASK);

		AddLine(ImVec2(b.x - line_w + 1, b.y + 1), ImVec2(b.x, b.y + 1), col & IM_COL32_A_MASK);
		AddLine(ImVec2(b.x - line_w + 1, b.y - 1), ImVec2(b.x - 2, b.y - 1), col & IM_COL32_A_MASK);
		AddLine(ImVec2(b.x - line_w, b.y - 1), ImVec2(b.x - line_w, b.y + 1), col & IM_COL32_A_MASK);
	}
}

void CDrawList::AddRectFilled(const ImVec2& a, const ImVec2& b, const ImColor& col, float rounding)
{
	GImGui->CurrentWindow->DrawList->AddRectFilled(a, b, col, rounding);
}

void CDrawList::AddRectFilledMultiColor(const ImVec2& a, const ImVec2& c, ImColor col_upr_left, ImColor col_upr_right, ImColor col_bot_right, ImColor col_bot_left)
{
	GImGui->CurrentWindow->DrawList->AddRectFilledMultiColor(a, c, col_upr_left, col_upr_right, col_bot_right, col_bot_left);
}

void CDrawList::AddQuad(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImVec2& d, const ImColor& col, float thickness)
{
	GImGui->CurrentWindow->DrawList->AddQuad(a, b, c, d, col, thickness);
}

void CDrawList::AddQuadFilled(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImVec2& d, const ImColor& col)
{
	GImGui->CurrentWindow->DrawList->AddQuadFilled(a, b, c, d, col);
}

void CDrawList::AddTriangle(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImColor& col, float thickness)
{
	GImGui->CurrentWindow->DrawList->AddTriangle(a, b, c, col, thickness);
}

void CDrawList::AddTriangleFilled(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImColor& col)
{
	GImGui->CurrentWindow->DrawList->AddTriangleFilled(a, b, c, col);
}

void CDrawList::AddCircle(const ImVec2& centre, float radius, const ImColor& col, int num_segments, float thickness)
{
	GImGui->CurrentWindow->DrawList->AddCircle(centre, radius, col, num_segments, thickness);
}

void CDrawList::AddCircleFilled(const ImVec2& centre, float radius, const ImColor& col, int num_segments)
{
	GImGui->CurrentWindow->DrawList->AddCircleFilled(centre, radius, col, num_segments);
}

static void AddTextEx(ImVec2 pos, const ImColor& col, float wrap_width = 0.f, FontFlags flags = FontFlags_None, const char* fmt = NULL)
{
	if (!fmt || !strlen(fmt))
		return;

	const auto text_size = GImGui->Font->CalcTextSizeA(GImGui->Font->FontSize, FLT_MAX, wrap_width, fmt);

	if (flags & FontFlags_CenterX)
		pos.x -= text_size.x * 0.5f;

	if (flags & FontFlags_CenterY)
		pos.y -= text_size.y * 0.5f;

	GImGui->CurrentWindow->DrawList->PushTextureID(GImGui->IO.Fonts->TexID);

	if (flags & FontFlags_Shadow)
		GImGui->CurrentWindow->DrawList->AddText(GImGui->Font, GImGui->Font->FontSize, pos + ImVec2(1, 1), col & IM_COL32_A_MASK, fmt);

	if (flags & FontFlags_Outline)
	{
		GImGui->CurrentWindow->DrawList->AddText(GImGui->Font, GImGui->Font->FontSize, pos - ImVec2(0, 1), col & IM_COL32_A_MASK, fmt);
		GImGui->CurrentWindow->DrawList->AddText(GImGui->Font, GImGui->Font->FontSize, pos + ImVec2(0, 1), col & IM_COL32_A_MASK, fmt);
		GImGui->CurrentWindow->DrawList->AddText(GImGui->Font, GImGui->Font->FontSize, pos + ImVec2(1, 0), col & IM_COL32_A_MASK, fmt);
		GImGui->CurrentWindow->DrawList->AddText(GImGui->Font, GImGui->Font->FontSize, pos - ImVec2(1, 0), col & IM_COL32_A_MASK, fmt);

		GImGui->CurrentWindow->DrawList->AddText(GImGui->Font, GImGui->Font->FontSize, pos - ImVec2(1, 1), col & IM_COL32_A_MASK, fmt);
		GImGui->CurrentWindow->DrawList->AddText(GImGui->Font, GImGui->Font->FontSize, pos + ImVec2(1, -1), col & IM_COL32_A_MASK, fmt);
		GImGui->CurrentWindow->DrawList->AddText(GImGui->Font, GImGui->Font->FontSize, pos - ImVec2(-1, 1), col & IM_COL32_A_MASK, fmt);
		GImGui->CurrentWindow->DrawList->AddText(GImGui->Font, GImGui->Font->FontSize, pos + ImVec2(1, 1), col & IM_COL32_A_MASK, fmt);
	}

	GImGui->CurrentWindow->DrawList->AddText(GImGui->Font, GImGui->Font->FontSize, pos, col, fmt);
	GImGui->CurrentWindow->DrawList->PopTextureID();
}

void CDrawList::AddText(const ImVec2& pos, const ImColor& col, FontFlags flags, const char* fmt, ...)
{
	char buf[4096] = { '\0' };
	va_list vlist = nullptr;
	va_start(vlist, fmt);
	vsprintf_s(buf, fmt, vlist);
	va_end(vlist);

	AddTextEx(pos, col, 0, flags, buf);
}

void CDrawList::AddTextWrapped(const ImVec2& pos, const ImColor& col, float wrap_width, FontFlags flags, const char* fmt, ...)
{
	char buf[4096] = { '\0' };
	va_list vlist = nullptr;
	va_start(vlist, fmt);
	vsprintf_s(buf, fmt, vlist);
	va_end(vlist);

	AddTextEx(pos, col, wrap_width, flags, buf);
}

void CDrawList::AddImage(ImTextureID user_texture_id, const ImVec2& a, const ImVec2& b, const ImVec2& uv_a, const ImVec2& uv_b, const ImColor& col)
{
	GImGui->CurrentWindow->DrawList->AddImage(user_texture_id, a, b, uv_a, uv_b, col);
}