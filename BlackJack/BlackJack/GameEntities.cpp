#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <Windows.h>
#include <conio.h>
using namespace std;

class Deck
{
private:
    double shuffleFraction;
    const vector<string> card_dict = { "A", "6", "7", "8", "9", "10", "V", "Q", "K" };
    vector<int> shuffled_deck;

public:
    Deck()
    {
        srand(time(NULL));
        shuffleFraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
        ShuffleDeck();
    }

    void ShuffleDeck()
    {
        vector<int> cnt(9, 0);
        int i;

        while (shuffled_deck.size() < 36)
        {
            i = static_cast<int>(rand() * shuffleFraction * cnt.size());
            if(cnt[i] < 4) shuffled_deck.push_back(i);

            cnt[i]++;
        }
    }

    void DeckFlush()
    {
        shuffled_deck.clear();
        ShuffleDeck();
    }

    int getCard()
    {
        int tmp = shuffled_deck.back();
        shuffled_deck.pop_back();

        return tmp;
    }

    string decodeCard(int n)
    {
        return card_dict[n];
    }
};

class Player
{
private:
    vector<int> card_flow;
    int cardsTaken = 0;
    int card_sum = 0;
    int aces_cnt = 0;

    int Score = 0;

public:
    string name;

    Player()
    {
        static int player_cnt = 1;
        name = string("Игрок" + to_string(player_cnt));
        card_flow.resize(0);
        player_cnt++;
    }

    int getCardSum()
    {
        int sum = card_sum;
        int aces_cnt = this->aces_cnt;

        while (sum > 21 && aces_cnt > 0)
        {
            sum -= 10;
            aces_cnt--;
        }
        
        return sum;
    }

    void printCardSet(Deck* deck)
    {
        for (int i = 0; i < cardsTaken; i++)
            cout << deck->decodeCard(card_flow[i]) << " ";
    }

    void takeCard(int c)
    {
        cardsTaken++;
        card_flow.push_back(c);

        if (c == 0)
        {
            card_sum += 11;
            aces_cnt++;
        }
        else if (c >= 6) card_sum += (c - 4);
        else card_sum += (c + 5);
    }

    string getFirstCard(Deck* deck)
    {
        return deck->decodeCard(card_flow.front());
    }

    void PlayerFlush()
    {
        card_flow.clear();
        cardsTaken = 0;
        card_sum = 0;
        aces_cnt = 0;
    }

    int getCardsTaken()
    {
        return cardsTaken;
    }

    void setScore()
    {
        Score++;
    }

    int getScore()
    {
        return Score;
    }

};

class Menu
{
private:
    int playerCount = 1;
    int gameCount = 0;

public:

    Menu(int Width, int Height)
    {
        _COORD coord;
        coord.X = Width;
        coord.Y = Height;

        _SMALL_RECT Rect;
        Rect.Top = 0;
        Rect.Left = 0;
        Rect.Bottom = 800;
        Rect.Right = 600;

        HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleScreenBufferSize(Handle, coord);
        SetConsoleWindowInfo(Handle, TRUE, &Rect);

        HWND console = GetConsoleWindow();
        RECT r;
        GetWindowRect(console, &r);
        MoveWindow(console, r.left, r.top, 800, 600, TRUE);

    }

    int secure_cin()
    {
        string str;
        getline(cin, str);
        if (str.size() > 1) return -1;
        else
        {
            if (str[0] >= '0' && str[0] <= '9') return (str[0] - '0');
            else return -1;
        }
    }

    void sys_pause(string out)
    {
        string tmp;
        cout << out << endl;
        cin.clear();
        cin.sync();
        _getch();
    }

