#include <iostream>
#include <string.h>
#include <fstream>
#include <conio.h>
#include <graphics.h>
using namespace std;
ifstream f("form.txt");
//#include "verificare_corectitudine_formula.h"
int afisare123(char formula[300],int  &n ,int x,int middle,int dimensiune_font);
int afisare(char formula[300],int  &n ,int x,int middle,int dimensiune_font);
int lungime_formula(char formula[300],int  &n ,int x,int middle,int dimensiune_font);

void reset_font_size(int dim)
{
    settextstyle(1,HORIZ_DIR,dim);

}

void partitionare(char form[300],char nou[200])
{
    char v[300];

    int i,paranteze = 0;
    i = 0;
    strcpy(v,form);


    do
    {
        if (v[i] == '{')
            paranteze ++;
        if (v[i] == '}')
            paranteze --;
        i++;
    }
    while (paranteze);
    strncpy(nou,form,i);
    nou[i] = '\0';

}
void colorare(int x,int y, int c)
{
    setfillstyle(SOLID_FILL,c);
    bar(x*20,y*20,x*20+20,y*20+20);
}

int execute_order_66()
{
    int a[51][51] = {0},x,y,c,i,j;
    srand(time(NULL));
    for (i = 0; i <= 5000; i++)
    {
        x = rand() % 50;
        y = rand() % 50;
        c = rand() % 16;
        if (a[x][y] == 0)
        {
            a[x][y] = 1;
            colorare(x,y,c);
        }
        //delay();
    }
    for (i = 0; i<=50; i++)
        for (j=0; j<=50; j++)
        {
            if (a[i][j] == 0)
            {
                c = rand() % 16;
                colorare(i,j,c);
            }
        }

    delay (2000);
    closegraph();
    _getch();
    return 0;
    //delay(3000);
}


void strip(char a[200])
{
    strcpy(a,a+1);
    a[strlen(a)-1] = '\0';
}


int inaltime_formula(char form[301],int dimensiune_font)
{
    if (dimensiune_font == 0)
        dimensiune_font = 1;
    reset_font_size(dimensiune_font);
    int inaltime, h = textheight(form)-2;
    int i=0,j;
    char p[200],u[200],aux[200];
    inaltime = h;
    //cout <<"form : " << form << '\n';
    if (strstr(form,"#b"))
    {
        char q[300];
        partitionare(strstr(form,"#b")+2,q);
        inaltime += inaltime_formula(q,dimensiune_font/2);
    }
    if (strstr(form,"#t"))
    {
        char q[300];
        partitionare(strstr(form,"#t")+2,q);
        inaltime += inaltime_formula(q,dimensiune_font/2);
    }
    if (strstr(form,"#s"))
        {
         char sus[100],jos[100];
         partitionare(strstr(form,"#s")+2,sus);
         partitionare(strstr(form,"#s")+2+strlen(sus),jos);
         inaltime = max(inaltime,40+inaltime_formula(sus,dimensiune_font/2)+inaltime_formula(jos,dimensiune_font/2));
        }
    if ( strstr(form,"#p"))
        {

         //cout << strstr(form,"#p")<<'\n';
         char sus[100],jos[100],exp[100];
         partitionare(strstr(form,"#p")+2,sus);
         partitionare(strstr(form,"#p")+2+strlen(sus),jos);
         partitionare(strstr(form,"#p")+2+strlen(sus)+strlen(jos),exp);
         inaltime = max(inaltime,60+inaltime_formula(sus,dimensiune_font/2)+inaltime_formula(jos,dimensiune_font/2));
         inaltime = max(inaltime,inaltime_formula(exp,dimensiune_font)*3/2);

        }

    if (strstr(form,"#d"))
    {
        char primul[300],ultimul[300];
        partitionare(strstr(form,"#d")+2,primul);
        partitionare(strstr(form,"#d")+2+strlen(primul),ultimul);
        //cout << '\n'<<inaltime_formula(primul,dimensiune_font)<<'\n';
        //cout << '\n'<<inaltime_formula(ultimul,dimensiune_font)<<'\n';
        return inaltime_formula(primul,dimensiune_font)+inaltime_formula(ultimul,dimensiune_font);
    }
    char t[300];
    strcpy(t,form);
    while (strstr(t,"#"))
           {
            strcpy(t,strstr(t,"#")+1);
            if (strchr("0987654321",t[0]))
                {inaltime = max(inaltime,9*dimensiune_font);
                }
           }
    strcpy(t,form);
    if (strstr(t,"#q"))
    {   char primul[300];
        partitionare(strstr(t,"#q")+2,primul);
        inaltime = max(max(inaltime,h * 3/2),inaltime_formula(primul,dimensiune_font));

    }
    return inaltime;

}


