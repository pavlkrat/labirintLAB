// LABIRINT.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <queue>

using namespace std;

const size_t x = 3, y = 15, z = 25;
int color = -1, stx = -1, sty = -1;
char A[x][y][z];
pair<int, int> elev[x];
char cl[x];

void inp_color()
{
    string s;
    while (color == -1)
    {
        cout << "Enter colour(red, green, blue):\n";
        getline(cin, s);
        if (s == "red")
            color = 0;
        else if (s == "green")
            color = 1;
        else if (s == "blue")
            color = 2;
    }
}

void inp_x()
{
    while (stx < 0 || stx >= y)
    {
        cout << "Enter x(between 0 and " << y - 1 << "):\n";
        cin >> stx;
    }
}

void inp_y()
{
    while (sty < 0 || sty >= z)
    {
        cout << "Enter y(between 0 and " << z - 1 << "):\n";
        cin >> sty;
    }
}

void init_mat()
{
    elev[0] = { 0,z / 2 };
    elev[1] = { y - 1,0 };
    elev[2] = { y / 2,z - 1 };
    cl[0] = 'R';
    cl[1] = 'G';
    cl[2] = 'B';
    for (int i = 0;i < x;i++)
    {
        for (int j = 0;j < y;j++)
            for (int k = 0;k < z;k++)
                A[i][j][k] = cl[i];
        A[i][elev[i].first][elev[i].second] = '&';
    }
    A[x - 1][elev[x - 1].first][elev[x - 1].second] = 'F';
    A[0][1][3] = A[0][2][5] = A[0][4][2] = A[0][6][1] = A[0][8][11] = A[0][11][13] = A[0][12][19] = 'X';
    A[1][1][3] = A[1][y - 1][4] = A[1][y - 6][12] = A[1][y - 2][0] = A[1][y - 4][0] = A[1][12][19] = 'X';
    A[2][1][3] = A[2][y - 3][5] = A[2][7][7] = A[2][6][0] = A[2][y - 1][11] = A[2][y - 1][13] = 'X';
    //A[2][y / 2 + 1][z - 1] = A[2][y / 2 - 1][z - 1] = A[2][y / 2][z - 2] = 'X';  //блокирует выход
}

void print_floor(int v)
{
    for (int j = 0;j < y;j++)
    {
        for (int k = 0;k < z;k++)
            cout << A[v][j][k] << " ";
        cout << "\n";
    }
    cout << "\n";
}

void get_way(int v, int ai, int aj)
{
    if (make_pair(ai, aj) == elev[v])
        return;
    A[v][ai][aj] = 'S';
    pair<int, int> pr[y][z];
    for (int j = 0;j < y;j++)
        for (int k = 0;k < z;k++)
            pr[j][k] = { -1,-1 };
    queue<pair<int, int> > q;
    q.push({ ai,aj });
    pr[ai][aj] = { -2,-2 };
    int curi, curj;
    while (!q.empty())
    {
        curi = q.front().first;
        curj = q.front().second;
        if (curi == elev[v].first && curj == elev[v].second)
            break;
        if (curi > 0 && pr[curi-1][curj] == make_pair(-1,-1) && A[v][curi-1][curj] != 'X')
        {
            q.push({ curi - 1,curj });
            pr[curi - 1][curj] = { curi,curj };
        }
        if (curi < y - 1 && pr[curi + 1][curj] == make_pair(-1, -1) && A[v][curi + 1][curj] != 'X')
        {
            q.push({ curi + 1,curj });
            pr[curi + 1][curj] = { curi,curj };
        }
        if (curj > 0 && pr[curi][curj - 1] == make_pair(-1, -1) && A[v][curi][curj - 1] != 'X')
        {
            q.push({ curi,curj - 1 });
            pr[curi][curj - 1] = { curi,curj };
        }
        if (curj < z - 1 && pr[curi][curj + 1] == make_pair(-1, -1) && A[v][curi][curj + 1] != 'X')
        {
            q.push({ curi,curj + 1 });
            pr[curi][curj + 1] = { curi,curj };
        }
        q.pop();
    }
    curi = pr[elev[v].first][elev[v].second].first;
    curj = pr[elev[v].first][elev[v].second].second;
    if (curi == -1)
    {
        print_floor(v);
        cout << "Impossible!";
        exit(0);
    }
    while (pr[curi][curj].first != -2)
    {
        A[v][curi][curj] = '-';
        int tmp = curi;
        curi = pr[curi][curj].first;
        curj = pr[tmp][curj].second;
    }
}

void do_cycle()
{
    get_way(color, stx, sty);
    print_floor(color);
    for (int i = color + 1;i < x;i++)
    {
        get_way(i, elev[i - 1].first, elev[i - 1].second);
        print_floor(i);
    }
}

int main()
{
    inp_color();
    inp_x();
    inp_y();
    init_mat();
    do_cycle();
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
