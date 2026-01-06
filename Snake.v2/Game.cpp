#include "Game.h"
#include "Source.hpp"

// Constructor: initialize game window, grid, state, timers, score, menus
Game::Game()
    : window({ config::WINDOW_WIDTH, config::WINDOW_HEIGHT }, config::WINDOW_TITLE),
    grid(config::GRID_ROWS, config::GRID_COLS, config::GRID_CELL_SIZE),
    state(State::MainMenu),
    moveTimer(0.f),
    moveDelay(config::SNAKE_SPEED),
    score(0),
	menuAnimated(false),
	pauseAnimated(false)
{
    window.setFramerateLimit(60);  // Limit FPS to 60

    pendingDir = snake.getDirection();  // Initialize snake direction
    fruit.spawn(snake);                 // Spawn first fruit

    initUI();      // Setup UI elements (menus, score, overlay)
    initSounds();  // Load sounds and music

    // Load and set window icon
    sf::Image icon;
    if (icon.loadFromFile("Sprite/icon-snake.png"))
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

// Main game loop
void Game::run()
{
    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds(); // Delta time for frame
        processEvents();                        // Handle input
        update(dt);                              // Update game state
        render();                                // Draw everything
    }
}

// Update game state
void Game::update(float dt)
{
    textManager.updateAnimations(dt);  // Update text animations

    if (state != State::Playing) return; // Only update snake if playing

    moveTimer += dt;
    if (moveTimer >= moveDelay)
    {
        moveTimer = 0.f;

        // Check for collisions with walls or self
        if (snake.checkCollision())
        {
            soundManager.playSound("hit_wall");
            resetGame();
            return;
        }

        // Move snake in pending direction
        snake.setDirection(pendingDir);
        snake.move();

        // Check if snake ate the fruit
        if (snake.getPosition() == fruit.getPosition())
        {
            soundManager.playSound("eat");
            snake.grow();
            fruit.spawn(snake);
            score++;
        }

		// Check win condition
		if (snake.checkWinCondition())
        {
            resetGame(); // Reset game on win
            return;
        }
    }

    snake.updateRender(dt);  // Update snake rendering
	textManager.setText("score", "Score: " + std::to_string(score)); // Update score display
}

// Render all objects
void Game::render()
{
    window.clear();

    // Draw main game objects
    grid.draw(window);
    fruit.draw(window);
    snake.draw(window);

    // Draw and animate menus if necessary
    if (state == State::MainMenu)
    {
        window.draw(overlay);
        animateMenuOnce(mainMenu, "menu_", menuAnimated);
        highlightMenu(mainMenu, "menu_");
        setMenuVisibility(mainMenu, "menu_", true);
    }
    else if (state == State::Paused)
    {
        window.draw(overlay);
        animateMenuOnce(pauseMenu, "pause_", pauseAnimated);
        highlightMenu(pauseMenu, "pause_");
        setMenuVisibility(pauseMenu, "pause_", true);
    }

    // Draw score
    textManager.setText("score", "Score: " + std::to_string(score));
    textManager.draw(window);

    window.display();
}

// Handle window events and keyboard input
void Game::processEvents()
{
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type != sf::Event::KeyPressed)
            continue;

        auto key = event.key.code;

        // Delegate input based on current state
        if (state == State::MainMenu) handleMenuInput(key);
        else if (state == State::Playing) handleGameInput(key);
        else if (state == State::Paused) handlePauseInput(key);
    }
}

// Initialize UI elements: menus, score, overlay
void Game::initUI()
{
    textManager.loadFont(config::FONT_PATH);

    // Setup main menu
    mainMenu.setItems({ "Start Game", "Exit" });
    setMenu(mainMenu.getItems(), "menu_", 220.f);

    // Setup pause menu
    pauseMenu.setItems({ "Resume", "Restart", "Quit" });
    setMenu(pauseMenu.getItems(), "pause_", 220.f);

    // Score text
    textManager.addText("score", "Score: 0", 22, { 10.f, 10.f });

    // Overlay for menus
    overlay.setSize({ (float)config::WINDOW_WIDTH, (float)config::WINDOW_HEIGHT });
    overlay.setFillColor(sf::Color(0, 0, 0, 150));
}

// Reset game state (after death or restart)
void Game::resetGame()
{
    snake = Snake();              // Reset snake
    fruit.spawn(snake);           // Respawn fruit
    score = 0;
    pendingDir = snake.getDirection();
    hideMainMenu();
    hidePauseMenu();
    state = State::Playing;
}

