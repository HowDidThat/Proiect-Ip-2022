#include <iostream>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <fstream>
#include <time.h>
#include <string.h>
#include <typeinfo>
using namespace std;


struct segment
{
int x,y;
}snake[100],fruct;

int lenght;
int pp = 900/16;

void draw_snake()
{   setfillstyle(SOLID_FILL,BLUE);
    bar(50 + pp*(fruct.x-1)+2,50+pp*(fruct.y-1)+2,50+pp*fruct.x-2,50+pp*fruct.y-2);

    setfillstyle(SOLID_FILL,GREEN);
    for (int i = 0; i<lenght ; i++)
        {
        bar(50+pp*(snake[i].x-1)+2,
            50+pp*(snake[i].y-1)+2,
            50+pp*snake[i].x-2,
            50+pp*snake[i].y-2);
        }

    if (snake[0].x == fruct.x && snake[0].y == fruct.y)
        {
            lenght ++;
        }

}

void draw_matrix()
{  setcolor(RED);
   clearviewport();

    int i;
    for (i = 50; i<=950; i=i+900/16)
        {
            line (i,50,i,950);
            line (50,i,950,i);

        }

    //settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
	//settextjustify(CENTER_TEXT,CENTER_TEXT);
    outtextxy(400,10,"Snek");
    char punctaj[5];
    punctaj[0] = (lenght-5)/100+'0';
    punctaj[1] = (lenght-5)/10%10+'0';
    punctaj[2] = (lenght-5)%10+'0';
    punctaj[3] = '\0';

    outtextxy(100,10,punctaj);
    draw_snake();
}

void sus()
{
    for (int i=lenght-1;i>=1;i--)
        snake[i] = snake[i-1];
    snake[0].y -= 1;
}

void stanga()
{
    for (int i=lenght-1;i>=1;i--)
        snake[i] = snake[i-1];
    snake[0].x -= 1;
}

void jos()
{
    for (int i=lenght-1;i>=1;i--)
        snake[i] = snake[i-1];
    snake[0].y += 1;
}

void dreapta()
{
    for (int i=lenght-1;i>=1;i--)
        snake[i] = snake[i-1];
    snake[0].x += 1;
}

void read_snake()
{
    ifstream f("s.txt");
    f>>lenght;
    for (int i=0;i<lenght;i++)
    {
      f>>snake[i].x;
      f>>snake[i].y;
    }
}

bool verificare_moarte()
{
 for (int i=1;i<lenght;i++)
    if (snake[i].x==snake[0].x && snake[i].y == snake[0].y)
        return false;
 if (snake[0].x < 1 || snake[0].x>16 || snake[0].y<1 || snake[0].y > 16)
    return false;
 return true;
}

void asezare_fruct()
{
  fruct.x = rand() % 16 + 1;
  fruct.y = rand() % 16 +1;
}


int snek()
{   int k = 0;
    srand(time(NULL));
    char c;
    draw_matrix();
    //line(0,0,100,100);
    delay(1000);
    //bar(0,0,100,100);
    read_snake();
    //draw_matrix();
    //getch();
    //char c = KEY_UP;
    bool ok = true;
    asezare_fruct();
    while (ok)
    {
       if (kbhit())
            c = char (getch());
    setactivepage(k);
    setvisualpage(1-k);
    switch(c)
       {

          case KEY_UP :  sus();break;
          case KEY_LEFT : stanga();break;
          case KEY_DOWN :  jos();break;
          case KEY_RIGHT :  dreapta();break;
          case 'x' : ok = false;break;
       }
    k = 1-k;
    ok = verificare_moarte();
    if (!ok)
        {
            setactivepage(k);
            setvisualpage(k);
        }
    draw_matrix();
    if (snake[0].x == fruct.x && snake[0].y == fruct.y)
        asezare_fruct();
    delay(100);
    }
    return 0;
}
