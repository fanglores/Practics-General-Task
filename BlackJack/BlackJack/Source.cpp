#include "GameEntities.cpp"

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
Русская колода карт Без карт 2..5!!!

имена игрокам?
выход в главное меню?
унифицировать размер консоли и шрифт?
*/