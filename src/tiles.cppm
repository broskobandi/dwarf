export module tiles;

import canvas;
import std;
import sdl2;

using std::vector;
using std::uint32_t;
using std::int32_t;
using std::size_t;

using sdl2::Rect;
using sdl2::Point;
using sdl2::Dimensions;

export class Tiles {
public:

	enum class HitboxPosition {
		TOP_LEFT,
		TOP_CENTER,
		TOP_RIGHT,
		RIGHT_CENTER,
		BOTTOM_RIGHT,
		BOTTOM_CENTER,
		BOTTOM_LEFT,
		LEFT_CENTER,
		CENTER
	};

	struct InitData {
		size_t tex_id;
		uint32_t num_imgs;
		Dimensions dstrect_size;
		Dimensions srcrect_size;
		Dimensions hitbox_size;
		HitboxPosition hitbox_position {HitboxPosition::CENTER};
		uint32_t rows;
		uint32_t cols;
		uint32_t layers {1};
		int32_t y_offset {0};
		int32_t z_offset {0};
	};

private:

	struct Tile {
		Rect hitbox;
		bool is_exposed {false};
		bool is_active {true};
	};

	vector<Canvas::RenderData> rd;
	vector<Tile> tiles;
	uint32_t num_tiles_per_layer;
	size_t tex_id;
	uint32_t num_imgs;
	Dimensions dstrect_size;
	Dimensions srcrect_size;
	Dimensions hitbox_size;
	HitboxPosition hitbox_position {HitboxPosition::CENTER};
	uint32_t rows;
	uint32_t cols;
	uint32_t layers {1};
	int32_t y_offset {0};
	int32_t z_offset {0};
public:
	Tiles(InitData init_data);
	const vector<Canvas::RenderData>& render_data() const;
	void update(Point mouse_pos, bool left_click);
	vector<Canvas::RenderData> hitboxes_render_data() const;
};
