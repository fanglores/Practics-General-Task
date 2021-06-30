#include <iostream>
#include "GameEntities.cpp"
using namespace std;



int main()
{
	Menu menu;

	int code = menu.MainMenu();
	if (code == 0) return 0;
	
	Player* player_array = new Player[code];

	/*
	for (int i = 0; i < code; i++)
	{
		string name;
		cout << "Player" << i + 1 << " enter your name: ";
		cin >> name;
		player_array[i].name = name;
	}
	*/

	Deck deck;
	menu.GameMenu(player_array, &deck);


}