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

	Texture textureTree;
	textureTree.loadFromFile("resources/graphics/tree.png");
	Sprite spriteTree(textureTree);
	const float TREE_HORIZONTAL_POSITION = 810;
	const float TREE_VERTICAL_POSITION = 0;
	spriteTree.setPosition(Vector2f(TREE_HORIZONTAL_POSITION, TREE_VERTICAL_POSITION));

	Texture textureBee;
	textureBee.loadFromFile("resources/graphics/bee.png");
	Sprite spriteBee(textureBee);
	spriteTree.setPosition(Vector2f(0, 800));
	bool beeActive = false;
	float beeSpeed = 0.0f;

	Texture textureCloud;
	textureCloud.loadFromFile("resources/graphics/cloud.png");
	Sprite spriteCloud1(textureCloud);
	Sprite spriteCloud2(textureCloud);
	Sprite spriteCloud3(textureCloud);

	spriteCloud1.setPosition(Vector2f(0, 0));
	spriteCloud2.setPosition(Vector2f(0, 250));
	spriteCloud3.setPosition(Vector2f(0, 500));

	bool cloud1Active = false;
	bool cloud2Active = false;
	bool cloud3Active = false;

	float cloud1Speed = 0.0f;
	float cloud2Speed = 0.0f;
	float cloud3Speed = 0.0f;

	while (window.isOpen()) {
		if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
			window.close();
		}
		window.clear();

		window.draw(spriteBackground);
		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);
		window.draw(spriteTree);
		window.draw(spriteBee);

		window.display();
	}

	return 0;
}