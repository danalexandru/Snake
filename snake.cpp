#include<stdio.h>
#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<conio.h>
#include<time.h>
using namespace std;
#define M 21
#define N 42

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

#define NUM8 56
#define NUM4 52
#define NUM6 54
#define NUM2 50

struct position{
    int x;
    int y;
    };
int start()
{
    cout<<"Welcome to Snake(1.0)!"<<endl;
    cout<<"Would you like to play?(Y/N)";
    char ch;
    ch = getch();
    while (ch != 'y' && ch != 'Y' && ch != 'n' && ch != 'N')
    {
        cout<<"You have introduced an odd character! Please try again!"<<endl;
        cout<<"Would you like to play?(Y/N)";
        fflush(stdin);
        ch = getch();
    }
    if (ch == 'y' || ch == 'Y') return 1;
    else return 0;
}
int **initializare(int **a, position f1)
{
    a = new int*[M];
    for (int i=0;i<M;i++)
    {
        a[i] = new int[N];
        for (int j=0;j<N;j++)
        {
            if (i == 0 || i == M-1) a[i][j] = -1;
            else if (j == 0 || j == N-1) a[i][j] = -2;
            else if (i == 10 && j >= 18 && j <= 22) a[i][j] = 1;
            else if (i == f1.x && j == f1.y) a[i][j] = 1;
            else a[i][j] = 0;
        }
    }
    return a;
}
position *initializare(position *v)
{
    v = (position*)malloc(5*sizeof(position));;
    for (int i=0;i<5;i++)
    {
        v[i].x = 10;
        v[i].y = 22 - i;
    }
    return v;
}
position food(position f1, position *v, int dim)
{
    f1.x = rand() % (M - 2) + 1;
    f1.y = rand() % (N - 2) + 1;
    int k = 0;
    while (k == 0)
    {
        k = 1;
        for (int i=0;i<dim;i++)
        {
            if (v[i].x == f1.x && v[i].y == f1.y){
                f1.x = rand() % (M - 2) + 1;
                f1.y = rand() % (N - 2) + 1;
                k = 0;
            }
        }
    }
    return f1;
}
int **modifica(int **a, position *v, int dim, position f1)
{
    int e;
    for (int i=0;i<M;i++)
        for (int j=0;j<N;j++)
        {
            if (i == 0 || i == M - 1) a[i][j] = -1;
            else if (j == 0 || j == N - 1) a[i][j] = -2;
            else if (i == f1.x && j == f1.y) a[i][j] = 1;
            else {
                    e = 0;
                for (int k=0;k<dim;k++)
                    if (i == v[k].x && j == v[k].y)
                            e  = 1;
                    a[i][j] = e;
            }
        }
    return a;
}
int game_over(position *v, int dim)
{
    for (int i=1;i<dim;i++)
        for (int j=0;j<i;j++)
        if (v[i].x == v[j].x && v[i].y == v[j].y) return 0;
    return 1;
}
void afiseaza(int **a)
{
    cout<<"Control Keys: "<<endl;
    cout<<"|     W     |      |     "<<char(56)<<"     |"<<endl;
    cout<<"|  A  S  D  |  or  |  "<<char(52)<<"  "<<char(50)<<"  "<<char(54)<<"  |"<<endl<<endl;
    for (int i=0;i<M;i++)
    {
        for (int j=0;j<N;j++)
        {
            if (a[i][j] == -1) cout<<"_";
            else if (a[i][j] == -2) cout<<"|";
            else if (a[i][j] == 1) cout<<"*";
            else if (a[i][j] == 0) cout<<" ";
        }
        cout<<endl;
    }
}
position *move_snake(position *v, int ver, int dim)
{
    if (ver == 1)
    {
        for (int i=dim-1;i>0;i--)
            {
                v[i].y = v[i-1].y;
                v[i].x = v[i-1].x;
            }
        v[0].x--;
    }
    if (ver == 2)
    {
        for (int i=dim-1;i>0;i--)
           {
                v[i].y = v[i-1].y;
                v[i].x = v[i-1].x;
            }
        v[0].y--;
    }
    if (ver == 3)
    {
        for (int i=dim-1;i>0;i--)
           {
                v[i].y = v[i-1].y;
                v[i].x = v[i-1].x;
            }
        v[0].x++;
    }
    if (ver == 4)
    {
        for (int i=dim-1;i>0;i--)
            {
                v[i].y = v[i-1].y;
                v[i].x = v[i-1].x;
            }
        v[0].y++;
    }
    return v;
}
position *control(int **a, position *v, int dim, int &este)
{
    char ch;
    ch = getch();
    if (ch == 'w' || ch == 'W' || ch == KEY_UP || ch == NUM8)
        {
            if (v[0].x != 1) v = move_snake(v, 1, dim);
            else este = 0;
            }
    if (ch == 'a' || ch == 'A' || ch == KEY_LEFT || ch == NUM4)
        {
            if (v[0].y != 1) v = move_snake(v, 2, dim);
            else este = 0;
            }
    if (ch == 's' || ch == 'S' || ch == KEY_DOWN || ch == NUM2)
        {
            if (v[0].x != M-2) v = move_snake(v, 3, dim);
            else este = 0;
            }
    if (ch == 'd' || ch == 'D' || ch == KEY_RIGHT || ch == NUM6)
        {
            if (v[0].y != N-2) v = move_snake(v, 4, dim);
            else este = 0;
            }
            return v;
}
int main()
{
    int start_game = start();
    if (start_game == 0){
        system("cls");
        cout<<"Ok! Have a nice day!"<<endl;
    }
    else{
    int **a, dim = 5, este = 1, score = 0, hscore;
    FILE *f = fopen("highscore.bin", "rb");
    fread(&hscore, sizeof(int), 1, f);
    fclose(f);
    position *v, f1;
    v = initializare(v);
    f1 = food(f1, v, dim);
    a = initializare(a, f1);
    system("cls");
    afiseaza(a);
    srand(time(NULL));
    cout<<endl;
    cout<<"Score: "<<score<<endl;
    cout<<"Highscore: "<<hscore<<endl;
    while(este == 1)
    {
        if (v[0].x == f1.x && v[0].y == f1.y)
        {
            dim++;
            v = (position*)realloc(v, dim*sizeof(position));
            f1 = food(f1, v, dim);
            score += 10;
        }
        v = control(a, v, dim, este);
        este = game_over(v, dim);
        if (este == 0) {
                system("cls");
                cout<<"You're score: "<<score<<endl;
                cout<<"Highscore: "<<hscore<<endl;
                if (score > hscore)
                {
                    f = fopen("highscore.bin", "wb");
                    fwrite(&score, sizeof(int), 1, f);
                    fclose(f);
                }
        }
        else {a = modifica(a, v, dim, f1);
        system("cls");
        afiseaza(a);
        cout<<endl;
        cout<<"Score: "<<score<<endl;
        cout<<"Highscore: "<<hscore<<endl;
        }
        }
    }
}
