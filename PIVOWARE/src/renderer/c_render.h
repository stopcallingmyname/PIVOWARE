#pragma once

class CRender : public CDrawList {
public:
	CRender();
	~CRender();

	void RenderScene(std::function<void()> render_function);
};

extern std::unique_ptr<CRender> g_pRender;