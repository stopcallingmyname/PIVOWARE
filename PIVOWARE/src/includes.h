#pragma once

#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif

#define WIN32_LEAN_AND_MEAN

#pragma warning(disable: 4005)
#pragma warning(disable: 4200)

#define _USE_MATH_DEFINES

#include <cmath>
#include <cassert> 
#include <windows.h> 
#include <winternl.h> 
#include <shellapi.h> 

#include <wininet.h> 

#include <iostream> 

#include <type_traits>
#include <map> 
#include <string>
#include <memory> 
#include <mutex>  
#include <fstream>
#include <sstream> 
#include <functional> 
#include <deque>
#include <optional> 
#include <random> 
#include <filesystem> 

#include <future>

#include <coroutine> 

#include "const.h"

#include "MinHook/MinHook.h"
#include "MinHook/MHHelper.h"

#define IMGUI_DEFINE_MATH_OPERATORS

#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_settings.h"
#include "ImGui/edited/imgui_edited.h"
#include "ImGui/imstb_truetype.h"

// Guard tools
#include "security/xorstr.h"

//#include "messages/usermsg.h"

// Hooks on directx functions for imgui and other things
#include "hooks/c_directx.h"

// Game hooks
#include "hooks/t_game_hook.h"
#include "hooks/c_game_hooks.h"

// Global Variables
#include "common/c_gvars.h"

// Config
// Aimbot
#include "common/config/settings/aimbot/t_aimbot_settings.h"

// Visuals
#include "common/config/settings/visuals/local/t_visuals_local_settings.h"
#include "common/config/settings/visuals/world/t_visuals_world_settings.h"
#include "common/config/settings/visuals/t_visuals_settings.h"

// Misc
#include "common/config/settings/misc/t_misc_settings.h"

// Widgets
#include "common/config/settings/widgets/t_widgets_settings.h"

#include "common/config/t_config_variables.h"
#include "common/config/c_config_item.h"
#include "common/config/c_config_manager.h"

// Overlay classes
#include "overlay/menu/fonts/lexend_regular.h"
#include "overlay/menu/fonts/lexend_bold.h"
#include "overlay/menu/fonts/icomoon.h"
#include "overlay/menu/fonts/icomoon_widget.h"
#include "overlay/menu/utils/c_font_manager.h"
#include "overlay/menu/utils/c_configs_list.h"
#include "overlay/menu/enums/e_font_type.h"
#include "overlay/menu/c_menu.h"

#include "renderer/enums/e_font_flag_list.h"
#include "renderer/c_drawlist.h"
#include "renderer/c_render.h"

#include "nlohmann/json.hpp" // Json library

// Il2cpp
#include "includes/libil2cpp/il2cpp-metadata.h"
#include "utils/memory.h"
#include "utils/il2cpp/c_il2cpp.h"
//#include "tools/math.h" 
#include "utils/c_utils.h" 
//#include "tools/input_system.h" 

// sdk classes
#include "sdk/unity/c_object.h"
#include "sdk/unity/c_asset_bundle_create_request.h"
#include "sdk/unity/c_asset_bundle.h"
#include "sdk/unity/c_il2cpp_reference_array.h"
#include "sdk/unity/c_component.h"
#include "sdk/unity/c_camera.h"
#include "sdk/unity/s_color.h"
#include "sdk/unity/c_shader.h"
#include "sdk/unity/c_material.h"
#include "sdk/unity/c_renderer.h"
#include "sdk/unity/c_skinned_mesh_renderer.h"
#include "sdk/unity/c_mesh_renderer.h"
#include "sdk/unity/c_transform.h"
#include "sdk/unity/c_game_object.h"
#include "sdk/unity/c_render_settings.h"
#include "sdk/c_client.h"
#include "sdk/c_sky.h"

// assets
#include "assets/bytes/asset_bundle.h"
#include "assets/enums/e_shader_type.h"
#include "assets/enums/e_material_type.h"
#include "assets/c_asset_bundle_manager.h"

// game classes
#include "game/t_player_data.h"
#include "game/t_entity_data.h"
#include "game/c_game_data.h"

//#include "world/weaponinfo.h"
//#include "world/baseinfo.h"
//#include "world/baselocal.h"
//#include "world/baseplayer.h"
//#include "world/baseentity.h"
//#include "world/baseweapon.h"

// features
//#include "features/misc/misc.h"
//#include "features/visuals/overlay/selection_players.h"
//#include "features/visuals/radar/radar.h"
//#include "features/visuals/overlay/draw_players_out_of_fov.h"
//#include "features/visuals/overlay/draw_players.h"
//#include "features/visuals/overlay/draw_entities.h"
#include "features/visuals/overlay/c_draw_world.h"
#include "features/visuals/overlay/c_draw_local.h"
#include "features/visuals/c_visuals.h"

#if _WIN32 || _WIN64
#if _WIN64
#define ENV64BIT
#else
#define ENV32BIT
#endif
#endif