// Resume game from pause
void Game::resumeGame()
{
    hideMainMenu();
    hidePauseMenu();
    state = State::Playing;
}

// Animate menu items (fade in + scale)
void Game::animateMenu(const std::vector<std::string>& ids)
{
    for (int i = 0; i < ids.size(); i++)
    {
        std::string id = ids[i];
        textManager.animateTextFade(id, sf::Color(255, 255, 255, 0), sf::Color::White, 0.5f + i * 0.1f);
        textManager.animateTextScale(id, 0.8f, 1.f, 0.5f + i * 0.1f);
    }
}

// Hide menus
void Game::hideMainMenu() { setMenuVisibility(mainMenu, "menu_", false); }
void Game::hidePauseMenu() { setMenuVisibility(pauseMenu, "pause_", false); }

// Show menus
void Game::showPauseMenu() { setMenuVisibility(pauseMenu, "pause_", true); pauseAnimated = false; }
void Game::showMainMenu() { setMenuVisibility(mainMenu, "menu_", true); menuAnimated = false; }

// Load sounds and music
void Game::initSounds()
{
    soundManager.loadSound("eat", "Sound/music_food.wav");
    soundManager.loadSound("mouse_click", "Sound/mouse_click.wav");
    soundManager.loadSound("hit_wall", "Sound/hit_wall.wav");
    soundManager.loadMusic("Sound/soft-background-piano.wav");
    soundManager.setMusicVolume(30.f);
    soundManager.playMusic(true);
}

// Setup menu text elements
void Game::setMenu(const std::vector<std::string>& items, const std::string& prefix, float yStart)
{
    for (int i = 0; i < items.size(); i++)
    {
        std::string id = prefix + std::to_string(i);
        textManager.addText(id, items[i], 32, { 0.f, yStart + i * 50.f });
        textManager.centerText(id, config::WINDOW_WIDTH / 2.f, yStart + i * 50.f);
        textManager.setColor(id, sf::Color(255, 255, 255, 0)); // Initially invisible
    }
}

// Helper: show/hide menu items
void Game::setMenuVisibility(const Menu& menu, const std::string& prefix, bool visible)
{
    for (int i = 0; i < menu.getItems().size(); i++)
        textManager.setVisible(prefix + std::to_string(i), visible);
}

// Animate menu once (avoid repeating animation)
void Game::animateMenuOnce(const Menu& menu, const std::string& prefix, bool& flag)
{
    if (flag) return;
    std::vector<std::string> ids;
    for (int i = 0; i < menu.getItems().size(); i++)
        ids.push_back(prefix + std::to_string(i));
    animateMenu(ids);
    flag = true;
}

// Highlight selected menu item
void Game::highlightMenu(const Menu& menu, const std::string& prefix)
{
    for (int i = 0; i < menu.getItems().size(); i++)
        textManager.setColor(prefix + std::to_string(i),
            i == menu.getSelectedIndex() ? sf::Color::Yellow : sf::Color::White);
}

// Handle main menu input
void Game::handleMenuInput(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Up) mainMenu.moveUp();
    else if (key == sf::Keyboard::Down) mainMenu.moveDown();
    else if (key == sf::Keyboard::Enter)
    {
        if (mainMenu.getSelectedIndex() == 0) // Start Game
        {
            soundManager.playSound("mouse_click");
            hideMainMenu();
            state = State::Playing;
        }
        else // Exit
        {
            window.close();
        }
    }
}

// Handle in-game controls
void Game::handleGameInput(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Escape)
    {
        showPauseMenu();
        state = State::Paused;
    }

    // Movement controls
    if (key == sf::Keyboard::W) pendingDir = { 0, -1 };
    if (key == sf::Keyboard::S) pendingDir = { 0, 1 };
    if (key == sf::Keyboard::A) pendingDir = { -1, 0 };
    if (key == sf::Keyboard::D) pendingDir = { 1, 0 };
}

// Handle pause menu input
void Game::handlePauseInput(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Up) pauseMenu.moveUp();
    else if (key == sf::Keyboard::Down) pauseMenu.moveDown();
    else if (key == sf::Keyboard::Enter)
    {
        int choice = pauseMenu.getSelectedIndex();

        if (choice == 0) // Resume
        {
            soundManager.playSound("mouse_click");
            resumeGame();
        }
        else if (choice == 1) // Restart
        {
            soundManager.playSound("mouse_click");
            resetGame();
        }
        else // Quit to main menu
        {
            soundManager.playSound("mouse_click");
            resetGame();
            showMainMenu();
            state = State::MainMenu;
        }
    }
}