
struct VisualsLocalSettings_t {
	bool enable;
	bool shootig_through_walls;
	std::vector<float> chams_color;
	struct FovChanger_t {
		bool enable;
		float value;
	} fovChanger[2];

	struct AspectChanger_t {
		bool enable;
		float value;
	} aspectChanger;
};