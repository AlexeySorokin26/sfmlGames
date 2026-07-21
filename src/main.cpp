#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
	VideoMode vm(Vector2u(1920, 1080));
	RenderWindow window(vm, "Timber!", State::Windowed);

	Texture textureBackground;
	textureBackground.loadFromFile("resources/graphics/background.png");
	Sprite spriteBackground(textureBackground);
	spriteBackground.setPosition(Vector2f(0, 0));

	while (window.isOpen()) {
		if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
			window.close();
		}
		window.clear();
		window.draw(spriteBackground);
		window.display();
	}

	return 0;
}