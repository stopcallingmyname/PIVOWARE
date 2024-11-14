#pragma once

class CVector3 {
public:
	float x, y, z;

	CVector3 Init(float _x, float _y, float _z) {
		x = _x;
		y = _y;
		z = _z;

		return *this;
	}

	bool operator ==(CVector3 b) {
		return this->x == b.x && this->y == b.y && this->z == b.z;
	}

	bool operator !=(CVector3 b) {
		return !(this->x == b.x && this->y == b.y && this->z == b.z);
	}
};

class CVisuals {
public:
	CVisuals();
	~CVisuals();

	void Overlay();
	void Update();
	void OnDestroy();

	void InMenuUpdate();
private:
	void FovChanger();
	void AspectChanger();

	typedef CVector3*(*weapon_system_get_cursor_t)(CVector3*, void*, bool, int32_t);
	static CVector3* GetCursor(CVector3* retstr, void* _inst, bool inside, int32_t radius); // WeaponSystem -> private Vector3i? GetCursor(bool inside, int radius)

	typedef CVector3* (*weapon_system_get_cursor_under_ray_t)(CVector3*, void*, bool, int32_t, void*);
	static CVector3* GetCursorUnderRay(CVector3* retstr, void* _inst, bool inside, int32_t radius, void* ray);  // WeaponSystem -> private Vector3i? GetCursorUnderRay(bool inside, int radius, Ray ray)

private:
	std::unique_ptr<CDrawWorld> m_pDrawWorld;
	std::unique_ptr<CDrawLocal> m_pDrawLocal;
};

extern std::unique_ptr<CVisuals> g_pVisuals;