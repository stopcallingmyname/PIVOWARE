#include "includes.h"
#include "c_draw_local.h"

CDrawLocal::CDrawLocal() {}

void CDrawLocal::Overlay() {
	if (!g_Cvars.visuals.local.enable)
		return;

	if (!g_pGameData->IsReady())
		return;
}
