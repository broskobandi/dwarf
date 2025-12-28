module tiles;

import canvas;
import std;
import sdl2;

using std::vector;
using std::uint32_t;
using std::int32_t;
using std::size_t;
using std::nullopt;

using sdl2::Rect;
using sdl2::Point;

Tiles::Tiles(Tiles::InitData id) :
	num_tiles_per_layer(id.rows * id.cols),
	tex_id(id.tex_id),
	num_imgs(id.num_imgs),
	dstrect_size(id.dstrect_size),
	srcrect_size(id.srcrect_size),
	hitbox_size(id.hitbox_size),
	hitbox_position(id.hitbox_position),
	rows(id.rows),
	cols(id.cols),
	layers(id.layers),
	y_offset(id.y_offset),
	z_offset(id.z_offset)
{
	num_tiles_per_layer = rows * cols;
	size_t index = 0;
	for (uint32_t z = 0; z < layers; z++) {
		for (uint32_t y = 0; y < rows; y++) {
			for (uint32_t x = 0; x < cols; x++) {
				int32_t x_offset = y % 2 == 0 ? 0 : dstrect_size.w / 2;
				Rect dstrect {
					static_cast<int32_t>(x * dstrect_size.w + x_offset),
					static_cast<int32_t>(y * y_offset - z * z_offset),
					dstrect_size.w,
					dstrect_size.h
				};
				Rect hitbox {0, 0, hitbox_size.w, hitbox_size.h};
				switch (hitbox_position) {
					case HitboxPosition::TOP_LEFT:
						hitbox.x = dstrect.x;
						hitbox.y = dstrect.y;
						break;
					case HitboxPosition::TOP_CENTER:
						hitbox.x =
							dstrect.x + ((dstrect_size.w - hitbox_size.w) / 2);
						hitbox.y = dstrect.y;
						break;
					case HitboxPosition::TOP_RIGHT:
						hitbox.x =
							dstrect.x + (dstrect_size.w - hitbox_size.w);
						hitbox.y = dstrect.y;
						break;
					case HitboxPosition::RIGHT_CENTER:
						hitbox.x =
							dstrect.x + (dstrect_size.w - hitbox_size.w);
						hitbox.y =
							dstrect.y + ((dstrect_size.h - hitbox_size.h) / 2);
						break;
					case HitboxPosition::BOTTOM_RIGHT:
						hitbox.x =
							dstrect.x + (dstrect_size.w - hitbox_size.w);
						hitbox.y =
							dstrect.y + (dstrect_size.h - hitbox_size.h);
						break;
					case HitboxPosition::BOTTOM_CENTER:
						hitbox.x =
							dstrect.x + ((dstrect_size.w - hitbox_size.w) / 2);
						hitbox.y =
							dstrect.y + (dstrect_size.h - hitbox_size.h);
						break;
					case HitboxPosition::BOTTOM_LEFT:
						hitbox.x =
							dstrect.x;
						hitbox.y =
							dstrect.y + (dstrect_size.h - hitbox_size.h);
						break;
					case HitboxPosition::LEFT_CENTER:
						hitbox.x =
							dstrect.x;
						hitbox.y =
							dstrect.y + ((dstrect_size.h - hitbox_size.h) / 2);
						break;
					case HitboxPosition::CENTER:
						hitbox.x =
							dstrect.x + ((dstrect_size.w - hitbox_size.w) / 2);
						hitbox.y =
							dstrect.y + ((dstrect_size.h - hitbox_size.h) / 2);
						break;
				}
				Rect srcrect {0, 0, srcrect_size.w, srcrect_size.h};
				tiles.push_back({hitbox});
				rd.push_back({tex_id, dstrect, srcrect});
				index++;
			}
		}
	}
}

const vector<Canvas::RenderData>& Tiles::render_data() const {
	return rd;
}

void Tiles::update(Point mouse_pos, bool left_click) {
	size_t index = 0;
	for (auto& tile : tiles) {
		tile.is_exposed = false;
		if (
			index + num_tiles_per_layer >= rd.size() || 
			!tiles.at(index + num_tiles_per_layer).is_active
		) {
			tile.is_exposed = true;
		}
		if (tile.is_active) {
			rd.at(index).alpha_mod = 255;
		}
		if (
			mouse_pos.has_intersection(tile.hitbox) &&
			tile.is_exposed &&
			tile.is_active
		) {
			rd.at(index).alpha_mod = 128;
			if (
				left_click
			) {
				tile.is_active = false;
				rd.at(index).alpha_mod = 0;
			}
		}
		index++;
	}
}

vector<Canvas::RenderData> Tiles::hitboxes_render_data() const {
	vector<Canvas::RenderData> rd;
	for (const auto& tile : tiles) {
		rd.push_back(Canvas::RenderData{
			sdl2::Color{50, 50, 50, 128}, Rect(tile.hitbox)
		});
	}
	return rd;
}
