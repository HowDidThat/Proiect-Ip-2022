#include <iostream>
#include <string.h>
#include <fstream>
#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "s.h"
using namespace std;
ofstream fout;
int a[17][17];


int desenare_tabel(int n)
{
    setcolor (5);
    //deseneaza tabelul care va fi umplut pentru caracterul nou astfel incat sa
    //se incadreze 16*16 de casute
    setfillstyle(SOLID_FILL,BLACK);
    bar(0,0,1000,1000);
    int i,q;
    setlinestyle(0,0,3);
    q = n-100;
    q /=16;
    for (i=50; i<=n-50; i=i+q)
    {
        line (50,i,50+16*q,i);
        line (i,50,i,50+16*q);
    }
    setfillstyle(SOLID_FILL,WHITE);
    bar (q*8,10,q*10+25,40);
    settextstyle(1,HORIZ_DIR,3);
    outtextxy(q*8+10,10,"Salvare");
    bar (10,10,40,40);
    setfillstyle(SOLID_FILL,RED);
    line(15,25,35,25);
    line(15,25,25,15);
    line(15,25,25,35);
    line(960,960,990,960);
    line(990,960,990,970);
    line(990,970,960,970);
    line(960,970,960,980);
    setfillstyle(SOLID_FILL,WHITE);
    return q;
}

void empty_a()
{
 for (int i=0;i<=16;i++)
        for (int j = 0;j<=16;j++)
        a[i][j] = 0;
}

void add_caracter_nou()
{
    //deschhide fisierul cu caractere noi si
    //adauga matricea a dupa care o pregateste pentru
    // un alt element
    fout.open("caractere_noi.txt",ios::app);
    fout << 1 <<'\n';
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16 ; j++)
        {
            fout << a[i][j] <<' ';
        }
        fout << '\n';
    }
    fout.close();
    empty_a();

}



int colorare_patrat(int marime_casuta)
{
    // inverseaza culoarea patratului care a fost clickuit pentru desenare
    // alb inseamna 1 si negru inseamna 0 in matrice


    int x,y,linie,coloana;
    if (ismouseclick(WM_LBUTTONDOWN))
    {
        clearmouseclick(WM_LBUTTONDOWN);
        x = mousex();
        y = mousey();
        if (x > 50 && x < marime_casuta*16+50 && y > 50 && y < marime_casuta*16+30)
        {

            linie = (x-50) / marime_casuta ;
            coloana = (y - 50) / marime_casuta ;
            if (a[coloana][linie] == 0)
            {
                setfillstyle(SOLID_FILL,WHITE);
                bar(50+marime_casuta*linie+1,50+marime_casuta*coloana+1,50+marime_casuta*(linie + 1),50+marime_casuta*(coloana+1));
                a[coloana][linie] = 1;
            }
            else
            {
                setfillstyle(SOLID_FILL,BLACK);
                bar(50+marime_casuta*linie+1,50+marime_casuta*coloana+1,50+marime_casuta*(linie + 1),50+marime_casuta*(coloana+1));
                a[coloana][linie] = 0;
            }
        }
        else if (x>50+marime_casuta*8 && x < 50+marime_casuta*12 && y >10 && y < 40)
        {
            add_caracter_nou();
            desenare_tabel(100+marime_casuta*16);
        }
        else if (x>10 && x<40 && y > 10 && y < 40)
            return 0;
        else if (x>950 && x < 1000 && y > 950 && y < 1000)
            {snek();
             desenare_tabel(100+marime_casuta * 16);
            }
        else cout <<"Nu este desenabil acilea !!"<<'\n';

        cout <<x << ' '<<y<<'\n';
    }
    return 1;

}


void caracter_nou(int inaltime_ecran,int latime_ecran)
{
    /*
    desenare caracter nou
    *******************************************
    *************** Caracter nou **************
    *******************************************
    */
    int marime_casuta;
    setfillstyle(SOLID_FILL,0);
     int a = getcolor();
    setcolor (15);
    marime_casuta = desenare_tabel(min(latime_ecran,inaltime_ecran));
    int repetare = 1;
    do
        repetare = colorare_patrat(marime_casuta);
    while (repetare);
    setcolor(a);

}
