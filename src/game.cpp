module game;
import sdl2;
import std;
import tiles;

using sdl2::Sdl;
using sdl2::Window;
using sdl2::Renderer;
using sdl2::Event;
using sdl2::KeyCode;
using sdl2::Point;

using std::uint32_t;

void Game::run() {
	constexpr uint32_t WIN_W {800};
	constexpr uint32_t WIN_H {600};
	auto sdl = Sdl::init(Sdl::Flags::EVERYTHING);
	auto win = sdl->window("Dwarf", {WIN_W, WIN_H}, Window::Flags::SHOWN);
	auto ren = win->renderer(Renderer::Flags::PRESENTVSYNC);
	auto event = sdl->event();
	ren.set_blend_mode(Renderer::BlendMode::BLEND);

	Tiles tiles(
		ren, "../assets/ground4.bmp", TilesInitData{
			.num_rows = WIN_H / (128 / 4),
			.num_cols = WIN_W / 128,
			.num_layers = 4,
			.dstrect_size = 128,
			.srcrect_size = 32,
			.hitbox_size = 64,
			.y_offset = 128 / 4,
			.z_offset = 128 / 2,
			.hitbox_position = HitboxPosition::TOP_CENTER
		}
	);

	bool is_running {true};

	while (is_running) {
		bool left_click {false};

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

		ren.clear({30, 70, 70, 255});

		tiles.draw(ren);

		ren.present();
	}
}
