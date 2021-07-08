#include "GameEntities.cpp"

int main()
{
	setlocale(LC_ALL, "rus");
	Menu mn(100, 300);

	cout << string(100, '=') << "\t\t\tTest 1" << endl << string(100, '=') << endl;

	//Test 1

	cout << "Ввод символа: ";
	cout << "Функция ввода вернула: " << mn.secure_cin() << endl << endl;

	cout << "Ввод строки: ";
	cout << "Функция ввода вернула: " << mn.secure_cin() << endl << endl;

	cout << "Ввод строки 2: ";
	cout << "Функция ввода вернула: " << mn.secure_cin() << endl << endl;

	cout << "Ввод числа: ";
	cout << "Функция ввода вернула: " << mn.secure_cin() << endl << endl;

	cout << "Ввод большого числа: ";
	cout << "Функция ввода вернула: " << mn.secure_cin() << endl << endl;

	cout << "Ввод отрицательного числа 1: ";
	cout << "Функция ввода вернула: " << mn.secure_cin() << endl << endl;

	cout << "Ввод отрицательного числа 2: ";
	cout << "Функция ввода вернула: " << mn.secure_cin() << endl << endl;

	cout << "Ввод корректного числа 1: ";
	cout << "Функция ввода вернула: " << mn.secure_cin() << endl << endl;

	cout << "Ввод корректного числа 2: ";
	cout << "Функция ввода вернула: " << mn.secure_cin() << endl << endl;

	cout << endl << string(100, '=') << "\t\t\tTest 2" << endl << string(100, '=') << endl;

	//Test 2
	Deck dk;

	cout << "Начальная колода: ";
	for (int i = 0; i < 36; i++)
		cout << dk.decodeCard(dk.getCard());

	dk.ShuffleDeck();
	cout << endl << "Перемешанная колода: ";
	for (int i = 0; i < 36; i++)
		cout << dk.decodeCard(dk.getCard());

	dk.DeckFlush();
	cout << endl << "Очищенная колода: ";
	for (int i = 0; i < 36; i++)
		cout << dk.decodeCard(dk.getCard());

	cout << endl << endl << endl;

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