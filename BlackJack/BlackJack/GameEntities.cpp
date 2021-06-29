#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <map>
using namespace std;


class Deck
{
private:
    double shuffleFraction;
    map<int, char> card_dict{ {1, 'A'}, {2, '2'}, {3, '3'}, {4, '4'}, {5, '5'}, {6, '6'}, {7, '7'}, {8, '8'}, 
        {9, '9'}, {10, '10'}, {11, 'V'}, {12, 'Q'}, {13, 'K'} };

public:
    Deck()
    {
        srand(time(NULL));
        this->shuffleFraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    }

    int getCard()
    {
        return static_cast<int>(rand() * shuffleFraction * 13 + 1);
    }

    char decodeCard(int n)
    {
        return card_dict[n];
    }
};

class Player
{
private:
    vector<int> card_set;
    int card_sum = 0;

public:
    string name;

    Player()
    {
        card_set.resize(13, 0);
    }

    int getCardSum()
    {
        int sum = 0;
        for (int c = 1; c < 14; c++)
        {
            for (int i = 0; i < card_set[c]; i++)
            {
                if (c == 1) card_sum += 11;
                else if (c >= 11) card_sum += 10;
                else card_sum += c;
            }
        }
        if (sum > 21 && card_set[1] > 0) sum -= 10;
        return sum;
    }

    void printCardSet(Deck* deck)
    {
        for (int i : card_set) cout << deck->decodeCard(i) << " ";
    }

    void takeCard(int c)
    {
        card_set[c]++;
        if (c == 1) card_sum += 11;
        else if (c >= 11) card_sum += 10;
        else card_sum += c;
    }


};


class Menu
{
private:
    int playerCount;

public:
    int MainMenu()
    {
        int ans;
        while (true)
        {
            system("cls");
            cout << "Welcome to the 21 game!" << endl << endl;
            cout << "1. Start solo game\n2. Start cooperative game\n3. Rules\n0. Exit" << endl << endl;
            cout << "Enter the  number: ";

            cin >> ans;

            switch (ans)
            {
            case 0:
                return 0;

            case 1:
                this->playerCount = 1;
                return playerCount;

            case 2:
                cout << "\nEnter the number of players (no more than 7): ";
                cin >> this->playerCount;
                return playerCount;

            case 3:
                printRules();
                system("pause");
                break;
            default:
                cout << "Input error. Try again";
                system("pause");
                break;
            }
        }
    }

    void GameMenu(Player* players, Deck* deck)
    {
        Player dealer;
        dealer.name = "Dealer";
        char c = 'Y';
        
        while (c == 'Y')
        {
            for (int i = 0; i < playerCount; i++) players[i].takeCard(deck->getCard());
            dealer.takeCard(deck->getCard());

            for (int i = 0; i < playerCount; i++) players[i].takeCard(deck->getCard());
            dealer.takeCard(deck->getCard());

            for (int i = 0; i < playerCount; i++) TurnMenu(&players[i], deck);



            //score count?

            cout << "Want to play again? Y/N\n>>";
            cin >> c;
        }
    
    }

    void TurnMenu(Player* player, Deck* deck)
    {
    
    }

    void printRules()
    {
        system("cls");
        cout << "\t\t\tRules";
        cout << "coming soon";
    }

};

