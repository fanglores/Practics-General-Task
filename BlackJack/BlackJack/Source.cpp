#include <iostream>
#include "GameEntities.cpp"
using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	Menu menu;

	int code = menu.MainMenu();
	if (code != 0)
	{
		Player* player_array = new Player[code];

		Deck deck;
		menu.GameMenu(player_array, &deck);
	}

	return 0;
}

/*
To do:
deck from 6 to 10? russian
add name to players?
Improve rules as in Rules section
Less pauses
When one player plays dont wait OTHER players?
*/