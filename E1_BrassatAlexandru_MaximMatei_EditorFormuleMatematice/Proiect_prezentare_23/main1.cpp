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
#include "alegere_culoare.h"
using namespace std;

#define inaltime_ecran 1000
#define latime_ecran 1000
#define culoare_linii BLUE
int asteptare_input();
int color = 0,window;
char ex[10][300];
int font = 4;
void impartire_ecran()
{
    // deseneaza liniile care impart ecranul in lightcian
    setlinestyle(3,1,3);
    setcolor(0);
    line (0,inaltime_ecran * 0.75,latime_ecran,inaltime_ecran * 0.75);
    line (0.75*latime_ecran,0,0.75*latime_ecran,0.75*inaltime_ecran);
    line (0.5*latime_ecran,0.75*inaltime_ecran,0.5*latime_ecran,inaltime_ecran);
    line (0,0.1*inaltime_ecran,0.75*latime_ecran,0.1*inaltime_ecran);
    line (0.75*latime_ecran,0.55*inaltime_ecran,latime_ecran,0.55*inaltime_ecran);
    line (0.75*latime_ecran,616,latime_ecran,616);
    line (0.75*latime_ecran,682,latime_ecran,682);
    setcolor(color);
 }

void reguli()
{

 int top,left, a = getcolor();

 left = 50;
 setcolor(0);
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
 left += textheight("asdasdasd123123{}");
 outtextxy(top,left, "Car. Spec. : #Numar_simbol");
 outtextxy(850,570,"1");
 outtextxy(850,640,"2");
 outtextxy(850,710,"3");
  setcolor(a);


}

void desenare_butoane()
{
    //deseneaza butoanele din stanga sus pt iesire si desenare
    setcolor(15);
    setfillstyle(SOLID_FILL,RED);
    bar(10,10,90,60);
    outtextxy(20,25,"Demo");
    bar(100,10,200,60);
    outtextxy(110,25,"Formula");
    bar (210,10,310,60);
    outtextxy (220,25,"Desenare");
    bar (320,10,420,60);
    outtextxy (330,25,"Culoare");
    bar (430,10,530,60);
    outtextxy (450,25,"Arbore");
    bar (540,10,650,60);
    outtextxy(550,25,"Salvare");
    int q = latime_ecran* 0.75 - 20;
    bar (q - 70,10,q,60);
    outtextxy (q-60,25,"YOLO");
    setcolor(color);
    setfillstyle(SOLID_FILL,WHITE);
}

void displayText(char inStr[], int x = 30, int y = 120) {
    int lungime = strlen(inStr);
    int sf = -1, k = 0, i;
    setfillstyle(SOLID_FILL,WHITE);
    char tempStr[40]="";
    settextstyle(1,0,3);
    for(i = 0; i<lungime && k<4; i++) {
        tempStr[++sf] = inStr[i];
        tempStr[sf+1] = '\0';
        if(textwidth(tempStr)>650) {
            char tt = tempStr[sf];
            tempStr[sf] = 0;
            outtextxy(x, y+k*30, tempStr);
            k++;
            tempStr[0] = tt;
            tempStr[1] = 0;
            sf = 0;
        }
    }
    if(k<4) outtextxy(x, y+k*30, tempStr);
    else inStr[i-1]=0;
}

char inStr[250];
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
    setcolor(color);
    //setfillstyle(SOLID_FILL,RED);
    //bar (latime_ecran*0.1,inaltime_ecran*0.15,latime_ecran*0.65,inaltime_ecran*0.35);
    setfillstyle(SOLID_FILL,BLUE);
    setbkcolor(RED);
    desenare_butoane();
    setbkcolor(WHITE);
    char formula[300];
    ifstream fin("formula_memorata.txt");
    fin.getline(formula,300);
    fin.close();
    settextstyle(1,0,2);
    displayText(inStr);
    initializare_caractere(latime_ecran,inaltime_ecran);
    int repetare = 1;
    do
        repetare = asteptare_input();
    while (repetare);
    closegraph();
}


