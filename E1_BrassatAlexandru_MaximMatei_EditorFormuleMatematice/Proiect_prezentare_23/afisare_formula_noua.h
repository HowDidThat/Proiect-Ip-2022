#include <iostream>
#include <string.h>
#include <fstream>
#include <graphics.h>
#include <conio.h>\
#include <time.h>
/*
    ^  - exponent
    ~  - subtext
    \{}/{}   - division
*/
int afisare(char formula[100], int &n, int x, int y, int dimensiune_font);
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

void strip(char a[200])
{
    strcpy(a,a+1);
    a[strlen(a)-1] = '\0';
}


int formula_height(char form[301],int dimensiune_font)
{
    reset_font_size(dimensiune_font);
    int inaltime = textheight(form);
    int i=0,j,h,h_1,h_2;
    char p[200],u[200];
    for (i=0; i<=strlen(form); i++)
    {
        if (form[i] == '#')
        {
            int q = form[i+1];
            switch (q)
            {
            case 't':
                partitionare(form+3,p);
                cout <<'t'<<'\t'<<p<<'\n';
                i+=strlen(p)+2;
                strip(p);
                h = formula_height(p,dimensiune_font/2);
                inaltime += h;
                break;
            case 'b':
                partitionare(form+2,p);
                cout <<'b'<<'\n';
                i+=strlen(p)+2;
                strip(p);
                h = formula_height(p,dimensiune_font/2);
                inaltime += h;
                break;
            case 'd':
                partitionare(form+2,p);
                partitionare(form+strlen(p)+2 ,u);
                i+= strlen(p)+strlen(u)+4;
                strip(p);
                strip(u);
                cout <<p<<'\t'<<u<<'\n';
                h_1 = formula_height(p,dimensiune_font);
                h_2 = formula_height(u,dimensiune_font);
                inaltime += h_1 + h_2 -inaltime;
                break;
            case 's':
                inaltime += 40;
            case 'p':
                inaltime += 40;
            }
        }
    }
    return inaltime;

}

