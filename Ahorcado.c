#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const char player1[8] = "\033[92m"; //Verde
const char player2[8] = "\033[94m"; //Cyan
const char reset[8] = "\033[37m";   //Blanco

void print_scr();
void update_scr();
void scan_scr();
void bot_start();
void bot_logic();

int board [3][3] = {{0,0,0},
                    {0,0,0},
                    {0,0,0}};
int pos_temp[9][2];
int tempx;
int tempy;
int result = 0;
int player = 1;

int main()
{
    srand(time(NULL));
    bot_start();

    while (result == 0)
    {
        print_scr();
        //update_scr();
        bot_logic();
        scan_scr();
        system("pause");
    }
    system("cls");
    if (result == 1)
    {
        printf (player1);
        printf ("Ha ganado el jugador 1!\n\n");
        printf (reset);
    }else if (result == 2)
    {
        printf (player2);
        printf ("Ha ganado el jugador 2!\n\n");
        printf (reset);
    }
    system("pause");
    return 0;
}

void print_scr(){
    system("cls");
    if (player == 1)
    {
        printf (player1);
        printf ("Jugador 1\n");
        printf (reset);
    }else if (player == 2)
    {
        printf (player2);
        printf ("Jugador 2\n");
        printf (reset);
    }
    for (int i = 0; i < 4; i++)
    {
        printf ("\n");
        if (i != 0)
            printf ("%d " , i);
        for (int l = 0; l < 4; l++)
        {
            if (i == 0 && l != 0)
                printf (" %d" , l);
            else if (i == 0 && l == 0)
                printf ("  ");
            else if (l != 0)
                printf ("|");
            if (board[i-1][l-1] == 1 && i != 0 && l != 0)
            {
                printf (player1);
                printf ("X");
                printf (reset);
                }
            else if (board[i-1][l-1] == 2 && i != 0 && l != 0)
            {
                printf (player2);
                printf ("O");
                printf (reset);
            }
            else if (board[i-1][l-1] == 0 && i != 0 && l != 0)
                printf ("_");
        }
        if (i != 0)
        {
            printf ("|");
        }
    }
    printf ("\n");
}

void update_scr(){
    int err = 0;
    do{    
        int x,y;
        printf ("\n");
        if (err == 1)
        {
            printf ("coordenada incorrecta\n");
        }
        printf ("Introduce la coordenada (X): ");
        scanf_s ("%d", &x);
        printf ("Introduce la coordenada (Y): ");
        scanf_s ("%d", &y);
        if (board[x-1][y-1] != 0)
            err = 1;
        else {
            board[x-1][y-1] = player;
            err = 0;
        }
        if (player == 1 && err == 0)
            player = 2;
        else if (player == 2 && err == 0)
            player = 1;
    }while (err != 0);
}

void scan_scr(){
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == 1 && board[i][1] == 1 && board[i][2] == 1 || board[0][i] == 1 && board[1][i] == 1 && board[2][i] == 1)
            result = 1;
        else if (board[i][0] == 2 && board[i][1] == 2 && board[i][2] == 2 || board[0][i] == 2 && board[1][i] == 2 && board[2][i] == 2)
            result = 2;
    }
    if (board[0][0] == 1 && board[1][1] == 1 && board[2][2] == 1 || board[0][2] == 1 && board[1][1] == 1 && board[2][0] == 1)
        result = 1;
    else if (board[0][0] == 2 && board[1][1] == 2 && board[2][2] == 2 || board[0][2] == 2 && board[1][1] == 2 && board[2][0] == 2)
        result = 2;
}

void bot_start(){
    int pos = 0;
    for (int i = 0; i < 3; i++) {
        for (int l = 0; l < 3; l++) {
            if (board[i][l] == 0)
                pos_temp[pos][0] = i;
                pos_temp[pos][1] = l;
                pos++;
        }
    }
    if (pos > 0) {
        int rand_n = rand() % pos;
        tempx = pos_temp[rand_n][0];
        tempy = pos_temp[rand_n][1];
        board[tempx][tempy] = 2;
    }
}

void bot_logic(){
    int pos = 0;
    for (int i = -1; i <= 1; i++) {
        for (int l = -1; l <= 1; l++) {
            if (board[tempx + i][tempy + l] == 0 && tempx + i >= 0 && tempy + l >= 0 && tempx + i <= 2 && tempy + l <= 2){
                pos++;
            }
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int l = 0; l < 3; l++) {
            if (board[i][l] == 0)
                pos_temp[pos][0] = i;
                pos_temp[pos][1] = l;
                pos++;
        }
    }
    if (pos > 0) {
        int rand_n = rand() % pos;
        tempx = pos_temp[rand_n][0];
        tempy = pos_temp[rand_n][1];
        board[tempx][tempy] = 2;
    }
}