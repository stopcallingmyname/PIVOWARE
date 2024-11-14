#pragma once

class CMenu {
public:
	CMenu();
	~CMenu();

	bool IsOpened();

	void Open();
	void Close();
	void Toggle();

	void Draw();
	void Watermark(const char* cheat_name, const char* nickname, const char* ping);

	const char* m_sTitle = "PIVOWARE";
private:
	bool m_bIsOpened;

	std::unique_ptr<CConfigsList> m_pConfigsList;
};

extern std::unique_ptr<CMenu> g_pMenu;