    int MainMenu()
    {
        int ans;
        
        while (true)
        {
            system("cls");
            cout << "Добро пожаловать в игру 21!" << endl << endl;
            cout << "1. Одиночная игра\n2. Совместная игра\n3. Правила игры\n0. Выход" << endl << endl;
            cout << "Введите цифру: ";

            ans = secure_cin();
            cout << endl;

            switch (ans)
            {
            case 0:
                cout << "Завершение работы игры..." << endl << "Надеемся увидеть Вас снова!" << endl;
                return 0;

            case 1:
                playerCount = 1;
                return playerCount;
            case 2:
                while (true)
                {
                    cout << "Введите количество игроков (не больше 7): ";
                    playerCount = secure_cin();
                    if (playerCount >= 1 && playerCount <= 7) return playerCount;
                    else
                    {
                        cout << "Ошибка ввода. Попробуйте ещё раз" << endl;
                        sys_pause("Нажмите любую клавишу, чтобы повторить ввод...");
                        system("cls");
                    }
                }
                break;
            case 3:
                PrintRules();
                sys_pause("Для возврата в главное меню нажмите любую клавишу...");
                break;
            default:
                cout << "Ошибка ввода. Попробуйте ещё раз" << endl;
                sys_pause("Нажмите любую клавишу, чтобы повторить ввод...");
                break;
            }
        }
    }