int inaltime_top(char form[300],int dimensiune_font)
{
    reset_font_size(dimensiune_font);
    int inaltime, h = textheight(form);
    int i=0,j;
    char p[200],u[200],aux[200];
    inaltime = h;

    while (strstr(form,"#t"))
    {
      char q[300];
      partitionare(strstr(form,"#t")+2,q);
      strcpy(strstr(form,"#t"),strstr(form,"#t")+strlen(q)+2);
    }

    if (strstr(form,"#b"))
    {
        char q[300];
        partitionare(strstr(form,"#b")+2,q);
        inaltime += inaltime_top(q,dimensiune_font/2);
    }
    if (strstr(form,"#s"))
        {
         char sus[100],jos[100];
         partitionare(strstr(form,"#s")+2,sus);
         partitionare(strstr(form,"#s")+2+strlen(sus),jos);
         inaltime = max(inaltime,20+inaltime_formula(sus,dimensiune_font/2)+inaltime_formula(jos,dimensiune_font/2));
        }
    if ( strstr(form,"#p"))
        {

         char sus[100],jos[100];
         partitionare(strstr(form,"#p")+2,sus);
         partitionare(strstr(form,"#p")+2+strlen(sus),jos);
         inaltime = max(inaltime,40+inaltime_formula(sus,dimensiune_font/2)+inaltime_formula(jos,dimensiune_font/2));
         cout <<'\n'<< "inaltime : "<<inaltime<<"   "<<40+inaltime_formula(sus,dimensiune_font/2)+inaltime_formula(jos,dimensiune_font/2)<<'\n';
        }




    if (strstr(form,"#d"))
    {
        char primul[300],ultimul[300];
        partitionare(strstr(form,"#d")+2,primul);
        partitionare(strstr(form,"#d")+2+strlen(primul),ultimul);
        return inaltime_top(primul,dimensiune_font)+inaltime_top(ultimul,dimensiune_font);
    }
    char t[300];
    strcpy(t,form);
    while (strstr(t,"#"))
           {
            strcpy(t,strstr(t,"#")+1);
            if (strchr("0987654321",t[0]))
                {inaltime = max(inaltime,9*dimensiune_font);
                }
           }
    strcpy(t,form);
    if (strstr(t,"#q"))
    {   char primul[300];
        partitionare(strstr(t,"#q")+2,primul);
        inaltime = max(max(inaltime,h * 3/2),inaltime_top(primul,dimensiune_font));

    }
    return inaltime;
}



int  draw_sum(char formula[300],int &n,int x,int middle, int dimensiune_font)
{
    char primul[300],mijloc[300],ultim[300];
    partitionare(formula+n,primul);
    partitionare(formula+n+strlen(primul),mijloc);
    partitionare(formula+n+strlen(primul)+strlen(mijloc),ultim);
    //

    line(x+10,middle,x,middle-10);
    line(x,middle-10,x+15,middle-10);
    line(x+10,middle,x,middle+10);
    line(x,middle+10,x+15,middle+10);
    n+= strlen(primul)+strlen(mijloc)+strlen(ultim);
    reset_font_size(dimensiune_font/2);
    int x1,x2,x3,n1 = 0;
    x1 = afisare(primul,n1,x,middle-5-inaltime_formula(primul,dimensiune_font/2),dimensiune_font/2);
    n1 = 0;
    x2 = afisare(mijloc,n1,x,middle+inaltime_formula(mijloc,dimensiune_font/2)+5,dimensiune_font/2);
    n1 = 0;
    x3 = afisare(ultim,n1,max(x+20,max(x1,x2)),middle,dimensiune_font);

    return x3;
}

