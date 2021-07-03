#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <Windows.h>
using namespace std;

#define _CRT_SECURE_NO_WARNINGS

class Deck
{
private:
    double shuffleFraction;
    const string card_dict[14] = { "err", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "V", "Q", "K"};

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
    int Score = 100;

public:
    string name;

    Player()
    {
        static int player_cnt = 1;
        name = string("Игрок" + to_string(player_cnt));
        card_set.resize(14, 0);
        player_cnt++;
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
            {
                //Sleep(600);
                cout << deck->decodeCard(c) << " ";
            }
    }

    void takeCard(int c)
    {
        //card overtake
        if (card_flow.size() >= 5)
        {
            cout << "Больше нельзя!";
        }

        card_flow.push_back(c);
        card_set[c]++;
        if (c == 1) card_sum += 11;
        else if (c >= 11) card_sum += c % 9;
        else card_sum += c;
    }

    string getFirstCard(Deck* deck)
    {
        return deck->decodeCard(card_flow.front());
    }

    void PlayerFlush()
    {
        card_set.clear();
        card_set.resize(14, 0);
        card_flow.clear();
        card_sum = 0;
    }

    void setScore(int d)
    {
        Score += d;
    }

    int getScore()
    {
        return Score;
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
            cout << "Добро пожаловать в игру 21!" << endl << endl;
            cout << "1. Одиночная игра\n2. Совместная игра\n3. Правила игры\n0. Выход" << endl << endl;
            cout << "Введите число: ";

            //INPUT SECURE
            if (scanf("%d", &ans)) cout << "scanf!";
            else cout << "err";

            switch (ans)
            {
            case 0:
                return 0;

            case 1:
                this->playerCount = 1;
                return playerCount;

            case 2:
                cout << "\nВведите количество игроков (не больше 7): ";
                cin >> this->playerCount;
                return playerCount;

            case 3:
                printRules();
                system("pause");
                break;
            default:
                cout << "Ошибка ввода. Попробуйте ещё раз" << endl;
                system("pause");
                break;
            }
        }
    }

    void GameFlush(Player* dealer, Player* players)
    {
        for (int i = 0; i < playerCount; i++)
            players[i].PlayerFlush();
        dealer->PlayerFlush();
    }

    void PrintStats(Player* dealer, Player* players, Deck* deck, int playerNumber)
    {
        system("cls");
        cout << "\t\t\t(Игрок" << playerNumber + 1 << ") " << players[playerNumber].name << " ходит!" << endl;
        cout << "Крупье: ";

        //Sleep(500);
        cout << dealer->getFirstCard(deck);
        //Sleep(500);
        cout << " X" << endl;
        //Sleep(500);

        for (int i = 0; i < playerCount; i++)
            if (i != playerNumber)
            {
                cout << players[i].name << ": ";
                players[i].printCardSet(deck);
                cout << endl;
            }
            else cout << endl;
        
        cout << endl;
        cout << "Ваша рука: ";
        players[playerNumber].printCardSet(deck);
        cout << endl << endl;
        //Sleep(500);
    }

    void DealerGame(Player* dealer, Deck* deck)
    {
        while (dealer->getCardSum() < 17)
        {
            cout << "Сейчас играет крупье..." << endl;
            cout << "Рука крупье: ";
            dealer->printCardSet(deck);
            dealer->takeCard(deck->getCard());
            Sleep(800);
            system("cls");
        }

        cout << "Сейчас играет крупье..." << endl;
        cout << "Рука крупье: ";
        dealer->printCardSet(deck);
        cout << endl << endl;
        cout << "Крупье сыграл. Набранные очки: " << dealer->getCardSum() << "!" << endl << endl;

        system("pause");
        system("cls");
    }

    void GameMenu(Player* players, Deck* deck)
    {
        Player dealer;
        dealer.name = "Крупье";
        int c = 1;
        
        while (c == 1)
        {
            system("cls");
            GameFlush(&dealer, players);

            for (int i = 0; i < playerCount; i++) players[i].takeCard(deck->getCard());
            dealer.takeCard(deck->getCard());

            for (int i = 0; i < playerCount; i++) players[i].takeCard(deck->getCard());
            dealer.takeCard(deck->getCard());

            if (dealer.getCardSum() == 21)
            {
                cout << "У крупье 21! Пересдача...";
                system("pause");
            }
            else
            {
                for (int i = 0; i < playerCount; i++) 
                    TurnMenu(&dealer, players, deck, i);
                
                system("cls");
                DealerGame(&dealer, deck);
                cout << "Очки крупье: " << dealer.getCardSum() << "!\t";
                if (dealer.getCardSum() > 21) cout << "Крупье проигрывает!" << endl;
                else if (dealer.getCardSum() == 21) cout << "Крупье выигрывает!" << endl;
                cout << endl;

                for (int i = 0; i < playerCount; i++)
                {
                    int ds = dealer.getCardSum(), ps = players[i].getCardSum();
                    cout << "(Игрок" << i + 1 << ") " << players[i].name << " набрал " << players[i].getCardSum() << "!\t";
                    
                    //IMPROVE SCORE SYSTEM!!!
                    if (ds > 21)
                    {
                        if (ps < 21) { cout << players[i].name << " выигрывает!" << endl << endl; players[i].setScore(ds - 21); }
                        else if (ps == 21) { cout << players[i].name << " выигрывает!" << endl << endl; players[i].setScore(ps); }
                        else if (ps > ds) { cout << players[i].name << " проигрывает!" << endl << endl; players[i].setScore(ds - ps); }
                        else if (ps < ds) cout << "Ничья!" << endl;
                        else cout << "Ничья!" << endl;
                    }
                    else if (ds == 21)
                    {
                        if (ps != ds) { cout << players[i].name << " проигрывает!" << endl << endl; players[i].setScore(-abs(ds - ps)); }
                        else cout << "Ничья!" << endl;
                    }
                    else
                    {
                        if (ps > 21) { cout << players[i].name << " проигрывает!" << endl << endl; players[i].setScore(ps - 21); }
                        else if (ps == 21) { cout << players[i].name << " выигрывает!" << endl << endl; players[i].setScore(ps); }
                        else if (ps > ds) { cout << players[i].name << " выигрывает!" << endl << endl; players[i].setScore(ps - ds); }
                        else if (ps < ds) { cout << players[i].name << " проигрывает!" << endl << endl; players[i].setScore(ps - ds); }
                        else cout << "Ничья!" << endl;
                    }
                }

                c = 0;
                while (c != 1 && c != 2)
                {
                    cout << "\nСыграть ещё раз?\n1. Играть\n2. Выход\n>>";

                    //INPUT SECURE
                    scanf("%d", &c);

                    if (c != 2 && c != 1) cout << "Ошибка ввода. Попробуйте ещё раз" << endl;
                    system("pause");
                    system("cls");
                }
            }
        }
    
    }

    void TurnMenu(Player* dealer, Player* players, Deck* deck, int playerNumber)
    {
        int ans;
        Player* player = &players[playerNumber];

        while (player->getCardSum() < 21)
        {
            system("cls");
            PrintStats(dealer, players, deck, playerNumber);
            cout << "Сделайте ход:\n1. Добрать\n2. Закончить ход\n\n>>";

            //INPUT SECURE
            scanf("%d", &ans);

            if (ans == 1)
            {
                player->takeCard(deck->getCard());
                PrintStats(dealer, players, deck, playerNumber);
            }
            else if (ans == 2) break;
            else
            {
                cout << "Ошибка ввода. Попробуйте ещё раз" << endl;
                system("pause");
            }
        }

        if (player->getCardSum() == 21) cout << "21! Вы выиграли!" << endl;
        else if (player->getCardSum() > 21) cout << "Перебор! Вы проиграли!" << endl;
        cout << "Передаем ход следующему игроку..." << endl;
        system("pause");
        system("cls");
    }

    void printRules()
    {
        system("cls");
        cout << "\t\t\tПравила игры" << endl;
        cout << "Каждый игрок получает на руки по две карты." << endl;
        cout << "Любой игрок в свой ход может попросить дополнительную карту, если считает нужным, или отказаться от нее." << endl
            << "Игрок может иметь на руках не более 5 карт. Игрок, набравший 21 очко, сразу выигрывает." << endl
            << "Так же сразу выигрывает игрок набравший \"золотое очко\", то есть имеющий на руках двух тузов." << endl
            << "Игрок, набравший количество очков большее чем 21, автоматически проигрывает" << endl;
        cout << "Игроки набравшие менее 21 очка ждут, пока крупье не доберет карты себе." << endl
            << "Если сумма очков крупье превышает сумму очков игрока, он проигрывает." << endl
            << "Если сумма очков крупье меньше суммы очков игрока, игрок выигрывает." << endl << endl;
    }

};