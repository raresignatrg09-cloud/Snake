#pragma once

namespace config
{
	constexpr unsigned int GRID_ROWS = 20;
	constexpr unsigned int GRID_COLS = 13;
	constexpr unsigned int GRID_CELL_SIZE = 40;
	constexpr unsigned int WINDOW_WIDTH = GRID_COLS * GRID_CELL_SIZE;
	constexpr unsigned int WINDOW_HEIGHT = GRID_ROWS * GRID_CELL_SIZE;
	constexpr const char* WINDOW_TITLE = "Snake";
	constexpr float SNAKE_SPEED = 0.2f;
	constexpr const char* FONT_PATH = "Font/OpenSans-Regular.ttf";
}