module canvas;

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
}

void Canvas::draw(const vector<RenderData>& rd) const {
}

size_t create_texture(const path& bmp) {
}
