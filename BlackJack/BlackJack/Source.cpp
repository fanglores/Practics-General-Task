#include "GameEntities.cpp"

int main()
{
	setlocale(LC_ALL, "rus");

	vector<long long unsigned int> vect(9, 0);
	Deck dk;

	long long unsigned int i = 0, cnt = 0;

	while (true)
	{
		cnt++;
		vect[dk.getCard()]++;

		if (i == 100000)
		{
			for (long long unsigned int j : vect) cout << (double)j / cnt << " ";
			cout << endl;
		}

		i++;
	}

	/*
	Menu menu(100, 300);

	int code = menu.MainMenu();
	if (code != 0)
	{
		Player* player_array = new Player[code];

		Deck deck;
		menu.GameMenu(player_array, &deck);
	}
	*/
	return 0;
}


/*
To do:
имена игрокам?
выход в главное меню?
унифицировать шрифт?
*/