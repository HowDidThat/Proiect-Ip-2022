#include <iostream>
#include <string.h>
#include <fstream>
#include <graphics.h>
#include <conio.h>
#include "desenare_caracter_nou.h"
#include "butoane_caractere_speciale.h"
#include "pentru_calcule.h"
#include "afisare_formula.h"
#include "verificare_corectitudine_formula.h"
using namespace std;

#define inaltime_ecran 1000
#define latime_ecran 1000
#define culoare_linii BLUE
int asteptare_input();

void impartire_ecran()
{
    // deseneaza liniile care impart ecranul in lightcian
    setlinestyle(3,1,3);
    setcolor(RED);
    line (0,inaltime_ecran * 0.75,latime_ecran,inaltime_ecran * 0.75);
    line (0.75*latime_ecran,0,0.75*latime_ecran,0.75*inaltime_ecran);
    line (0.5*latime_ecran,0.75*inaltime_ecran,0.5*latime_ecran,inaltime_ecran);
    line (0,0.1*inaltime_ecran,0.75*latime_ecran,0.1*inaltime_ecran);
    line (0.75*latime_ecran,0.55*inaltime_ecran,latime_ecran,0.55*inaltime_ecran);

 }

void reguli()
{
 int top,left;
 left = 50;
 top = latime_ecran*0.75+20;
 outtextxy(top+80,left,"Reguli :");
 left += textheight("Reguli")+5;
 outtextxy(top,left,"Exponent : # t {exp}");
 left += textheight("Exponent : # t {exp}")+5;
 outtextxy(top,left,"Subscript : # b {sub}");
 left += textheight("Subscript : # b {sub}")+5;
 outtextxy(top,left,"Impartire : # d {term1}{term2}");
 left += textheight("Impartire : # d {term1}{term2}")+5;
 outtextxy(top,left,"Radical : # q {radical}");
 left += textheight("Radical : # q {radical}")+5;
 outtextxy(top,left,"Suma/Produs : ");
 left += textheight ("Suma/Produs : ");
 outtextxy(top,left, "# s / p {T.sus}{T.jos}{exp}");
}

void desenare_butoane()
{
    //deseneaza butoanele din stanga sus pt iesire si desenare
    setfillstyle(SOLID_FILL,RED);
    bar(10,10,90,60);
    outtextxy(20,30,"EXIT");
    bar(100,10,200,60);
    outtextxy(110,30,"Formula");
    bar (210,10,310,60);
    outtextxy (220,30,"Desenare");
    bar (320,10,400,60);
    outtextxy (330,30,"Salvare");
    int q = latime_ecran* 0.75 - 20;
    bar (q - 70,10,q,60);
    outtextxy (q-60,30,"YOLO");
}

void start_pagina_principala()
{
    // int pagina_principala;
    //pagina_principala = initwindow(inaltime_ecran,latime_ecran);

  // initwindow(inaltime_ecran,latime_ecran);
    setbkcolor(WHITE);
    setfillstyle(SOLID_FILL,WHITE);
    settextstyle(3,HORIZ_DIR,1);
    bar(0,0,1000,1000);
    impartire_ecran();
    reguli();
    setcolor(BLUE);
    //setfillstyle(SOLID_FILL,RED);
    //bar (latime_ecran*0.1,inaltime_ecran*0.15,latime_ecran*0.65,inaltime_ecran*0.35);
    setfillstyle(SOLID_FILL,BLUE);
    //bar ()
    desenare_butoane();
    char formula[300];
    ifstream fin("foemula_memorata.txt");
    fin.getline(formula,300);
    fin.close();
    initializare_caractere(latime_ecran,inaltime_ecran);
    int repetare = 1;
    do
        repetare = asteptare_input();
    while (repetare);
    closegraph();
}

void vrea_sa_scrie_dar_nu_poate()
{
    ifstream fin("formula_memorata.txt");
    int x,y,i = 0;
    char formula[100];
    fin.getline(formula,100);
    i = strlen(formula);
    fin.close();
    outtextxy(latime_ecran*0.3,inaltime_ecran*0.2,formula);
    ofstream fout("formula_memorata.txt");
    int ok = 1;
    while (ok)
    {
        clearmouseclick(WM_LBUTTONDOWN);
        formula[i] = getch();
        if (int (formula[i]) == 10)
            ok = 0;
        else if (int (formula[i]) == 8 )
        {
            formula[i-1] = '\0';
            i--;
        }

        else
        {
            formula[i+1] = '\0';
            i++;
        }
        cout << formula[i-1];
        setfillstyle(SOLID_FILL,RED);
        bar (latime_ecran*0.1,inaltime_ecran*0.15,latime_ecran*0.65,inaltime_ecran*0.35);
        outtextxy(latime_ecran*0.3,inaltime_ecran*0.2,formula);
    }
    fout << formula;
    fout.close();

}
void scrie()
{
    ifstream f("formula_memorata.txt");
    char a[100];
    f.getline(a,100);
    int n;
    n = strlen(a);
    setfillstyle(SOLID_FILL,WHITE);
    bar (0,500,730,730);
    if (verificare_formula(a))
        {
        cout << textheight(a);
        afisare_form(a,1000,1000);

        }
    clearmouseclick(WM_LBUTTONDOWN);
    int repetare = 1;
    do
        repetare = asteptare_input();
    while (repetare);
    closegraph();

}

void scrie_YOLO()
{
    ifstream f("formula_memorata.txt");
    char a[100];
    f.getline(a,100);
    int n;
    n = strlen(a);
    setfillstyle(SOLID_FILL,WHITE);
    bar (0,500,730,730);
    if (strstr(a,"#hdh"))
        execute_order_66();
    else
        afisare_form(a,1000,1000);
    clearmouseclick(WM_LBUTTONDOWN);
    int repetare = 1;
    do
        repetare = asteptare_input();
    while (repetare == 1);
    if (!repetare)
        closegraph();

}

int asteptare_input()
{
    int x,y;

    if (ismouseclick(WM_LBUTTONDOWN))
    {
        clearmouseclick(WM_LBUTTONDOWN);
        x = mousex();
        y = mousey();
        if (x > 10 && x < 90 && y > 10 && y < 60)
            return 0;
        else if (x > 210 && x < 310 && y > 10 && y < 60 )
        {
            caracter_nou(inaltime_ecran,latime_ecran);
            start_pagina_principala();
        }

        else if (x > 100 && x < 200 && y > 10 && y < 60)
                scrie();
        else if (x>latime_ecran* 0.75 - 90 && x < latime_ecran* 0.75 - 20 && y > 10 && y < 60)
                {
                 scrie_YOLO();
                }
        else if (x>320 && x < 400 && 10 < y && 60 > y)
            writeimagefile("Formula",0,400,740,740,true,0);
    }
    return 1;

}


int main()
{
    initwindow(inaltime_ecran,latime_ecran);
    start_pagina_principala();
    return 0;
}

