#include "Menu.h"

Menu::Menu()
	: selectedIndex(0)
{
}

void Menu::setItems(const std::vector<std::string>& menuItems)
{
	items = menuItems;
	selectedIndex = 0;
}

void Menu::moveUp()
{
	if (selectedIndex > 0)
	{
		selectedIndex--;
	}
}

void Menu::moveDown()
{
	if (selectedIndex < static_cast<int>(items.size()) - 1)
	{
		selectedIndex++;
	}
}

int Menu::getSelectedIndex() const
{
	return selectedIndex;
}

const std::vector<std::string>& Menu::getItems() const
{
	return items;
}
