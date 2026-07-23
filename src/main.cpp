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

	Clock clock;

	while (window.isOpen()) {
		if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
			window.close();
		}
		window.clear();

		Time dt = clock.restart();

		if (!beeActive) {
			srand((int)time(0));
			beeSpeed = (rand() % 200) + 200;

			srand((int)time(0) * 10);
			float height = (rand() % 1350) + 500;
			spriteBee.setPosition(Vector2f(2000, height));
			beeActive = true;
		}
		else {
			spriteBee.setPosition(Vector2f(spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()), spriteBee.getPosition().y));
			if (spriteBee.getPosition().x < -100) {
				beeActive = false;
			}
		}

		if (!cloud1Active)
		{
			srand((int)time(0) * 10);
			cloud1Speed = (rand() % 200);

			srand((int)time(0) * 10);
			float height = (rand() % 150);
			spriteCloud1.setPosition(Vector2f(- 200, height));
			cloud1Active = true;
		}
		else
		{
			spriteCloud1.setPosition(Vector2f(
				spriteCloud1.getPosition().x +
				(cloud1Speed * dt.asSeconds()),
				spriteCloud1.getPosition().y));\

			if (spriteCloud1.getPosition().x > 1920)
				cloud1Active = false;
		}
		if (!cloud2Active)
		{
			srand((int)time(0) * 20);
			cloud2Speed = (rand() % 200);
			srand((int)time(0) * 20);
			float height = (rand() % 300) - 150;
			spriteCloud2.setPosition(Vector2f(-200, height));
			cloud2Active = true;
		}
		else
		{
			spriteCloud2.setPosition(Vector2f(
				spriteCloud2.getPosition().x +
				(cloud2Speed * dt.asSeconds()),
				spriteCloud2.getPosition().y));
			if (spriteCloud2.getPosition().x > 1920)
			{
				cloud2Active = false;
			}
		}
		if (!cloud3Active)
		{
			srand((int)time(0) * 30);
			cloud3Speed = (rand() % 200);
			srand((int)time(0) * 30);
			float height = (rand() % 450) - 150;
			spriteCloud3.setPosition(Vector2f(-200, height));
			cloud3Active = true;
		}
		else
		{
			spriteCloud3.setPosition(Vector2f(
				spriteCloud3.getPosition().x +
				(cloud3Speed * dt.asSeconds()),
				spriteCloud3.getPosition().y));
			if (spriteCloud3.getPosition().x > 1920)
			{
				cloud3Active = false;
			}
		}

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