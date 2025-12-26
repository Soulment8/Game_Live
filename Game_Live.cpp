#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>

using namespace std;

void print_field(int row, int coll, char** arr, char** h_arr, int& generation, ofstream& fout);

char** create_arr(int row, int coll)
{
    char** arr = new char* [row];
    for (int i = 0; i < row; i++)
    {
        arr[i] = new char[coll];
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < coll; j++)
        {
            arr[i][j] = '-';
        }
    }
    return arr;
}

void copy_arr(int row, int coll, char** arr, char** h_arr)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < coll; j++)
        {
            arr[i][j] = h_arr[i][j];
        }
    }
}

void new_live(int row, int coll, char** arr, char** h_arr, int generation, ofstream& fout)
{
    for (int i = 0; i < row; i++)
    {
        int i2 = i;
        if (i != 0)
        {
            i2--;
        }
        for (int j = 0; j < coll; j++)
        {
            int q = 2, w = 2;
            int quantity_live = 0;

            int j2 = j;

            if (j != 0)
            {
                j2--;
            }

            for (int x = i2; x < i + q; x++)

            {

                if (i == row - 1)
                {
                    q = 0;
                }
                for (int y = j2; y < j + w; y++)
                {
                    if (j == coll - 1)
                    {
                        w = 0;
                    }
                    if (arr[x][y] == '*')
                    {
                        quantity_live++;

                        if (x == i && y == j)
                        {
                            quantity_live--;
                        }
                    }

                }
            }

            if (arr[i][j] == '*' && quantity_live != 2 && quantity_live != 3)
            {

                h_arr[i][j] = '-';

            }

            else if (arr[i][j] == '-' && quantity_live == 3)
            {
                h_arr[i][j] = '*';
            }


        }
    }
    print_field(row, coll, arr, h_arr, generation, fout);
}

void print_field(int row, int coll, char** arr, char** h_arr, int& generation, ofstream& fout)
{
    
    int all_quantity_live = 0; 
    int history_points = 0;
    if (fout.is_open())
    {
        generation++;

        fout << endl << "Generatoion " << generation << ":" << endl;

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < coll; j++)
            {
                cout << " " << h_arr[i][j] << " ";

                if (h_arr[i][j] == '*')
                {
                    fout << i << " " << j << endl;
                    all_quantity_live++;

                    if (generation > 1 && arr[i][j] == h_arr[i][j])
                    {
                        history_points++;
                    }
                }
            }
            cout << endl;
        }
        
        cout << " Generation: " << generation << " Alive: " << all_quantity_live << endl;
    }
    else
    {
        cout << "Unable to open file" << endl;
    }

    if (all_quantity_live == 0)
    {
        cout << " All cells are dead. Game over! " << endl;
        return 0;
    }
    else if (history_points == all_quantity_live)
    {
        cout << " The world has stagnated. Game over! " << endl;
        return 0;
    }

    Sleep(1000);

    system("cls");

    copy_arr(row, coll, arr, h_arr);

    new_live(row, coll, arr, h_arr, generation, fout);
}


int main(int argc, char** argv)

{
    setlocale(LC_ALL, "Rus");
    ifstream fin("in.txt");
    ofstream fout("history.txt");

    int row = 0, coll = 0;

    int generation = 0, a = 0, s = 0;

    if (fin.is_open())
    {
        fin >> row; fin >> coll;
    }
    else
    {
        cout << "Unable to open file" << endl;
    }

    char** arr = create_arr(row, coll);
    char** h_arr = create_arr(row, coll);;

    while (fin >> a, fin >> s)
    {
        arr[a][s] = '*';
        h_arr[a][s] = '*';
    }

    fin.close();

    print_field(row, coll, arr, h_arr, generation, fout);

    fout << endl << "End Game " << endl << endl;

    for (int i = 0; i < row; i++)
    {
        delete[] arr[i];
        delete[] h_arr[i];
    }
    delete[] arr;
    delete[] h_arr;
}