int  draw_produce(char formula[300],int &n,int x,int middle, int dimensiune_font)
{
    char primul[300],mijloc[300],ultim[300];
    partitionare(formula+n,primul);
    partitionare(formula+n+strlen(primul),mijloc);
    partitionare(formula+n+strlen(primul)+strlen(mijloc),ultim);
    //
    cout <<primul<<'\n'<<mijloc<<'\n'<<ultim;


    line(x,middle-10,x+20,middle-10);
    line(x+5,middle-10,x+5,middle+10);
    line(x+15,middle-10,x+15,middle+10);

   // line(x+10,middle,x,middle-10);
   // line(x,middle-10,x+15,middle-10);
   // line(x+10,middle,x,middle+10);
   // line(x,middle+10,x+15,middle+10);
    n+= strlen(primul)+strlen(mijloc)+strlen(ultim);
    reset_font_size(dimensiune_font/2);
    int x1,x2,x3,n1 = 0;
    x1 = afisare(primul,n1,x,middle-inaltime_formula(primul,dimensiune_font/2)-10,dimensiune_font/2);
    n1 = 0;
    x2 = afisare(mijloc,n1,x,middle+inaltime_formula(mijloc,dimensiune_font/2)+5,dimensiune_font/2);
    n1 = 0;
    x3 = afisare(ultim,n1,max(x+25,max(x1,x2)),middle,dimensiune_font);

    return x3;
}


int division(char formula[300],int &n,int x,int middle, int dimensiune_font)
{
    char prima[300],ultima[300],test1[300],test2[300];
    int h1,h2,x1,x2;
    x +=5;
    partitionare(formula+n,prima);
    partitionare(formula+n+strlen(prima),ultima);
    strcpy(test1,prima);
    strcpy(test2,ultima);
    int xp,xu,mijloc;
    int n1 = 0;
    xp = lungime_formula(prima,n1,500,middle,dimensiune_font) - 500 ;
    n1 = 0;
    xu = lungime_formula(ultima,n1,500,middle,dimensiune_font) - 500 ;
    mijloc = max(xp,xu) / 2;
    /////////////////
    // cout << "prima : "<<prima<<'\n';
    //cout << "ultima : "<<ultima <<'\n';
    //strip(prima);
    //strip(ultima);
    if (strstr(prima,"#d") == NULL)
    {
      int n1 = 0,bot = 0;
      char *q;
      q = strstr(prima,"#b");
      while (q)
      {
        if (bot == 0)
            {
                reset_font_size(max(dimensiune_font/2,1));
                bot += textheight(prima)+10;
                reset_font_size(dimensiune_font);
            }

        else if (bot == 1)
              {
                reset_font_size(max(dimensiune_font/2,1));
                bot += textheight(prima)+2;
                reset_font_size(dimensiune_font);
            }
        else
              {
                reset_font_size(max(dimensiune_font/4,1));
                bot += textheight(prima)+2;
                reset_font_size(dimensiune_font);
            }
        q = strstr(q+2,"#b");
      }

      x1 = afisare123(prima,n1,x + mijloc - xp/2,middle- max(inaltime_formula(prima,dimensiune_font)/2,bot+2),dimensiune_font);

    }
    else
    {
      int n1 = 0,n2 = 0;
      char inalt[300];
      strip(prima);
      n += 2;
      partitionare(strstr(prima,"#d")+2,inalt);
      partitionare(strstr(prima,"#d")+2+strlen(inalt),inalt);
      x1 = afisare123(prima,n1,x + mijloc - xp/2,middle-10-inaltime_formula(inalt,dimensiune_font),dimensiune_font);

    }

    if (strstr(ultima,"#d") == NULL)
    {
       int n1 = 0,bot = 0;
      char *q;
      q = strstr(ultima,"#t");
      while (q)
      {
        bot += textheight(ultima)/3+2;
        q = strstr(q+2,"#t");
      }
       //cout <<"OK";
       int h;
        h = max(inaltime_formula(ultima,dimensiune_font)/2-5,bot);
        x2 = afisare123(ultima,n1,x + mijloc - xu/2,middle+10+h,dimensiune_font);

    }
    else
    {
      int n2 = 0;
      char inalt[300];
      strip(ultima);
      n += 2;
      partitionare(strstr(ultima,"#d")+2,inalt);

      x2 = afisare123(ultima,n2,x + mijloc - xu/2,middle+5+inaltime_formula(inalt,dimensiune_font),dimensiune_font);
      //partitionare(strstr(ultima,"#d")+2+strlen(inalt),inalt);

    }
    ////////////////
    line(x,middle,max(x1,x2),middle);
    n += strlen(prima) + strlen(ultima);
    return max(x1,x2);
}