void scrie()
{
    ifstream f("formula_memorata.txt");
    char a[100];
    f.getline(a,100);
    f.close();
    setfillstyle(SOLID_FILL,WHITE);
    bar (0, 500, 730, 730);
    if (verificare_formula(a))
        {
        setfillstyle(0,WHITE);
        bar (0, 250, 745, 745);
        afisare_form123(a,1000,1000,color,font);
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
    bar (0,450,730,730);
    if (strstr(a,"#noed"))
        execute_order_66();
    else
        {   setfillstyle(0,WHITE);
            bar(0, 225, 750, 750);
            afisare_form123(a,1000,1000,color,font);
        }
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
        //cout<<x<<" "<<y<<endl;
        if (x > 10 && x < 90 && y > 10 && y < 60)
            {
                int fml;
                fml = formula_demo(x,y,window);
                strcpy(inStr,ex[fml]);
                //setfillstyle(SOLID_FILL,WHITE);
                bar(25, 110, 740, 250);
                displayText(inStr);
                /*int a = getcolor();
                setfillstyle(SOLID_FILL,15);
                bar(0, 125, 750, 750);

                settextstyle(1,0,2);
                int i=0;
                while (textwidth(inStr+i)>700)
                    {
                    i++;
                    }
                setfillstyle(SOLID_FILL,15);
                bar(0,155,740,300);
                outtextxy(30,180,inStr+i);*/
            }
        else if (x > 210 && x < 310 && y > 10 && y < 60 )
        {
            caracter_nou(inaltime_ecran,latime_ecran);
            start_pagina_principala();
        }

        else if (x > 100 && x < 200 && y > 10 && y < 60)
                {
                    ofstream f("formula_memorata.txt");
                    f<<inStr;
                    f.close();
                    scrie();
                }
        else if (x>latime_ecran* 0.75 - 90 && x < latime_ecran* 0.75 - 20 && y > 10 && y < 60)
                {
                    ofstream f("formula_memorata.txt");
                    f<<inStr;
                    f.close();
                    scrie_YOLO();

                }
        else if(x >= 430 && y >= 10 && x <= 530 && y <= 60)
        {
            verificare_formula(inStr,1);
        }
        else if (x>320 && x < 420 && y > 10 && y < 60)
        {
            color = alegere_culoare_text(x,y,color,window);
            start_pagina_principala();
        }
        else if (x>540 && x< 650 && y > 10 && y < 60)
        {
            char  nume[100];
            salvare_formula(x,y,nume,window);
            writeimagefile(nume,0,400,745,745);
        }
        else if (x > 750 && x < 1000)
        {
            if (y>550 && y < 612)
            {
              font = 2;
              start_pagina_principala();
              settextstyle(1,0,2);
                int i=0;
                while (textwidth(inStr+i)>700)
                    {
                    i++;
                    }
                setfillstyle(SOLID_FILL,15);
                bar(0,155,740,300);
                outtextxy(50,180,inStr+i);
            }
            else if (y>612 && y < 682)
            {
               font = 4;
               start_pagina_principala();
                settextstyle(1,0,2);
                int i=0;
                while (textwidth(inStr+i)>700)
                    {
                    i++;
                    }
                setfillstyle(SOLID_FILL,15);
                bar(0,155,740,300);
                outtextxy(30,180,inStr+i);
            }
            else if (y > 682 && y < 750)
            {
                font = 6;
                start_pagina_principala();
                settextstyle(1,0,2);
                int i=0;
                while (textwidth(inStr+i)>700)
                    {
                    i++;
                    }
                setfillstyle(SOLID_FILL,15);
                bar(0,155,740,300);
                outtextxy(30,180,inStr+i);
            }


        }



    }
    if(kbhit()) {
        char ch = getch();
        //cout<<(int)ch<<" ";
        if(ch == 8) //backspace
                {
                    if(strlen(inStr)==0) cout<<"cuvant gol!";
                    else {
                        setfillstyle(0, WHITE);
                        bar(25, 110, 740, 200);
                        inStr[strlen(inStr)-1] = 0;
                    }
                }
        else if (ch == 0) ch = getch(); //arrow keys
        else if (ch == 13) { //enter
            int n = strlen(inStr);
            if (verificare_formula(inStr))
            {
                //cout <<inStr<<'\n';
                setfillstyle(0,WHITE);
                bar(0, 225, 740, 740);
                afisare_form123(inStr,1000,1000,color,font);

            }
        }
        else {
                switch(ch) {
                    case '^': strcat(inStr,"#t");//curPos+=2;
                            break;
                    default : {
                        int s = strlen(inStr);
                        inStr[s] = ch;
                        inStr[s+1] = '\0';
                    }
                }
        }
        settextstyle(1,0,2);
        int i=0;
        while (textwidth(inStr+i)>700)
        {
          i++;
        }
        setfillstyle(SOLID_FILL,WHITE);
        bar(25, 110, 740, 250);
        displayText(inStr);
        //cout<<"str = "<<inStr<<"\n\n";
    }
    return 1;
}

void load_f()
{
    ifstream demo("exemple.txt");
    int i = 1;
    for (i=1;i<=9;i++)
    {
        demo.getline(ex[i],100);
    }
    demo.close();

}

int main()
{
    window = initwindow(inaltime_ecran,latime_ecran,"Pagina Principala");
    setcolor(color);
    load_f();
    start_pagina_principala();
    return 0;
}

