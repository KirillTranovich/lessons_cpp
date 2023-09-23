#include <iostream>
#include <vector>
#include <limits>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

vector<int> Data_Input(vector<int> coins_left)
{
    bool data_correct = false;
    vector<int> player_input = {0, 0};
    int a = -1;
    int b = -1;
    while (not data_correct)
    {
        data_correct = true;
        cout << "Enter two digits: \nFirst in range[1;3]\nSecond should be not higher than number of coins in row a";
        cout << "\n";
        cin >> a >> b;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Something is wrong with input data. Please try again\n\n";
            data_correct = false;
            continue;
        }
        player_input[0] = a;
        player_input[1] = b;
        cin.clear();
        if (not((1 <= a) and (a <= 3)))
        {
            data_correct = false;
            cout << "Something is wrong with input data. Please try again\n\n";
            continue;
        }
        if (not((1 <= b) and (b <= coins_left[a - 1])))
        {
            data_correct = false;
            cout << "Something is wrong with input data. Please try again\n\n";
            continue;
        }
    }
    cout << "\n\n\n";
    return player_input;
}

void Current_Game_Board(vector<int> rows)
{
    cout << "Rows:\n\n";
    for (int i = 0; i <= 2; ++i)
    {
        cout << "Row " << i + 1 << ": ";
        for (int k = 0; k <= rows[i] - 1; ++k)
        {
            cout << "($) ";
        }
        cout << "\n\n\n";
    }
}

vector<int> Player_Turn(vector<int> rows, vector<int> input)
{
    sleep(1.5);
    for (int i = 0; i < input[1]; ++i)
    {
        rows[input[0] - 1] = rows[input[0] - 1] - 1;
        Current_Game_Board(rows);
        cout << "Your Turn\n\n";
        sleep(1.5);
    }
    return rows;
}

bool Check_Game(vector<int> rows)
{
    for (int i = 0; i < 3; ++i)
    {
        if (rows[i] != 0)
            return true;
    }
    return false;
}

vector<int> Bot_Input(vector<int> rows)
{
    vector<int> comp_choice{0, 0};
    for (int i = 0; i < 3; ++i)
    {
        if (rows[i] >= 1)
        {
            for (int k = 1; k <= rows[i]; ++k)
            {
                switch (i)
                {
                case 0:
                    if (((rows[i] - k) ^ rows[1] ^ rows[2]) == 0)
                    {
                        comp_choice = {i, k};
                        return comp_choice;
                    }
                    break;
                case 1:
                    if (((rows[i] - k) ^ rows[0] ^ rows[2]) == 0)
                    {
                        comp_choice = {i, k};
                        return comp_choice;
                    }
                    break;
                case 2:
                    if (((rows[i] - k) ^ rows[0] ^ rows[1]) == 0)
                    {
                        comp_choice = {i, k};
                        return comp_choice;
                    }
                    break;
                }
            }
        }
    }
    if (comp_choice[0] == 0)
    {
        for (int i = 0; i < 3; ++i)
        {
            if (not rows[i] == 0)
            {
                return {i, 1};
                break;
            }
        }
    }
    return {0, 0};
}

vector<int> Bot_Turn(vector<int> rows)
{

    Current_Game_Board(rows);
    sleep(1.5);
    vector<int> input = Bot_Input(rows);
    for (int i = 0; i < input[1]; ++i)
    {
        rows[input[0]] = rows[input[0]] - 1;
        Current_Game_Board(rows);
        cout << "Computer is making a move\n\n";
        sleep(1.5);
    }
    return rows;
}

int main()
{
    vector<int> input;
    vector<int> rows{3, 4, 5};
    bool Game_Is_On = true;
    while (Game_Is_On)
    {
        Current_Game_Board(rows);
        input = Data_Input(rows);
        rows = Player_Turn(rows, input);
        Game_Is_On = Check_Game(rows);
        if (not Game_Is_On)
        {
            cout << "\n\n\n\n\n\nPlayer wins!!!\n\n\n\n\n\n";
            break;
        }
        rows = Bot_Turn(rows);
        Game_Is_On = Check_Game(rows);
        if (not Game_Is_On)
        {
            cout << "\n\n\n\n\n\nComputer wins!!!\n\n\n\n\n\n";
            break;
        }
    }
    return 0;
}
