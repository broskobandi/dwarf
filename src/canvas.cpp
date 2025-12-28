module canvas;

using sdl2::Renderer;
using sdl2::Window;
using sdl2::Texture;
using sdl2::Color;
using sdl2::Rect;
using sdl2::Point;

using std::vector;
using std::filesystem::path;
using std::size_t;
using std::optional;
using std::variant;
using std::nullopt;
using std::shared_ptr;
using std::holds_alternative;
using std::runtime_error;

Canvas::Canvas(const shared_ptr<Window>& win) :
	ren(win->renderer(Renderer::Flags::PRESENTVSYNC))
{}

void Canvas::clear(Color col) const {
	ren.clear(col);
}

void Canvas::present() const {
	ren.present();
}

void Canvas::draw(const RenderData& rd) const {
	if (holds_alternative<size_t>(rd.col_or_tex_id)) {
		auto tex_id = std::get<size_t>(rd.col_or_tex_id);
		if (tex_id >= textures.size()) {
			throw runtime_error("Texture id is out of bounds.");
		} else {
			ren.copy(
				textures.at(tex_id),
				rd.dstrect,
				rd.srcrect,
				rd.angle,
				rd.center,
				rd.flip
			);
		}
	}
}

void Canvas::draw(const vector<RenderData>& rd) const {
	for (const auto& data : rd) {
		draw(data);
	}
}

size_t Canvas::create_texture(const path& bmp) {
	size_t index = 0;
	for (const auto& p : loaded_bmps) {
		if (p == bmp) {
			return index;
		}
		index++;
	}

	textures.push_back(ren.texture(bmp));

	return textures.size() - 1;
}