int square(char formula[300],int &n,int x,int middle, int dimensiune_font)
{
    char text[300];
    partitionare(formula+n,text);
    if (strstr(text,"#d") == 0)
    {   int n1 = 0, h = inaltime_formula(text,dimensiune_font)+10;
        x+=5;
        line(x,middle,x+3,middle + h/3);
        line(x+3,middle+h/3,x+10,middle-h/3-3);
        n += strlen(text);
        int x1;
        x1 = afisare(text,n1,x+15,middle,dimensiune_font);
        line(x+10,middle-h/3-3,x1,middle-h/3-3);
        return x1;}
    else
        {
         char primul[300],ultimul[300];
         partitionare(strstr(text,"#d")+2,primul);
         partitionare(strstr(text,"#d")+2+strlen(primul),ultimul);
         int x1,n1 =0;
         x1 = afisare(text,n1,x+15,middle,dimensiune_font);
         n+=strlen(text);
         line(x,middle,x+5,middle+inaltime_formula(ultimul,dimensiune_font));
         line(x+5,middle+inaltime_formula(ultimul,dimensiune_font),x+10,middle-inaltime_formula(primul,dimensiune_font)-10);
         line(x+10,middle-inaltime_formula(primul,dimensiune_font)-10,x1,middle-inaltime_formula(primul,dimensiune_font)-10);

         return x1;
        }


}

int division1(char formula[300],int &n,int x,int middle, int dimensiune_font)
{
    char prima[300],ultima[300],test1[300],test2[300];
    int h1,h2,x1,x2;
    x += 5;
    partitionare(formula+n,prima);
    partitionare(formula+n+strlen(prima),ultima);
    strcpy(test1,prima);
    strcpy(test2,ultima);
    int xp,xu,mijloc;
    int n1 = 0;
    xp = lungime_formula(prima,n1,0,middle,dimensiune_font) - 500 ;
    n1 = 0;
    xu = lungime_formula(ultima,n1,0,middle,dimensiune_font) - 500 ;
    mijloc = max(xp,xu) / 2;
    /////////////////
    if (strstr(prima,"#d") == NULL)
    {
      int n1 = 0,bot = 0;
      if (strstr(prima,"#b"))
      {
          if (strstr(strstr(prima,"#b") + 2,"#b"))
            bot = textheight(prima);
          else bot = textheight(prima)/2;
      }
      x1 = lungime_formula(prima,n1,x + mijloc - xp/2,middle - inaltime_formula(prima,dimensiune_font)/2,dimensiune_font);

    }
    else
    {
      int n1 = 0,n2 = 0;
      char inalt[300];
      strip(prima);
      n += 2;
      partitionare(strstr(prima,"#d")+2,inalt);
      partitionare(strstr(prima,"#d")+2+strlen(inalt),inalt);
      x1 = lungime_formula(prima,n1,x + mijloc - xp/2,middle-inaltime_formula(inalt,dimensiune_font),dimensiune_font);
    }

    if (strstr(ultima,"#d") == NULL)
    {
        int n2 = 0,top = 0;
       if (strstr(ultima,"#t"))
      {
          if (strstr(strstr(ultima,"#t") + 2,"#t"))
            top = textheight(ultima);
          else top = textheight(ultima)/2;
      }
        x2 = lungime_formula(ultima,n2,x + mijloc - xu/2,middle+inaltime_formula(ultima,dimensiune_font)/2,dimensiune_font);

    }
    else
    {
      int n2 = 0;
      char inalt[300];
      strip(ultima);
      n += 2;
      partitionare(strstr(ultima,"#d")+2,inalt);


      x2 = lungime_formula(ultima,n2,x + mijloc - xu/2,middle+inaltime_formula(inalt,dimensiune_font),dimensiune_font);

    }


    n += strlen(prima) + strlen(ultima);
    return max(x1,x2);
}