int division(char formula[100],int &n,int x,int y,int dimensiune_font)
{
    char v[100],p[100];
    strcpy(v,formula+n);
    int i = 0,paranteze = 0,ok = 0;
    int n1 = 0,x1,x2,h;
    n1 = 0;
    do
    {
        if (v[i] == '{')
            paranteze ++;
        if (v[i] == '}')
            paranteze --;
        i++;
    }
    while (paranteze != 0);
    strncpy(p,v,i);
    p[i] = '\0';
    i++;
    paranteze = 1;
    while (paranteze != 0)
    {
        if (v[i] == '{')
            paranteze ++;
        if (v[i] == '}')
            paranteze --;
        i++;
    }
    v[i] = '\0';
    strcpy (v,v+strlen(p));
    //////////////////////////////////////////////////////////////
    h = textheight(p);
    int supra = 0,sub = 0,div = 0,supra1 = 0, sub1 = 0,div1 = 0;
    if (strstr(p,"#d"))
        div = 1;
    char *q;
    q = strstr(p,"#t");
    if (q != NULL)
    {
        q = strstr(q+2,"#t");
        if (q == NULL)
            supra ++;
        else
            supra+= 2;
    }
    q = strstr(p,"#b");
    if (q != NULL)
    {
        q = strstr(q+2,"#b");
        if (q==NULL)
            sub ++;
        else
            sub += 2;
    }
    int termen_1;
    x1 = afisare(p,n1,x,y-h*div/2-h/2-h*sub/2,dimensiune_font);

    div = 0;
    sub = 0;
    supra = 0;

    if (strstr(v,"#d"))
        div1++;
    q = strstr(v,"#t");
    if (q != NULL)
    {
        q = strstr(q+2,"#t");
        if (q == NULL)
            supra1 += 1;
        else
            supra1 += 2;
    }
    q = strstr(v,"#b");
    if (q != NULL)
    {
        q = strstr(q+2,"#b");
        if (q==NULL)
            sub1 += 1;
        else
            sub1 += 2;
    }

    ///////////////////////////////////////////////////////////
    n1 = 0;
    x2 = afisare(v,n1,x,y+h/2+h*div1/2+h*supra1/2,dimensiune_font);
    line(x,y+textheight(p)/2+3,max(x1,x2),y+textheight(p)/2+3);
    x = max(x1,x2);
    n += strlen(v)+ strlen(p);
    return x;

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

int  draw_sum(char formula[100],int &n,int x,int y, int dimensiune_font)
{
    int h = textheight(formula);
    y += h/2+6;
    line (x,y,x+h/2,y);
    line (x,y,x+h/4,y+h/4);
    line (x+h/4,y+h/4,x,y+h/2);
    line (x,y+h/2,x+h/2,y+h/2);
    int i = 0,paranteze = 0,ok = 0;
    char v[100],p[100],d[100];
    strcpy(v,formula+n);
    do
    {
        if (v[i] == '{')
            paranteze ++;
        if (v[i] == '}')
            paranteze --;
        i++;
    }
    while (paranteze != 0);
    strncpy(p,v,i);
    p[i] = '\0';
    strcpy(v,v+i);
    cout <<v<<'\n';
    i = 0;
    paranteze = 0;
    do
    {
        if (v[i] == '{')
            paranteze ++;
        if (v[i] == '}')
            paranteze --;
        i++;
    }
    while (paranteze != 0);
    strncpy(d,v,i);
    d[i] = '\0';
    strcpy(v,v+strlen(d));
    i = 0;
    paranteze = 0;
    do
    {
        if (v[i] == '{')
            paranteze ++;
        if (v[i] == '}')
            paranteze --;
        i++;
    }
    while (paranteze != 0);

    v[i] = '\0';

    int n1 = 0,x_1,x_2,x_3;
    // cout <<p<<'\n'<<d<<'\n'<<v;
    x_1 = afisare(p,n1,x,y-textheight(p)/2-6,dimensiune_font/2);
    n1 = 0;
    x_2 = afisare (d,n1,x,y+textheight(d),dimensiune_font/2);
    n += strlen(d) + strlen(p) + strlen(v);
    x = max(x+30,max(x_1,x_2));
    n1 = 0;
    x_3 = afisare (v,n1,x,y-6,dimensiune_font);

    return x_3;
}


int produce(char formula[100],int &n, int x, int y, int dimensiune_font)
{
    int h = textheight(formula)/2;
    y += h/2+11;
    line (x,y,x+h,y);
    line (x+h/3,y,x+h/3,y+h);
    line (x+2*h/3,y,x+2*h/3,y+h);
    char v[100],p[100],d[100];
    strcpy(v,formula+n);

    int i = 0,paranteze = 0,ok = 0;
    do
    {
        if (v[i] == '{')
            paranteze ++;
        if (v[i] == '}')
            paranteze --;
        i++;
    }
    while (paranteze != 0);
    strncpy(p,v,i);
    p[i] = '\0';
    strcpy(v,v+i);
    cout <<v<<'\n';
    i = 0;
    paranteze = 0;
    do
    {
        if (v[i] == '{')
            paranteze ++;
        if (v[i] == '}')
            paranteze --;
        i++;
    }
    while (paranteze != 0);
    strncpy(d,v,i);
    d[i] = '\0';
    strcpy(v,v+strlen(d));
    i = 0;
    paranteze = 0;
    do
    {
        if (v[i] == '{')
            paranteze ++;
        if (v[i] == '}')
            paranteze --;
        i++;
    }
    while (paranteze != 0);

    v[i] = '\0';

    int n1 = 0,x_1,x_2,x_3;
    // cout <<p<<'\n'<<d<<'\n'<<v;
    x_1 = afisare(p,n1,x,y-textheight(p)/2-6,dimensiune_font/2);
    n1 = 0;
    x_2 = afisare (d,n1,x,y+textheight(d),dimensiune_font/2);
    n += strlen(d) + strlen(p) + strlen(v);
    x = max(x+30,max(x_1,x_2));
    n1 = 0;
    x_3 = afisare (v,n1,x,y-6,dimensiune_font);

    return (x_3);
}
int radical(char formula[100],int &n,int x,int y, int dimensiune_font)
{
    int paranteze = 0,i = 0;
    char v[100];
    strcpy(v,formula+n);
    do
    {
        if (v[i] == '{')
            paranteze ++;
        if (v[i] == '}')
            paranteze --;
        i++;
    }
    while (paranteze != 0);
    v[i] = '\0';
    n = n + strlen(v);
    char *p;
    p = v;
    int sus,jos;
    sus = 0;
    jos = textheight(p);
    int h = textheight(p);
    while (p!= NULL)
    {

        if (p[1] == 'd')
        {
            sus -= h/2;
            jos += h/2;
        }
        if (p[1] == 't')
        {
            sus -= h/3+4;
        }
        if (p[1] == 'b')
            jos += h/3+4;
        p = strchr(p+1,'#');
    }
    setlinestyle(0,0,3);
    line (x,y+textheight(v)/2,x+10,y+jos);
    line (x+10,y+jos,x+20,y+sus);
    int x_1;
    x = x + 24;
    int n1;
    x_1 = afisare(v,n1,x,y,dimensiune_font);
    line (x,y+sus-2,x_1,y+sus-2);
    x = x_1;
    n += n1;
    return x;

}


int afisare(char formula[100], int &n, int x, int y, int dimensiune_font)
{
    char q[2];
    int height = textheight("{");
    reset_font_size(dimensiune_font);
    int ok = 1;
    while (n < strlen(formula) && ok == 1)
    {
        reset_font_size(dimensiune_font);

        if (formula[n] != '#' && formula[n]!= '{' && formula[n]!='}')
        {
            q[0] = formula[n];
            q[1] = '\0';
            outtextxy(x,y,q);
            x += textwidth(q);
            n++;
        }
        else if (formula[n] == '#')
        {
            n++;
            switch(formula[n])
            {
            case 't' :
                n ++;
                x = afisare(formula,n,x,y-height/2,dimensiune_font / 2);
                break;
            case 'b' :
                n ++;
                x = afisare(formula,n,x,y+height/2,dimensiune_font / 2);
                break;
            case 'd':
                n++;
                x = division(formula,n,x,y,dimensiune_font);
                break;
            case 'q':
                n++;
                x = radical(formula,n,x,y,dimensiune_font);
                break;
            case 's':
                n++;
                x = draw_sum(formula,n,x,y,dimensiune_font);
                break;
            case 'p':
                n++;
                x = produce(formula,n,x,y,dimensiune_font);
                break;

            default:
            {
                int a_1,a_2;
                a_1 = formula[n]-'0';
                n++;
                a_2 = formula[n]-'0';
                n++;
                pt_formula(a_1*10+a_2,y,x,dimensiune_font);
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

void afisare_form(char a[101],int inaltime_ecran, int latime_ecran)
{
    setlinestyle(0,0,3);
    int x = 30, y = 600,n = 0;
    afisare (a,n,x,y,4);

}
