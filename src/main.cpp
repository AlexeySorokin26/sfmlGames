#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
	VideoMode vm(Vector2u(1920, 1080));
	RenderWindow window(vm, "Timber!", State::Fullscreen);

	while (window.isOpen()) {
		if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
			window.close();
		}
		window.clear();
		window.display();
	}

	return 0;
}