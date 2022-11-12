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


void create_area(int size)
{
    plansza.resize(size, vector<int>(size, initialize_field_value));
}


void arrange_snacks(int snacks_count)
{
    for (int i = 0; i < snacks_count; i++)
    {
        int k, w, c;
        cin >> w >> k >> c;
        plansza[transform_index(w)][transform_index(k)] = c;
    }
}


void snake_eat(int k, int w, int color)
{
    snake.insert(snake.begin(), {k, w, color});
    plansza[w][k] = -1;
}


void snake_move(int k, int w)
{
    for(int i =  snake.size() - 1; i > 0; i--)
    {
        snake[i][0] = snake[i-1][0];
        snake[i][1] = snake[i-1][1];
        snake[i][2] = snake[i][2];
    }

    snake[0][0] = k;
    snake[0][1] = w;
    snake[0][2] = snake[0][2];
}


void snake_action(string direction)
{
    vector<int> move_values = {0, 0};

    if(direction == "P" || direction == "p")
    {
        move_values = {1, 0};
    }
    else if(direction == "L" || direction == "l")
    {
        move_values = {-1, 0};
    }
    else if(direction == "G" || direction == "g")
    {
        move_values = {0, -1};
    }
    else if(direction == "D" || direction == "d")
    {
        move_values = {0, 1};
    }

    vector<int> next_head_position;
    int k = snake[0][0] + move_values[0];
    int w = snake[0][1] + move_values[1];

    if(plansza[w][k] != -1)
    {
        snake_eat(k, w, plansza[w][k]);
    }
    else
    {
        snake_move(k, w);
    }
}


void command(const string input)
{
    if(input == "Z" || input == "z")
    {
        int w, k;
        cin >> w >> k;

        bool found = false;
        for(int i = 0; i < snake.size(); i++)
        {
            if(snake[i][0] == transform_index(k) && snake[i][1] == transform_index(w))
            {
                cout << snake[i][2] << endl;
                found = true;
                break;
            }
        }

        if(!found)
        {
            cout << -1 << endl;
        }
    }
    else
    {
        snake_action(input);
    }
}


void commands(int commands_count) {
    for (int i = 0;i < commands_count; i++)
    {
        cin >> single_command;
        command(single_command);
    }
}


int main()
{
    cin >> m_wym >> p_prze >> n_pol;

    create_area(m_wym);
    arrange_snacks(p_prze);
    commands(n_pol);

    return 0;
}
