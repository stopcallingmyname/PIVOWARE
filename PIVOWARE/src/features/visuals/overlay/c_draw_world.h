#pragma once

class CDrawWorld {
public:
	CDrawWorld();

	void Overlay();
	void Update();

private:
	void SkyboxChanger();
	void Fog();
};