#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

char snow[29][120];

void padenie(int i, int j)
{
    if (snow[i + 1][j] == ' ' && snow[i][j] != ' ' && snow[i + 1][j + 1] == '|' && (snow[i][j] == '.' || snow[i][j] == '*'))
    {
        snow[i + 1][j] = snow[i][j];
        snow[i][j] = ' ';
    }

    if ((snow[i][j] == '.' || snow[i][j] == '*') && snow[i + 1][j - 1] == ' ')
    {
        snow[i + 1][j - 1] = snow[i][j];
        snow[i][j] = ' ';
    }
}
void nakap(int ii, int jj)
{
    //падение снега
    int W = 1;
    for (int i = ii - 2; i >= 0; i--)
    {
        for (int j = 0; j < jj; j++)
        {   //падение учитывая ветер
            if ((snow[i][j] == '.' || snow[i][j] == '*') && (snow[i + 1][j + W] == ' '))
            {
                snow[i + 1][j + W] = snow[i][j];
                snow[i][j] = ' ';
            }
            //прессование снега
            if (snow[i + 1][j] == '.' && snow[i][j] != ' ')
            {
                snow[i + 1][j] = '*';
                snow[i][j] = ' ';
            }
            padenie(i, j);
        }
    }
}

void house(int ii, int jj)
{
    //пол
    for (int i = 0; i < jj; i++)
    {
        snow[28][i] = '-';
    }
    //стены
    for (int i = 17; i < ii - 1; i++)
    {
        snow[i][30] = '|';
        snow[i][80] = '|';
    }
    //потолки
    for (int i = 0; i < 53; i++)
    {
        snow[16][29 + i] = '-';
    }
    //окно
    for (int i = 20; i < 26; i++)
    {
        snow[i][40] = '|';
        snow[i][45] = '|';
        snow[i][50] = '|';
    }
    for (int i = 0; i < 11; i++)
    {
        snow[20][40 + i] = '-';
        snow[23][41 + i - 1] = '-';
        snow[26][40 + i] = '-';
    }
}
void circlessnow(int ii, int jj)
{
    int key = 0;
    while (key < 30)
    {
        //Заполнение первой строки

        char sym[] = { '*','.',' ' };

        for (int j = 0;j < jj;j++)
        {
            if (rand() % 15 == 1)
            {
                snow[0][j] = sym[rand() % 2];
            }
            else
            {
                snow[0][j] = sym[2];
            }
        }

        nakap(ii, jj);
        //скидывание снега если рядом есть пустое место
        for (int i = ii - 2; i >= 0; i--)
        {
            for (int j = 0; j < 118; j++)
            {
                if (snow[i + 1][j] == '*' && snow[i + 1][j + 1] == ' ' && snow[i][j] == '*')
                {
                    snow[i + 1][j + 1] = snow[i][j];
                    snow[i][j] = ' ';
                }
                if (snow[i + 1][j] == '*' && snow[i + 1][j - 1] == ' ' && snow[i][j] == '*')
                {
                    snow[i + 1][j - 1] = snow[i][j];
                    snow[i][j] = ' ';
                }
            }
        }
        //вывод
        system("cls");
        printf(snow);
        Sleep(200);
        key++;
    }
    key = 0;
}
void taet(int ii, int jj)
{
     for (int j = jj; j >= 0; j--)
     {
        
        if (snow[27][j] == '*' )
            snow[27][j] = ' '; //очистка экрана
        if (snow[15][j] == '*')
            snow[15][j] = ' '; //очистка экрана
     }
     
}
void main()
{
    int ii = 29;int jj = 120;
    //пустая консоль
    for (int i = 0; i < ii; i++)
    {
        for (int j = 0; j < jj; j++)
        {
            snow[i][j] = ' ';
        }
    }
    
    house(ii, jj);
    while (1)
    {
        circlessnow(ii, jj); //этап падение снега
        
        taet(ii, jj);
    }
}