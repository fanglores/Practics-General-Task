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
    const vector<string> card_dict{ "err", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "V", "Q", "K"};

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

    string decodeCard(int n)
    {
        return card_dict[n];
    }
};

class Player
{
private:
    vector<int> card_set, card_flow;
    int card_sum = 0;

public:
    string name;

    Player()
    {
        static int cnt = 1;
        this->name = string("Player" + to_string(cnt));
        card_set.resize(14, 0);
    }

    int getCardSum()
    {
        int sum = card_sum;
        int aces_cnt = card_set[1];

        while (card_sum > 21 && aces_cnt > 0)
        {
            sum -= 10;
            aces_cnt--;
        }
        
        return sum;
    }

    void printCardSet(Deck* deck)
    {
        for (int c = 1; c < 14; c++)
            for (int i = 0; i < card_set[c]; i++)
                cout << deck->decodeCard(c) << " ";   
    }

    void takeCard(int c)
    {
        card_flow.push_back(c);
        card_set[c]++;
        if (c == 1) card_sum += 11;
        else if (c >= 11) card_sum += 10;
        else card_sum += c;
    }

    string getFirstCard(Deck* deck)
    {
        return deck->decodeCard(card_flow.front());
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

    void PrintStats(Player* dealer, Player* players, Deck* deck, int playerNumber)
    {
        system("cls");
        cout << "Dealer: " << dealer->getFirstCard(deck) << " X" << endl;

        for (int i = 0; i < playerCount; i++)
            if (i != playerNumber)
            {
                cout << players[i].name << ": ";
                players[i].printCardSet(deck);
                cout << endl;
            }
        
        cout << endl;
        cout << "Your set is: ";
        players[playerNumber].printCardSet(deck);
        cout << endl << endl;

    }

    void GameMenu(Player* players, Deck* deck)
    {
        Player dealer;
        dealer.name = "Dealer";
        char c = 'Y';
        
        while (c == 'Y')
        {
            system("cls");

            for (int i = 0; i < playerCount; i++) players[i].takeCard(deck->getCard());
            dealer.takeCard(deck->getCard());

            for (int i = 0; i < playerCount; i++) players[i].takeCard(deck->getCard());
            dealer.takeCard(deck->getCard());

            if (dealer.getCardSum() == 21)
            {
                cout << "Dealer got 21! Restarting...";
                system("pause");
            }
            else
            {
                for (int i = 0; i < playerCount; i++) 
                    TurnMenu(&dealer, players, deck, i);
                

                //score count?

                cout << "Want to play again? Y/N\n>>";
                cin >> c;
            }
        }
    
    }

    void TurnMenu(Player* dealer, Player* players, Deck* deck, int playerNumber)
    {
        int ans;
        Player* player = &players[playerNumber];

        PrintStats(dealer, players, deck, playerNumber);

        while (player->getCardSum() < 21)
        {
            cout << "Choose an option:\n1. Hit\n2. Stay\n\n>>";
            cin >> ans;

            if (ans == 1)
            {
                player->takeCard(deck->getCard());
                PrintStats(dealer, players, deck, playerNumber);
            }
            else if (ans == 2) break;
            else cout << "Input error. Try again";
        }

        if (player->getCardSum() == 21) cout << "21! You won!" << endl;
        else if (player->getCardSum() > 21) cout << "Bust! You lose!" << endl;

    }

    void printRules()
    {
        system("cls");
        cout << "\t\t\tRules";
        cout << "coming soon";
    }

};

