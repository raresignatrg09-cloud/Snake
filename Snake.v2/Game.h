#pragma once

#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "Snake.h"
#include "Fruit.h"
#include "Menu.h"
#include "TextManager.h"
#include "SoundManager.h"

class Game
{
public:
    Game();
    void run();

private:
    enum class State
    {
        MainMenu,
        Playing,
        Paused
    };

    void processEvents();
    void update(float dt);
    void render();

    void handleMenuInput(sf::Keyboard::Key key);
    void handleGameInput(sf::Keyboard::Key key);
    void handlePauseInput(sf::Keyboard::Key key);

    void initUI();
    void resetGame();
    void resumeGame();
    void animateMenu(const std::vector<std::string>& ids);
    void hideMainMenu();
	void hidePauseMenu();
	void showPauseMenu();
	void showMainMenu();
	void initSounds();
    void setMenu(const std::vector<std::string>& items, const std::string& prefix, float yStart);
    void setMenuVisibility(const Menu& menu, const std::string& prefix, bool visible);
    void animateMenuOnce(const Menu& menu, const std::string& prefix, bool& flag);
    void highlightMenu(const Menu& menu, const std::string& prefix);

private:
    sf::RenderWindow window;
    sf::Clock clock;
    sf::Event event;

    State state;

    Grid grid;
    Snake snake;
    Fruit fruit;

    Menu mainMenu;
    Menu pauseMenu;
    TextManager textManager;

    sf::Vector2i pendingDir;
    float moveTimer;
    float moveDelay;

    unsigned int score;
    sf::RectangleShape overlay;

	SoundManager soundManager;

    bool menuAnimated;
    bool pauseAnimated;
};