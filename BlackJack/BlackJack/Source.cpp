#include <iostream>
#include "GameEntities.cpp"
using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	Menu menu;

	int code = menu.MainMenu();
	if (code == 0) return 0;
	
	Player* player_array = new Player[code];

	Deck deck;
	menu.GameMenu(player_array, &deck);

}

/*
To do:
Cards description in Rules section
Improve rules as in Rules section
Less pauses
When one player plays dont wait OTHER players?
Input check
*/