import std;
import sdl2;
import game;

using std::runtime_error;
using std::println;
using std::cerr;

int main(void) {
	try {
		Game::run();
	} catch (const runtime_error& e) {
		println(cerr, "{}", e.what());
	}

	return 0;
}
