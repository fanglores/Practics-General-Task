#include "GameEntities.cpp"

int main()
{
	setlocale(LC_ALL, "rus");

	Menu menu(100, 300);

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
fix: система подсчета - когда у дилера перебор, игрок проигрывает

имена игрокам?
выход в главное меню?
унифицировать шрифт?
*/