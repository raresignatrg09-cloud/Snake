#pragma once
#include <vector>
#include <string>

class Menu
{
public:
	Menu();

	void setItems(const std::vector<std::string>& menuItems);
	void moveUp();
	void moveDown();

	int getSelectedIndex() const;
	const std::vector<std::string>& getItems() const;
private:
	std::vector<std::string> items;
	int selectedIndex;
};