int square1(char formula[300],int &n,int x,int middle, int dimensiune_font)
{
    char text[300];
    partitionare(formula+n,text);
    int n1 = 0, h = inaltime_formula(text,dimensiune_font)+10;
    n += strlen(text);
    int x1;
    x1 = lungime_formula(text,n1,x+15,middle,dimensiune_font);
    return x1;
}


int  draw_sum1(char formula[300],int &n,int x,int middle, int dimensiune_font)
{
    char primul[300],mijloc[300],ultim[300];
    partitionare(formula+n,primul);
    partitionare(formula+n+strlen(primul),mijloc);
    partitionare(formula+n+strlen(primul)+strlen(mijloc),ultim);
    //

    n+= strlen(primul)+strlen(mijloc)+strlen(ultim);
    reset_font_size(dimensiune_font/2);
    int x1,x2,x3,n1 = 0;
    x1 = lungime_formula(primul,n1,x,middle-inaltime_formula(primul,dimensiune_font/2),dimensiune_font/2);
    n1 = 0;
    x2 = lungime_formula(mijloc,n1,x,middle+inaltime_formula(mijloc,dimensiune_font/2)+5,dimensiune_font/2);
    n1 = 0;
    x3 = lungime_formula(ultim,n1,max(x+20,max(x1,x2)),middle,dimensiune_font);

    return x3;
}

int  draw_produce1(char formula[300],int &n,int x,int middle, int dimensiune_font)
{
    char primul[300],mijloc[300],ultim[300];
    partitionare(formula+n,primul);
    partitionare(formula+n+strlen(primul),mijloc);
    partitionare(formula+n+strlen(primul)+strlen(mijloc),ultim);
    //




    n+= strlen(primul)+strlen(mijloc)+strlen(ultim);
    reset_font_size(dimensiune_font/2);
    int x1,x2,x3,n1 = 0;
    x1 = lungime_formula(primul,n1,x,middle-inaltime_formula(primul,dimensiune_font/2),dimensiune_font/2);
    n1 = 0;
    x2 = lungime_formula(mijloc,n1,x,middle+inaltime_formula(mijloc,dimensiune_font/2)+5,dimensiune_font/2);
    n1 = 0;
    x3 = lungime_formula(ultim,n1,max(x+25,max(x1,x2)),middle,dimensiune_font);

    return x3;
}



