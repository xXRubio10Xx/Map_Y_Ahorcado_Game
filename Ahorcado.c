#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void map_print();
void map_update();
void hang_print();
void hang_update();

int lives = 6;
char list [15][20] = {"billar", "pizarra", "fuego", "anaconda", "sardina", "puerta", "gafas", "enchufe", "sillon", "patinete", "camiseta", "balcon", "telefono", "perro", "sudadera"};
char *word;
int guess [20];
char letters [27];
int win = 0;
char hangman [7][9] =   {' ',' ',' ','+','-','-','-','+',' ',
                         ' ',' ',' ','|',' ',' ',' ','|',' ',
                         ' ',' ',' ','O',' ',' ',' ','|',' ',
                         ' ',' ','/','|','\\',' ',' ','|',' ',
                         ' ',' ','/',' ','\\',' ',' ','|',' ',
                         ' ',' ',' ',' ',' ',' ',' ','|',' ',
                         '=','=','=','=','=','=','=','=','='};

int board [10][10];
int posx;
int posy;
int main()
{
    srand(time(NULL));
    do {
    posx = rand() % 10;
    posy = rand() % 10;
    }while (posx == 4 && posy == 4);

    //MAP
    while (posx != 4 || posy != 4)
    {
        map_print();
        map_update();
    }

    //HANGMAN
    system("cls");
    memset(letters, ' ', sizeof(letters));
    word = list[rand() % 15]; //Puntero
    hang_print();
    while (lives > 0 && win < strlen(word)){
        hang_update();
        hang_print();
    }
    system("cls");
    if (win == strlen(word)) {
        printf("Has ganado\n\nla palabra era: %s\n", word);
    } else {
        printf("Has perdido\n\nla palabra era: %s\n", word);
    }
    system("pause");
    return 0;
}

void map_print(){
    system("cls");
    for (int i = 0; i < 10; i++)
    {
        printf ("\n");
        for (int l = 0; l < 10; l++)
        {
            if (i == 4 && l == 4){
                board[i][l] = 2;
                printf ("R");
            }
            else if (i == posy && l == posx){
                board[i][l] = 1;
                printf ("X");
            }
            else{
                board[i][l] = 0;
                printf ("-");
            }
        }     
    }
    printf ("\n");
}

void map_update(){
    char select;
    printf ("\n");
    printf ("W = Arriba\n");
    printf ("A = Izquierda\n");
    printf ("S = Abajo\n");
    printf ("D = Derecha\n");
    scanf_s (" %c", &select);
    int newPosX = posx, newPosY = posy;
    switch (select) {
        case 'w': case 'W': newPosY -= 1; break;
        case 'a': case 'A': newPosX -= 1; break;
        case 's': case 'S': newPosY += 1; break;
        case 'd': case 'D': newPosX += 1; break;
        default: break;
    }

    if (newPosX >= 0 && newPosX < 10 && newPosY >= 0 && newPosY < 10) {
        posx = newPosX;
        posy = newPosY;
    }
}

void hang_print(){
    system("cls");
    for (int i = 0; i < 7; i++)
    {
        printf ("\n");
        for (int l = 0; l < 9; l++)
        {
            if ((i == 2 && l == 3 && lives >= 6) ||   // Cabeza
                (i == 3 && l == 3 && lives >= 5) ||   // Cuerpo
                (i == 3 && l == 2 && lives >= 4) ||   // Brazo iz
                (i == 3 && l == 4 && lives >= 3) ||   // Brazo de
                (i == 4 && l == 2 && lives >= 2) ||   // Pierna iz
                (i == 4 && l == 4 && lives >= 1)) {   // Pierna de
                printf(" ");
            } else {
                printf("%c", hangman[i][l]);
            }
        }
    }
    printf ("\n");
}

void hang_update(){
    char try;
    int correct = 0;
    
    for (int i = 0; i < strlen(word); i++)
    {
        if (guess[i] == 1)
            printf ("%c", word[i]);
        else
            printf ("_");
    }
    printf("\n\nLetras usadas: ");
    for (int i = 0; i < 27; i++) {
        if (letters[i] != ' ') {
            printf("%c ", letters[i]);
        }
    }
    printf("\n\nIntroduce una letra: ");
    scanf(" %c", &try);
    for (int i = 0; i < strlen(word); i++) {
        if (strncmp(&try, &word[i], 1) == 0 && guess[i] == 0) {
            guess[i] = 1;
            correct = 1;
            win += 1;
        }
    }
    for (int i = 0; i < 27; i++) {
        if (letters[i] == try) {
            return;
        }
    }
    for (int i = 0; i < 27; i++) {
        if (letters[i] == ' ') {
            letters[i] = try;
            break;
        }
    }
    if (!correct)
        lives -= 1;
}
