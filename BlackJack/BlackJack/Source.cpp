#include "GameEntities.cpp"

int main()
{
	setlocale(LC_ALL, "rus");
	
	Deck dk;

	cout << "��������� ������: ";
	for (int i = 0; i < 36; i++)
		cout << dk.decodeCard(dk.getCard());

	dk.ShuffleDeck();
	cout << endl << "��������� ������: ";
	for (int i = 0; i < 36; i++)
		cout << dk.decodeCard(dk.getCard());

	dk.DeckFlush();
	cout << endl << "��������� ������: ";
	for (int i = 0; i < 36; i++)
		cout << dk.decodeCard(dk.getCard());


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
����� �������?
����� � ������� ����?
������������� �����?
*/