int lungime_formula(char formula[300],int  &n ,int x,int middle,int dimensiune_font)
{
    char q[2];
    int ok = 1;
    if (dimensiune_font == 0)
        dimensiune_font = 1;
    int x1,x2;
    while (n < strlen(formula) && ok == 1)
    {
        reset_font_size(dimensiune_font);

        if (formula[n] != '#' && formula[n]!= '{' && formula[n]!='}')
        {
            q[0] = formula[n];
            q[1] = '\0';
                {
                 x += textwidth(q);
                 n++;
                }
        }
        else if (formula[n] == '#')
        {
            switch(formula[n+1])
            {
            case 't' :
                n +=2;
                x1 = lungime_formula(formula,n,x,middle-textheight(formula)/2,dimensiune_font / 2);
                if (formula[n] == '#' && formula[n+1]=='b')
                    {
                    n += 2;
                    reset_font_size(dimensiune_font);
                    x2 = lungime_formula(formula,n,x,middle+textheight(formula)/2,dimensiune_font / 2);
                    x = max(x1,x2);
                    }
                else x = x1;
                break;
            case 'b' :
                n +=2;
                x1 = lungime_formula(formula,n,x,middle+textheight(formula)/2,dimensiune_font / 2);
                if (formula[n] == '#' && formula[n+1]=='t')
                    {
                    n += 2;
                    reset_font_size(dimensiune_font);
                    x2 = lungime_formula(formula,n,x,middle+textheight(formula)/2,dimensiune_font / 2);
                    x = max(x1,x2);
                    }
                else x = x1;
                break;
            case 'd':
               n += 2;
               x = division1(formula,n,x,middle,dimensiune_font);
               break;
            case 's':
                n += 2 ;
                x = draw_sum1(formula,n,x,middle,dimensiune_font);
                break;
           case 'p':
                n += 2;
                x = draw_produce1(formula,n,x,middle,dimensiune_font);
                break;
           case 'q':
                n += 2;
                x = square1(formula,n,x,middle,dimensiune_font);
                break;
            default:
            {
                int a_1,a_2;
                n++;
                a_1 = formula[n]-'0';
                n++;
                a_2 = formula[n]-'0';
                n++;
                //pt_formula(a_1*10+a_2,middle-4*(dimensiune_font),x,dimensiune_font);
                //cout <<x<<' ';
                x +=3 + 16*(float(dimensiune_font/2));

            }
            }
        }
        else if (formula[n] == '}')
        {
            ok = 0;
            n ++;
        }
        else n++;
    }

    return x;

}




int afisare(char formula[300],int  &n ,int x,int middle,int dimensiune_font)
{
    char q[2];
    int ok = 1;
    int x1,x2;
    while (n < strlen(formula) && ok == 1)
    {
        reset_font_size(dimensiune_font);

        if (formula[n] != '#' && formula[n]!= '{' && formula[n]!='}')
        {
            q[0] = formula[n];
            q[1] = '\0';
            if (x+textwidth(q) < 700)
                {

                 outtextxy(x,middle-textheight(q)/2,q);
                 x += textwidth(q);
                 n++;
                }
            //outtextxy(500,500,"123123123123");
        }
        else if (formula[n] == '#')
        {
            switch(formula[n+1])
            {
            case 't' :
                n +=2;
                x1 = afisare(formula,n,x,middle-textheight(formula)/2,dimensiune_font / 2);
                if (formula[n] == '#' && formula[n+1]=='b')
                    {
                    n += 2;
                    reset_font_size(dimensiune_font);
                    x2 = afisare(formula,n,x,middle+textheight(formula)/2,dimensiune_font / 2);
                    x = max(x1,x2);
                    }
                else x = x1;
                break;
            case 'b' :
                n +=2;
                x1 = afisare(formula,n,x,middle+textheight(formula)/2,dimensiune_font / 2);
                if (formula[n] == '#' && formula[n+1]=='t')
                    {
                    n += 2;
                    reset_font_size(dimensiune_font);
                    x2 = afisare(formula,n,x,middle+textheight(formula)/2,dimensiune_font / 2);
                    x = max(x1,x2);
                    }
                else x = x1;
                break;
            case 'd':
               n += 2;
               x = division(formula,n,x,middle,dimensiune_font);
               break;
            case 's':
                n += 2 ;
                x = draw_sum(formula,n,x,middle,dimensiune_font);
                break;
           case 'p':
                n += 2;
                x = draw_produce(formula,n,x,middle,dimensiune_font);
                break;
           case 'q':
                n += 2;
                x = square(formula,n,x,middle,dimensiune_font);
                break;
            default:
            {
                int a_1,a_2;
                n++;
                a_1 = formula[n]-'0';
                n++;
                a_2 = formula[n]-'0';
                n++;
                pt_formula(a_1*10+a_2,middle-4*(dimensiune_font),x,dimensiune_font);
                //cout <<x<<' ';
                x +=3 + 16*(float(dimensiune_font/2));

            }
            }
        }
        else if (formula[n] == '}')
        {
            ok = 0;
            n ++;
        }
        else n++;
    }

    return x;

}