    void GameMenu(Player* players, Deck* deck)
    {
        Player dealer;
        dealer.name = "Крупье";
        int ans = 1;

        while (ans == 1)
        {
            gameCount++;
            system("cls");
            GameFlush(&dealer, players, deck);

            for (int i = 0; i < playerCount; i++) players[i].takeCard(deck->getCard());
            dealer.takeCard(deck->getCard());

            for (int i = 0; i < playerCount; i++) players[i].takeCard(deck->getCard());
            dealer.takeCard(deck->getCard());

            if (dealer.getCardSum() == 21)
            {
                cout << "У крупье 21! Пересдача..." << endl;
                sys_pause("Для перезапуска игры нажмите любую клавишу...");
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

                    if (ps < 21)
                    {
                        if(ds > 21)
                        {
                            cout << players[i].name << " выигрывает!" << endl;
                            players[i].setScore();
                        }
                        else
                        {
                            if (ps > ds)
                            {
                                cout << players[i].name << " выигрывает!" << endl;
                                players[i].setScore();
                            }
                            else if (ps < ds)
                            {
                                cout << players[i].name << " проигрывает!" << endl;
                                dealer.setScore();
                            }
                            else
                            {
                                cout << "Ничья!" << endl;
                            }
                        }
                    }
                    else if (ps == 21)
                    {
                        if (ds == 21)
                        {
                            cout << "Ничья!" << endl;
                        }
                        else
                        {
                            cout << players[i].name << " выигрывает!" << endl;
                            players[i].setScore();
                        }
                    }
                    else
                    {
                        if (ds > 21)
                        {
                            cout << "Ничья!" << endl;
                        }
                        else 
                        { 
                            cout << players[i].name << " проигрывает!" << endl; 
                            dealer.setScore();
                        }
                    }
                }

                cout << endl << "Всего игр - " << gameCount << ";" << endl << "Общий счёт побед: " << endl;
                cout << "Крупье - " << dealer.getScore() << "; " << endl;
                for (int i = 0; i < playerCount; i++)
                {
                    cout << players[i].name << " - " << players[i].getScore() << "; ";
                    if (i % 3 == 2 && i != playerCount - 1) cout << endl;
                }
                cout << endl << endl;

                ans = 0;
                while (ans != 1 && ans != 2)
                {
                    //выход в главное меню?
                    cout << "Сыграть ещё раз?\n1. Играть\n2. Выйти из игры\n\nВведите цифру: ";

                    ans = secure_cin();

                    if (ans != 2 && ans != 1)
                    {
                        cout << "Ошибка ввода. Попробуйте ещё раз" << endl;
                        sys_pause("Нажмите любую клавишу, чтобы повторить ввод...");
                    }
                    system("cls");
                }
            }
        }
    }

    void TurnMenu(Player* dealer, Player* players, Deck* deck, int playerNumber)
    {
        int ans = 0;
        Player* player = &players[playerNumber];

        system("cls");
        PrintStats(dealer, players, deck, playerNumber);

        while (player->getCardSum() < 21 && player->getCardsTaken() < 5)
        {
            system("cls");
            PrintStats(dealer, players, deck, playerNumber);
            cout << "Сделайте ход:\n1. Добрать\n2. Закончить ход\n\n>>";

            ans = secure_cin();

            if (ans == 1)
            {
                player->takeCard(deck->getCard());
                PrintStats(dealer, players, deck, playerNumber);
            }
            else if (ans == 2) break;
            else
            {
                cout << "Ошибка ввода. Попробуйте ещё раз" << endl;
                sys_pause("Нажмите любую клавишу, чтобы повторить ввод...");
            }
        }

        if (player->getCardsTaken() == 5) cout << "Рука заполнена! Больше брать нельзя!" << endl;
        if (player->getCardSum() == 21) cout << "21! Вы выиграли!" << endl;
        else if (player->getCardSum() > 21) cout << "Перебор! Вы проиграли!" << endl;

        cout << endl << "Передаем ход следующему игроку..." << endl;
        if (ans == 2) Sleep(1000);
        else sys_pause("Нажмите любую клавишу для подтверждения...");
        system("cls");
    }

    void DealerGame(Player* dealer, Deck* deck)
    {
        while (dealer->getCardSum() < 17 && dealer->getCardsTaken() < 5)
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

        sys_pause("Нажмите любую клавишу, чтобы перейти к подсчёту очков...");
        system("cls");
    }

    void GameFlush(Player* dealer, Player* players, Deck* deck)
    {
        for (int i = 0; i < playerCount; i++)
            players[i].PlayerFlush();
        dealer->PlayerFlush();
        deck->DeckFlush();
    }

    void PrintStats(Player* dealer, Player* players, Deck* deck, int playerNumber)
    {
        system("cls");
        cout << "\t\t\t(Игрок" << playerNumber + 1 << ") " << players[playerNumber].name << " ходит!" << endl;
        cout << "Крупье: " << dealer->getFirstCard(deck) << " X" << endl;

        for (int i = 0; i < playerCount; i++)
            if (i != playerNumber)
            {
                cout << players[i].name << ": ";
                players[i].printCardSet(deck);
                cout << endl;
            }
            else cout << endl;

        if (playerCount > 1) cout << endl;
        cout << "Ваша рука: ";
        players[playerNumber].printCardSet(deck);
        cout << endl << endl;
    }

    void PrintRules()
    {
        system("cls");
        cout << "\t\t\t\tПравила игры" << endl;
        cout << "Каждый игрок получает на руки по две карты." << endl;
        cout << "Любой игрок в свой ход может попросить дополнительную карту, если считает нужным," << endl
            << "или отказаться от нее." << endl
            << "Игрок может иметь на руках не более 5 карт. Игрок, набравший 21 очко, сразу выигрывает." << endl
            << "Игрок, набравший количество очков большее чем 21, автоматически проигрывает" << endl;

        cout << "Игроки набравшие менее 21 очка ждут, пока крупье не доберет карты себе." << endl
            << "Если сумма очков крупье превышает сумму очков игрока, игрок проигрывает." << endl
            << "Если сумма очков крупье меньше суммы очков игрока, игрок выигрывает." << endl
            << "Если количество очков совпадает, то это ничья." << endl << endl;

        cout << "В игре используется стандартная колода из 36 карт." << endl
            << "Номиналы карт: A (туз) - 11 или 1, если сумма карт в руке превышает 21;" << endl
            << "карты от 6 до 10 имеют соответствующий номинал " << endl
            << "V (валет) - 2; Q (дама) - 3; K (король) - 4; X - карта крупье, рубашкой вверх" << endl << endl;

    }

};