#include "GameEntities.cpp"

int main()
{
	setlocale(LC_ALL, "rus");
	Menu mn(100, 300);

	cout << string(100, '=') << "\t\t\tTest 1" << endl << string(100, '=') << endl;

	//Test 1

	cout << "���� �������: ";
	cout << "������� ����� �������: " << mn.secure_cin() << endl << endl;

	cout << "���� ������: ";
	cout << "������� ����� �������: " << mn.secure_cin() << endl << endl;

	cout << "���� ������ 2: ";
	cout << "������� ����� �������: " << mn.secure_cin() << endl << endl;

	cout << "���� �����: ";
	cout << "������� ����� �������: " << mn.secure_cin() << endl << endl;

	cout << "���� �������� �����: ";
	cout << "������� ����� �������: " << mn.secure_cin() << endl << endl;

	cout << "���� �������������� ����� 1: ";
	cout << "������� ����� �������: " << mn.secure_cin() << endl << endl;

	cout << "���� �������������� ����� 2: ";
	cout << "������� ����� �������: " << mn.secure_cin() << endl << endl;

	cout << "���� ����������� ����� 1: ";
	cout << "������� ����� �������: " << mn.secure_cin() << endl << endl;

	cout << "���� ����������� ����� 2: ";
	cout << "������� ����� �������: " << mn.secure_cin() << endl << endl;

	cout << endl << string(100, '=') << "\t\t\tTest 2" << endl << string(100, '=') << endl;

	//Test 2
	Deck dk;

	cout << "��������� ������: ";
	for (int i = 0; i < 36; i++)
		cout << dk.decodeCard(dk.getCard());

	dk.ShuffleDeck();
	cout << endl << "������������ ������: ";
	for (int i = 0; i < 36; i++)
		cout << dk.decodeCard(dk.getCard());

	dk.DeckFlush();
	cout << endl << "��������� ������: ";
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
����� �������?
����� � ������� ����?
������������� �����?
*/