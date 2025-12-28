module tiles;

import canvas;
import std;
import sdl2;

using std::vector;
using std::uint32_t;
using std::int32_t;
using std::size_t;

using sdl2::Rect;
using sdl2::Point;

Tiles::Tiles(
	size_t tex_id,
	uint32_t tile_size,
	uint32_t hitbox_size,
	uint32_t rows,
	uint32_t cols,
	int32_t y_offset
) {
	for (uint32_t y = 0; y < rows; y++) {
		for (uint32_t x = 0; x < cols; x++) {
			int32_t x_offset = y % 2 == 0 ? 0 : tile_size / 2;
			Rect tile {
				static_cast<int32_t>(x * tile_size + x_offset),
				static_cast<int32_t>(y * y_offset),
				tile_size,
				tile_size
			};
			Rect hitbox {
				static_cast<int32_t>(tile.x + ((tile.w - hitbox_size) / 2)),
				static_cast<int32_t>(tile.y + ((tile.h - hitbox_size) / 2)),
				hitbox_size,
				hitbox_size
			};
			rd.push_back({tex_id, tile});
			hitboxes.push_back(hitbox);
		}
	}
}

const vector<Canvas::RenderData>& Tiles::render_data() const {
	return rd;
}


void Tiles::update(const Event::Mouse& mouse) {
	size_t index = 0;
	for (const auto& hb : hitboxes) {
		if (mouse.has_intersection(hb)) {
			rd.at(index).should_render = false;
		} else {
			rd.at(index).should_render = true;
		}
		index++;
	}
}

vector<Canvas::RenderData> Tiles::hitboxes_render_data() const {
	vector<Canvas::RenderData> rd;
	for (const auto& hb : hitboxes) {
		rd.push_back(Canvas::RenderData{
			sdl2::Color{50, 50, 50, 128}, Rect(hb)
		});
	}
	return rd;
}
