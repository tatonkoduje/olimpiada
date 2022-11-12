#include <iostream>
#include <vector>

using namespace std;

int m_wym, p_prze, n_pol;
vector<vector<int>> plansza;
vector<vector<int>> snake = { {0,0,0} };
char initialize_field_value = -1;
string single_command;

int transform_index(int value)
{
    return value - 1;
}


void show_snake(string message)
{
    cout << message << endl;
    cout << "size: " << snake.size() << endl;
    for (auto & i : snake) {
        cout << "[" << i[0] << i[1] << i[2] << "]" << ',';
    }

    cout << endl;
}


void create_area(int size)
{
    plansza.resize(size, vector<int>(size, initialize_field_value));
}


void arrange_snacks(int snacks_count)
{
    // snacks_count < m^2-1, != [0][0], != od poprzeniej pozycji przekaski
    cout << "Podaj dane przekasek. Ilosc: " << snacks_count << endl;

    for (int i = 0; i < snacks_count; i++)
    {
        cout << "Przekaska nr " << i << endl;
        int k, w, c;
        cin >> w >> k >> c;
        cout << "Transformuje na: " << transform_index(w) << " i " << transform_index(k) << endl;
        plansza[transform_index(w)][transform_index(k)] = c;
        cout << "Umiescilem snacka na planszy - kolor > " <<  plansza[transform_index(w)][transform_index(k)] << endl;
    }
}


void snake_eat(int k, int w, int color)
{
    cout << "Znalazlem przekaske o danych: (" << k << w << color << ")" << endl;
    snake.insert(snake.begin(), {k, w, color}); // dokladamy pierwszy elelment czyli glowe w kolorze przekaski z planszy
    plansza[w][k] = -1;
    cout << "Przekaska zjedzona. Pole zmienia wartosc z " << color << " na " <<  plansza[w][k] << endl;
}


void snake_move(int k, int w)
{
    //zmieniamy pozycje elementow od konca
    for(int i =  snake.size() - 1; i > 0; i--)
    {
        snake[i][0] = snake[i-1][0]; //  nowa pozycja x jest prana z poprzedniego elementu
        snake[i][1] = snake[i-1][1]; // nowa pozycja y jest prana z poprzedniego elementu
        snake[i][2] = snake[i][2]; // kolory nigdy sie mnie zmieniaja w kolejnych elementach jesli nei zje przekaski
    }

    // i na koncu mozemy zmodyfikowac element zerowy weza
    snake[0][0] = k; // pozycja x z vectora
    snake[0][1] = w; // pozycja y z vectora
    //snake[0][2] = snake[0][2]; // kolor glowy przy ruchu sie  nie zmienia
}


void snake_action(string direction)
{
    vector<int> move_values = {0, 0};

    if(direction == "P" || direction == "p")
    {
        move_values = {1, 0}; // vector poruszania zmienia sie tylko na x + 1 (y sie nie zmienia)
    }
    else if(direction == "L" || direction == "l")
    {
        move_values = {-1, 0}; // vector poruszania zmienia sie tylko na x - 1
    }
    else if(direction == "G" || direction == "g")
    {
        move_values = {0, -1}; // vector poruszania zmienia sie tylko na y - 1
    }
    else if(direction == "D" || direction == "d")
    {
        move_values = {0, 1}; // vector poruszania zmienia sie tylko na y + 1
    }
    else
    {
        cout << "Nieprawidlowa komenda" << endl;
    }


    show_snake("Waz przed zmianami: ");

    int k = snake[0][0] + move_values[0];
    int w = snake[0][1] + move_values[1];

    if(plansza[w][k] != -1) // jesli nastepna pozycja to snack to..
    {
        snake_eat(k, w, plansza[w][k]);
    }
    else  // a jesli nie to ruszamy wezem
    {
        snake_move(k, w);
    }

    show_snake("Waz po zmianach: ");
}


void command(const string input)
{
    if(input == "Z" || input == "z")
    {
        int w, k;
        cin >> w >> k;
        cout << "Transformuje na: " << transform_index(w) << " i " << transform_index(k) << endl;

        // w calym wezu szukam elementu ktorego w i k sie zgadza z szukanymi. Jesli waz ma taki element to znaczy ze jest na tym polu. Jak nei ma to -1
        bool found = false;
        for(int i = 0; i < snake.size(); i++)
        {
            if(snake[i][0] == transform_index(k) && snake[i][1] == transform_index(w))
            {
                cout << "Znalazlem weza na tym polu. Ma kolor: ";
                cout << "===============================================================> " << snake[i][2] << endl;
                found = true;
                break;
            }
        }

        if(!found)
        {
            cout << "Tu nie ma weza!" << endl;
            cout << "===============================================================> " << -1 << endl;
            cout << "A na planszy jest wartosc: " << plansza[transform_index(w)][transform_index(k)] << endl;
        }
    }
    else
    {
        snake_action(input);
    }
}


void commands(int commands_count) {
    cout << "Ilosc komend do wykorzystania: " << commands_count << endl;

    for (int i = 0;i < commands_count; i++)
    {
        cout << "Podaj komende nr " << i << endl;
        cin >> single_command;
        command(single_command);
    }
}


int main()
{
    cout << "Witaaaajjj!!! Podaj wymiar kwadratowej planszy [m], ilosc przekasek [p] oraz ilosc dostepnych komend [n]:" << endl;
    cin >> m_wym >> p_prze >> n_pol;

    create_area(m_wym);
    arrange_snacks(p_prze);
    commands(n_pol);

    cout << "Dziekuje za gre :D " << endl;

    return 0;
}
