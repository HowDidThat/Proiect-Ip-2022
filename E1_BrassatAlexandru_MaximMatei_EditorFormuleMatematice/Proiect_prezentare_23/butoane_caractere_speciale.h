#include <iostream>
#include <string.h>
#include <fstream>
#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

struct caracter
{
    int a[17][17];
} caractere[50];

int k;

void afisare_caracter(int left, int top,int k,int size1)
{
    setfillstyle(SOLID_FILL,RED);

    for (int i=0;i<16;i++)
     {
         for (int j = 0; j<16;j++)
    {
        if (caractere[k].a[j][i] == 1)
        {
        //putpixel(top+i,left+j,1);
        if (size1 != 2)
            bar (top+size1/2*i,left+size1/2*j,top+(i+1)*size1/2,left+(j+1)*size1/2);
        else
            putpixel(top+i,left+j,2);
       }
      //  cout << a[i][j];
    }
    //cout <<'\n';
     }
    setfillstyle(SOLID_FILL,WHITE);
}

void pt_formula(int nr_ordine,int x,int y,int sz)
{
    if (nr_ordine > k)
        int qweq;
    else
        {
            afisare_caracter(x,y,nr_ordine,sz);
        }


}

void initializare_caractere(int latime_ecran, int inaltime_ecran)
{   k = 0;
    int a = getcolor();
    setcolor(RED);
    setfillstyle(SOLID_FILL,WHITE);
    settextstyle(0,0,2);
    ifstream f("caractere_noi.txt");
    int q;
        while (f>>q)
    {
        for (int i=0; i<16;i++)
            for (int j=0;j<16;j++)
            f >> caractere[k].a[i][j];
        k++;
        if (k == 30)
            break;
    }
    cout <<k <<' ';
    int top_1,left_1;
    int left = latime_ecran *0.05, top = inaltime_ecran*0.8;
    for (int i=0;i<k;i++)
    {
        left_1 = i % 10;
        top_1 = i / 10 ;
        left_1 = left_1 * 40+ left +10;
        top_1 = top_1 * 60 + top +10;
        afisare_caracter(top_1,left_1,i,4);
        char q[3];
        q[0] = i/10+'0';
        q[1] = i%10 + '0';
        q[2] = '\0';
        outtextxy(left_1,top_1+35,q);
    }
    setcolor(a);
    setfillstyle(SOLID_FILL,WHITE);
    //line(100,100,500,500);

}
