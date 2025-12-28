module game;

import sdl2;
import canvas;
import tiles;

import std;

using sdl2::Sdl;
using sdl2::Dimensions;
using sdl2::Window;
using sdl2::Renderer;
using sdl2::Event;
using sdl2::KeyCode;
using sdl2::Texture;

using std::vector;
using std::uint32_t;
using std::int32_t;

void Game::run() {

	constexpr uint32_t WIN_W {800};
	constexpr uint32_t WIN_H {600};

	auto sdl = Sdl::init(Sdl::Flags::EVERYTHING);
	auto win =sdl->window(
		"Dwarf", Dimensions{WIN_W, WIN_H}, Window::Flags::SHOWN
	);
	auto event = sdl->event();
	bool is_running = true;

	Canvas canvas(win);

	Tiles tiles(Tiles::InitData{
		.tex_id = canvas.create_texture("../assets/ground4.bmp"),
		.num_imgs = 6,
		.dstrect_size = {128, 128},
		.srcrect_size = {32, 32},
		.hitbox_size = {64, 64},
		.hitbox_position = Tiles::HitboxPosition::TOP_CENTER,
		.rows = WIN_H / (128 / 4),
		.cols = WIN_W / 128,
		.layers = 1,
		.y_offset = 128 / 4,
		.z_offset = 128 / 2,
	});

	while (is_running) {
		bool left_click = false;
		while (event.poll()) {
			if (
				event.type() == Event::Type::QUIT ||
				(
					event.type() == Event::Type::KEYDOWN &&
					event.keycode() == KeyCode::q
				)
			) {
				is_running = false;
			}
			if (
				event.type() == Event::Type::MOUSEBUTTONDOWN &&
				event.mouse().left
			) {
				left_click = true;
			}
		}

		tiles.update({event.mouse().x, event.mouse().y}, left_click);

		canvas.clear({30, 70, 70, 255});

		canvas.draw(tiles.render_data());
		// canvas.draw(tiles.hitboxes_render_data());

		canvas.present();
	}

}
