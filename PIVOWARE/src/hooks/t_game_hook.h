#pragma once

struct GameHook_t {
	std::string id;
	std::function<void()> func;
};