int afisare123(char formula[300],int  &n ,int x,int middle,int dimensiune_font)
{
    char q[2];
    int ok = 1;
    int x1,x2;
    if (dimensiune_font == 0)
        dimensiune_font = 1;
    while (n < strlen(formula) && ok == 1)
    {
        reset_font_size(dimensiune_font);

        if (formula[n] != '#' && formula[n]!= '{' && formula[n]!='}')
        {
            q[0] = formula[n];
            q[1] = '\0';
            if (x+textwidth(q) < 700)
                {
                 outtextxy(x,middle-textheight(q)/2,q);
                 x += textwidth(q);
                 n++;
                }
            else n++;
        }
        else if (formula[n] == '#')
        {
            switch(formula[n+1])
            {
            case 't' :
                n +=2;
                char q[300];
                int x99;
                partitionare(formula+n,q);
                x99 = inaltime_top(q,dimensiune_font);
                x1 = afisare123(formula,n,x,middle-x99/2,int (dimensiune_font / 2));
                if (formula[n] == '#' && formula[n+1]=='b')
                    {
                    n += 2;
                    reset_font_size(dimensiune_font);
                    char q[300];
                    int x99;
                    partitionare(formula+n-1,q);
                    x99 = inaltime_formula(q,dimensiune_font/2);

                    x2 = afisare123(formula,n,x,middle+x99,int(dimensiune_font / 2));
                    x = max(x1,x2);
                    }
                else x = x1;
                break;
            case 'b' :
                n +=2;
                char z[300];
                int x98;
                partitionare(formula+n-1,z);
                x98 = inaltime_formula(z,dimensiune_font/2);
                x1 = afisare123(formula,n,x,middle+x98,int(dimensiune_font / 2));
                if (formula[n] == '#' && formula[n+1]=='t')
                    {
                    n += 2;
                    reset_font_size(dimensiune_font);
                    char z[300];
                    int x98;
                    partitionare(formula+n-1,z);
                    x98 = inaltime_formula(z,int (dimensiune_font/2));
                    x2 = afisare123(formula,n,x,middle-x98, int (dimensiune_font / 2));
                    x = max(x1,x2);
                    }
                else x = x1;
                break;
            case 'd':
               n += 2;
               x = division(formula,n,x,middle,dimensiune_font);
               break;
            case 's':
                n += 2 ;
                x = draw_sum(formula,n,x,middle,dimensiune_font);
                break;
           case 'p':
                n += 2;
                x = draw_produce(formula,n,x,middle,dimensiune_font);
                break;
           case 'q':
                n += 2;
                x = square(formula,n,x,middle,dimensiune_font);
                break;
            default:
            {
                int a_1,a_2;
                n++;
                a_1 = formula[n]-'0';
                n++;
                a_2 = formula[n]-'0';
                n++;
                pt_formula(a_1*10+a_2,middle-4*(dimensiune_font),x,dimensiune_font);
                //cout <<x<<' ';
                x +=3 + 16*(float(dimensiune_font/2));

            }
            }
        }
        else if (formula[n] == '}')
        {
            ok = 0;
            n ++;
        }
        else n++;
    }

    return x;

}

void afisare_form123(char a[301],int inaltime_ecran, int latime_ecran,int color,int dimensiune_font)
{
    setlinestyle(0,0,3);
    int n = 0;
    setcolor(color);
    afisare123(a,n,50,600,dimensiune_font);
}


void afisare_form(char a[301],int inaltime_ecran, int latime_ecran,int color,int dimensiune_font)
{
    setlinestyle(0,0,3);
    int n = 0;
    setcolor(color);
    afisare(a,n,50,600,dimensiune_font);
}
