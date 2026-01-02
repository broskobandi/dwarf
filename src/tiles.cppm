export module tiles;
import sdl2;
import std;

using sdl2::Renderer;
using sdl2::Texture;
using sdl2::Point;
using sdl2::Rect;

using std::size_t;
using std::uint32_t;
using std::int32_t;
using std::filesystem::path;
using std::vector;

export enum class HitboxPosition : uint32_t {
	TOP_CENTER,
	TOP_RIGHT,
	RIGHT_CENTER,
	BOTTOM_RIGHT,
	BOTTOM_CENTER,
	BOTTOM_LEFT,
	LEFT_CENTER,
	TOP_LEFT,
	CENTER
};

export struct TilesInitData {
	uint32_t num_rows;
	uint32_t num_cols;
	uint32_t num_layers;
	uint32_t dstrect_size;
	uint32_t srcrect_size;
	uint32_t hitbox_size;
	int32_t y_offset;
	int32_t z_offset;
	HitboxPosition hitbox_position;
};

export class Tiles : private TilesInitData {
private:
	struct Tile {
		bool is_exposed {false};
		bool is_active {true};
		bool is_highlighted {false};
		bool is_visible {false};
		bool is_staggered {false};
		bool is_blocked_right {false};
		bool is_blocked_left {false};
		bool is_blocked_above {false};
		bool is_in_shadow {false};
		Rect dstrect;
		Rect srcrect;
		Rect hitbox;
	};
	Texture tex;
	vector<Tile> tiles;
public:
	Tiles& operator=(Tiles&&) = delete;
	Tiles& operator=(const Tiles&) = delete;
	Tiles(const Tiles&) = delete;
	Tiles(Tiles&&) = delete;
	Tiles(const Renderer& ren, path path_to_bmp, TilesInitData&& init_data);
	void update(Point mouse_pos, bool left_click);
	void draw(const Renderer& ren) const;
};
