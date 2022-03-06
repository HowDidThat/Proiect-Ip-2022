#include <iostream>
#include <string.h>
#include <fstream>
#include <conio.h>
#include <graphics.h>


void lines()
{
    int i,j;
    setfillstyle(SOLID_FILL,9);
    bar(0,0,400,400);
    for (i = 50;i<=350;i+=75)
    {
        line (i,50,i,350);
        line (50,i,350,i);
    }
    for (i=0;i<=3;i++)
        for (j=0;j<=3;j++)
    {
        setfillstyle(SOLID_FILL,i*4+j);
        bar(50+75*(j),50+75*(i),50+75*(j+1),50+75*(i+1));
    }
    int a = getcolor();
    setcolor(5);
    setlinestyle(0,0,10);
    line(50,50,50,350);
    line(50,50,350,50);
    line(50,350,350,350);
    line(350,50,350,350);
   setcolor(a);
}

int alegere_culoare_text(int x,int y,int color,int window)
{
    int des = initwindow(400,400,"",x,y,false,true);
    setfillstyle(SOLID_FILL,WHITE);
    lines();
    while (true)
    if (ismouseclick(WM_LBUTTONDOWN))
    {
        clearmouseclick(WM_LBUTTONDOWN);
        x = mousex();
        y = mousey();
         if (x > 50 && x < 350 && y > 50 && y < 350)
        {
            closegraph(des);
            setcurrentwindow(window);
            return (x-50)/75 + (y-50)/75 * 4;
        }
         else
              {
                closegraph(des);
                setcurrentwindow(window);
                return color;
            }
    }


    return 0;
}

char inSrt[100];
int salvare_formula(int x,int y, char inStr[100],int window)
{  int des = initwindow(300,200,"",200,200,false,true);
  inStr[0] = '\0';
  settextstyle(1,0,2);
  setfillstyle(SOLID_FILL,BLACK);
  bar (0,0,500,500);
  if (textwidth(inStr)<700)
     outtextxy(30,100,inStr);
  while (true){
  if(kbhit()) {
        char ch = getch();
        if(ch == 8) //backspace
                {
                    if(strlen(inStr)==0) cout<<"cuvant gol!";
                    else {
                        setfillstyle(0, WHITE);
                        bar(25, 175, 740, 250);
                        inStr[strlen(inStr)-1] = 0;
                    }
                }
        else if (ch == 0) ch = getch(); //arrow keys
        else if (ch == 13) { //enter
            int n = strlen(inStr);
            if (verificare_formula(inStr))
            {
                closegraph(des);
                setcurrentwindow(window);
                return 0;

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
        setfillstyle(SOLID_FILL,BLACK);
        bar (0,0,500,500);
        if (textwidth(inStr)<700)
            outtextxy(30,100,inStr);
    }
    }

}


void lines2()
{
    int i,j;
    setfillstyle(SOLID_FILL,0);
    bar(0,0,400,400);
    for (i = 50;i<=350;i+=100)
    {
        line (i,50,i,350);
        line (50,i,350,i);
    }

    for (i=0;i<3;i++)
        for (j=0;j<3;j++)
    {
        char q[2];
        q[0] = (i*3+j+1)+'0';
        q[1] = '\0';
        outtextxy(100+j*100,100+i*100,q);

    }
}


int formula_demo(int x,int y,int window)
{
    int des = initwindow(400,400,"",x,y,false,true);
    setfillstyle(SOLID_FILL,WHITE);
    lines2();
    while (true)
    if (ismouseclick(WM_LBUTTONDOWN))
    {
        clearmouseclick(WM_LBUTTONDOWN);
        x = mousex();
        y = mousey();
         if (x > 50 && x < 350 && y > 50 && y < 350)
        {
            closegraph(des);
            setcurrentwindow(window);
            return (x-50)/100 + (y-50)/100 * 3 + 1;
        }
         else
              {
                closegraph(des);
                setcurrentwindow(window);
                return 0;
            }
    }


    return 0;
}



