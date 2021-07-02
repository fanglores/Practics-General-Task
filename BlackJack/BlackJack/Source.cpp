#include <iostream>
#include "GameEntities.cpp"
using namespace std;

int main()
{
	Menu menu;

	int code = menu.MainMenu();
	if (code == 0) return 0;
	
	Player* player_array = new Player[code];

	Deck deck;
	menu.GameMenu(player_array, &deck);

}