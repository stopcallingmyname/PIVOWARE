#pragma once

class CGameData {
public:
	CGameData();
	~CGameData();

	void Start();
	void Update();

	bool IsReady();
};

extern std::unique_ptr<CGameData> g_pGameData;