#include <SFML/Graphics.hpp>

#include <cstdlib>
#include <ctime>
#include <optional>
#include <sstream>
#include <string>

using namespace sf;


void UpdateBranches(int seed);

const int NUM_BRANCHES = 6;
std::vector<Sprite> branches;

enum class Side { LEFT, RIGHT, NONE };
Side branchPositions[NUM_BRANCHES];

int main()
{
    // Seed the RNG once, at start-up (not on every spawn).
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    VideoMode vm(Vector2u(1920, 1080));
    RenderWindow window(vm, "Timber!", State::Windowed);

    // --- Resources ---
    Texture textureBackground("resources/graphics/background.png");
    Sprite spriteBackground(textureBackground);
    spriteBackground.setPosition(Vector2f(0, 0));

    Texture textureTree("resources/graphics/tree.png");
    Sprite spriteTree(textureTree);
    const float TREE_HORIZONTAL_POSITION = 810;
    const float TREE_VERTICAL_POSITION = 0;
    spriteTree.setPosition(Vector2f(TREE_HORIZONTAL_POSITION, TREE_VERTICAL_POSITION));

    Texture textureBee("resources/graphics/bee.png");
    Sprite spriteBee(textureBee);
    spriteBee.setPosition(Vector2f(2000, 800)); // start off-screen
    bool beeActive = false;
    float beeSpeed = 0.0f;

    Texture textureCloud("resources/graphics/cloud.png");
    Sprite spriteCloud1(textureCloud);
    Sprite spriteCloud2(textureCloud);
    Sprite spriteCloud3(textureCloud);

    spriteCloud1.setPosition(Vector2f(-200, 0));
    spriteCloud2.setPosition(Vector2f(-200, 250));
    spriteCloud3.setPosition(Vector2f(-200, 500));

    bool cloud1Active = false;
    bool cloud2Active = false;
    bool cloud3Active = false;

    float cloud1Speed = 0.0f;
    float cloud2Speed = 0.0f;
    float cloud3Speed = 0.0f;

    Clock clock;

    bool paused = true;

    int score = 0;

    Font font("resources/fonts/testFont.ttf");

    Text messageText(font, "Type Enter to start!", 75);
    Text scoreText(font, "Score = 0", 100);

    messageText.setFillColor(Color::White);
    scoreText.setFillColor(Color::White);

    Texture textureBranch("resources/graphics/branch.png");
    for (int i = 0; i < NUM_BRANCHES; i++) {
        branches.emplace_back(textureBranch);
        branches[i].setPosition(Vector2f(-2000, -2000)); // In world position
        branches[i].setOrigin(Vector2f(220, 20));  // pivot point in own coordinates (center of image just half of it)
    }

    FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(Vector2f(
        textRect.position.x + textRect.size.x / 2.0f,
        textRect.position.y + textRect.size.y / 2.0f));
    messageText.setPosition(Vector2f(1920 / 2.0f, 1080 / 2.0f));
    scoreText.setPosition(Vector2f(20, 20));


    UpdateBranches(1);
    UpdateBranches(2);
    UpdateBranches(3);
    UpdateBranches(4);
    UpdateBranches(5);

    while (window.isOpen())
    {
        /*
        ****************************************
        ** Handle input
        ****************************************
        */
        // Pump the OS event queue, otherwise the window is flagged "Not Responding".
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
            window.close();

        if (Keyboard::isKeyPressed(Keyboard::Key::Enter))
            paused = false;

        if (Keyboard::isKeyPressed(Keyboard::Key::Space))
            paused = true;

        /*
        ****************************************
        ** Update the scene (only while playing)
        ****************************************
        */
        if (!paused)
        {
            Time dt = clock.restart();

            // Bee
            if (!beeActive)
            {
                beeSpeed = static_cast<float>((std::rand() % 200) + 200);
                float height = static_cast<float>((std::rand() % 1350) + 500);
                spriteBee.setPosition(Vector2f(2000, height));
                beeActive = true;
            }
            else
            {
                spriteBee.setPosition(Vector2f(
                    spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()),
                    spriteBee.getPosition().y));

                if (spriteBee.getPosition().x < -100)
                    beeActive = false;
            }

            // Cloud 1
            if (!cloud1Active)
            {
                cloud1Speed = static_cast<float>(std::rand() % 200);
                float height = static_cast<float>(std::rand() % 150);
                spriteCloud1.setPosition(Vector2f(-200, height));
                cloud1Active = true;
            }
            else
            {
                spriteCloud1.setPosition(Vector2f(
                    spriteCloud1.getPosition().x + (cloud1Speed * dt.asSeconds()),
                    spriteCloud1.getPosition().y));

                if (spriteCloud1.getPosition().x > 1920)
                    cloud1Active = false;
            }

            // Cloud 2
            if (!cloud2Active)
            {
                cloud2Speed = static_cast<float>(std::rand() % 200);
                float height = static_cast<float>((std::rand() % 300) - 150);
                spriteCloud2.setPosition(Vector2f(-200, height));
                cloud2Active = true;
            }
            else
            {
                spriteCloud2.setPosition(Vector2f(
                    spriteCloud2.getPosition().x + (cloud2Speed * dt.asSeconds()),
                    spriteCloud2.getPosition().y));

                if (spriteCloud2.getPosition().x > 1920)
                    cloud2Active = false;
            }

            // Cloud 3
            if (!cloud3Active)
            {
                cloud3Speed = static_cast<float>(std::rand() % 200);
                float height = static_cast<float>((std::rand() % 450) - 150);
                spriteCloud3.setPosition(Vector2f(-200, height));
                cloud3Active = true;
            }
            else
            {
                spriteCloud3.setPosition(Vector2f(
                    spriteCloud3.getPosition().x + (cloud3Speed * dt.asSeconds()),
                    spriteCloud3.getPosition().y));

                if (spriteCloud3.getPosition().x > 1920)
                    cloud3Active = false;
            }

            std::stringstream ss;
            ss << "Score = " << score;
            scoreText.setString(ss.str());

            for (int i = 0; i < NUM_BRANCHES; i++)
            {
                float height = i * 150;
                if (branchPositions[i] == Side::LEFT)
                {
                    branches[i].setPosition(Vector2f(610, height));
                    branches[i].setRotation(degrees(180));
                }
                else if (branchPositions[i] == Side::RIGHT)
                {
                    branches[i].setPosition(Vector2f(1330, height));
                    branches[i].setRotation(degrees(0));
                }
                else
                {
                    branches[i].setPosition(Vector2f(3000, height));
                }
            }
        }

        /*
        ****************************************
        ** Draw the scene (always)
        ****************************************
        */
        window.clear();

        window.draw(spriteBackground);
        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);

        for (int i = 0; i < NUM_BRANCHES; i++)
        {
            window.draw(branches[i]);
        }

        window.draw(spriteTree);
        window.draw(spriteBee);
        window.draw(scoreText);

        if (paused)
            window.draw(messageText);

        window.display();
    }

    return 0;
}

void UpdateBranches(int seed)
{
    for (int j = NUM_BRANCHES - 1; j > 0; j--) {
        branchPositions[j] = branchPositions[j - 1];
    }

    srand((int)time(0) + seed);
    int r = (rand() % 5);
    switch (r) {
    case 0:
        branchPositions[0] = Side::LEFT;
        break;
    case 1:
        branchPositions[0] = Side::RIGHT;
        break;
    default:
        branchPositions[0] = Side::NONE;
        break;
    }
}
