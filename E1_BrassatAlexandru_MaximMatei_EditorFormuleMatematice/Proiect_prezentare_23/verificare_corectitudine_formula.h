#include <iostream>
#include <string.h>
#include <fstream>
#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
int x = 30, y = 600;
bool ErrorFlag = false;
struct element
{
    int  tip = -1;
    char valoare[8];
};

struct sirTokeni
{
    int nrEl = 0;
    element v[100];
} sirTipuri;

struct nod
{
    nod* Lchild = NULL;
    element* op = NULL;
    nod* Rchild = NULL;
};
#define nrfnctii 9
char functii[][10] = {"sin", "cos", "tg", "ctg", "ln", "log", "f", "tan", "cot"};
int v[][20] =  ///ce elemente il pot urma
{
    /*0*/    {14,  10, 11, 12, 70, 50, 52, 53, 66, 62, 63, 64, 65, 69, -1}, //inceputul sirului (-1)
    /*1*/    {13,  10, 11, 12, 70, 50, 52, 53, 66, 62, 63, 64, 65, 69}, //([{
    /*2*/    {13,  10, 11, 12, 20, 21, 22, 40, 41, 42, 60, 61, 63, -1}, //)]}
    /*3*/    {12,  10, 11, 12, 50, 52, 53, 66, 62, 63, 64, 65, 69}, //+- (unary)
    /*4*/    {12,  10, 11, 12, 50, 52, 53, 66, 62, 63, 64, 65, 69}, //*/:^+-,= & functions
    /*5*/    {13,  10, 11, 12, 20, 21, 22, 40, 41, 42, 60, 61, -1, 67}, //numar
    /*6*/    {3,   10, 11, 12},  //# speciale
    //liste
    /*7*/    {6,   10, 11, 12, 66, 63, 70}, //op unari si paranteze deschise
    /*8*/    {2,   64, 65} //op trinari
};
/// "=,", "()", "+-", "*/:", "^"
///10 11 12 20 21 22    70      40     41   42     50     52       53      66    60   61   62  63   64   65   66   67   68    69      0
///{  [  (  )  ]  }   unary+-   <>=,   +-   /:*   int  double  literal functii  # t   b    d   q    s    p                 car_sp  nod_gol

bool apartine(int numar, int tipNr)
{//Brassat Alexandru
    int len = v[tipNr][0];
    for(int j = 1; j <= len; j++)
        if(numar == v[tipNr][j])
            return 1;
    return 0;
}

void sirTipToStr(sirTokeni sirTipuri, char sir[], int poz = 0, int numarDeCaractere = 999)
{//Brassat Alexandru
    sir[0] = 0;
    if(poz < 0)
        return;
    for(int i = 0; i < numarDeCaractere && poz+i <=sirTipuri.nrEl; i++)
    {
        if(sirTipuri.v[poz+i].tip/10 == 6)
            strcat(sir, "#");
        strcat(sir,sirTipuri.v[poz+i].valoare);
        strcat(sir," ");
    }
}

void throwErrorMessage(char mesaj[], int poz = -1)
{//Brassat Alexandru
    char sir[200] = "";
    ErrorFlag = true;
    setfillstyle(0,WHITE);
    bar (0, 225, 745, 745);
    outtextxy(x, y, mesaj);
    sirTipToStr(sirTipuri, sir, poz, 3);
    sir[35] = 0;
    outtextxy(x, y+ 23, sir);
}

void dissolve_AST(nod* p)
{//Brassat Alexandru
    if(p == NULL)
        return;
    dissolve_AST(p->Lchild);
    dissolve_AST(p->Rchild);
    delete p;
    return;
}

bool operate (nod* operanzi[], nod* operatori[], int &sfopz, int &sfopt)  //pop
{//Brassat Alexandru
    if(sfopt < 0 || sfopz < 0) goto Error;
    if(apartine(operatori[sfopt]->op->tip,7))  //paranteze, functii si +-unar {1 operand}
    {
        if(sfopz < 0)
            goto Error;
        nod* op1 = new nod;
        *op1 = *operanzi[sfopz];
        delete operanzi[sfopz];
        operanzi[sfopz] = new nod;
        *operanzi[sfopz] = *operatori[sfopt];
        operanzi[sfopz]->Lchild = op1;
        operanzi[sfopz]->Rchild = NULL;
        delete operatori[sfopt];
        sfopt--;
    }
    else if(apartine(operatori[sfopt]->op->tip,8))
    {
        //suma/produs {3 operanzi}
        if(sfopz<2)
            goto Error;
        nod* op1 = new nod;
        *op1 = *operanzi[sfopz];
        delete operanzi[sfopz];
        nod* op2 = new nod;
        *op2 = *operanzi[sfopz-1];
        delete operanzi[sfopz-1];
        nod* op3 = new nod;
        *op3 = *operanzi[sfopz-2];
        delete operanzi[sfopz-2];
        sfopz-=2;
        operanzi[sfopz] = new nod;
        *operanzi[sfopz] = *operatori[sfopt];
        operanzi[sfopz]->Lchild = new nod;
        operanzi[sfopz]->Lchild->op = new element;
        operanzi[sfopz]->Lchild->op->tip = 0;
        operanzi[sfopz]->Lchild->op->valoare[0] = '&';
        operanzi[sfopz]->Lchild->op->valoare[1] = 0;
        operanzi[sfopz]->Lchild->Lchild = op3;
        operanzi[sfopz]->Lchild->Rchild = op2;
        operanzi[sfopz]->Rchild = op1;
        delete operatori[sfopt];
        sfopt--;
    }
    else   // {2 operanzi}
    {
        if(sfopz < 1)
            goto Error;
        nod* op1 = new nod;
        *op1 = *operanzi[sfopz];
        delete operanzi[sfopz];
        nod* op2 = new nod;
        *op2 = *operanzi[sfopz-1];
        delete operanzi[sfopz-1];
        sfopz--;
        operanzi[sfopz] = new nod;
        *operanzi[sfopz] = *operatori[sfopt];
        operanzi[sfopz]->Lchild = op2;
        operanzi[sfopz]->Rchild = op1;
        delete operatori[sfopt];
        sfopt--;
    }
    return 1;
Error:
    throwErrorMessage("Argumente insuficiente");
    sfopt = -2;
    return 0;
}

void infixToArb(sirTokeni sir, nod* AST, nod* operanzi[], nod* operatori[], int &sfopz, int &sfopt)
{//Brassat Alexandru
    sfopz = sfopt = -1;
    for(int i = 1; i <= sir.nrEl && sfopt>=-1 && !ErrorFlag; i++)
    {
        if(sir.v[i].tip == 50 || sir.v[i].tip == 52 || sir.v[i].tip == 53 || sir.v[i].tip == 69)
        {
            // numar
            operanzi[++sfopz] = new nod;
            operanzi[sfopz]->op = new element;
            *operanzi[sfopz]->op = sir.v[i];
        }
        else  //operatii
        {

            if(sir.v[i].tip == 22)
            {
                while(!ErrorFlag && operatori[sfopt]->op->tip != 10)
                    operate(operanzi, operatori, sfopz, sfopt);
                operate(operanzi, operatori, sfopz, sfopt);
            }
            else if(sir.v[i].tip == 21)
            {
                while(!ErrorFlag && operatori[sfopt]->op->tip != 11)
                    operate(operanzi, operatori, sfopz, sfopt);
                operate(operanzi, operatori, sfopz, sfopt);
            }
            else if(sir.v[i].tip == 20)
            {
                while(!ErrorFlag && operatori[sfopt]->op->tip != 12)
                    operate(operanzi, operatori, sfopz, sfopt);
                operate(operanzi, operatori, sfopz, sfopt);
            }
            else
            {
                if(sir.v[i].tip>20)
                    while(!ErrorFlag && sfopt>=0 && (sir.v[i].tip < operatori[sfopt]->op->tip || (sir.v[i].tip/10 == 6 && operatori[sfopt]->op->tip/10 == 6)))
                        operate(operanzi, operatori, sfopz, sfopt);
                if(!ErrorFlag)
                {
                    operatori[++sfopt] = new nod;
                    operatori[sfopt]->op = new element;
                    *operatori[sfopt]->op = sir.v[i];
                }
            }
        }
    }
    while(sfopt>=0 && !ErrorFlag)
        operate(operanzi, operatori, sfopz, sfopt);
    if(sfopt<-1) operanzi[0] = NULL;
}

void buildAST(sirTokeni sirTipuri, nod* &AST)
{//Brassat Alexandru
    nod* operanzi[100];
    nod* operatori[100];
    int sfopt=0,sfopz = 0;
    infixToArb(sirTipuri, AST, operanzi, operatori, sfopz, sfopt);
    AST = operanzi[0];
}

int inaltime(nod* Nod, int depth = 0)
{//Brassat Alexandru
    if(!Nod->Lchild && !Nod->Rchild)
        return depth;
    int gradSt = 0, gradDr = 0;
    if(Nod->Rchild)
        gradDr = inaltime(Nod->Rchild, depth + 1);
    if(Nod->Lchild)
        gradSt = inaltime(Nod->Lchild, depth + 1);
    return max(gradSt, gradDr);
}

void drawNod(nod* Nod, int x, int y, int latura)
{//Brassat Alexandru
    settextstyle(1,0,1);
    outtextxy(x-textwidth(Nod->op->valoare)/2,y-textheight(Nod->op->valoare)/2,Nod->op->valoare);
}

int frunze(nod* Nod) {//Brassat Alexandru
    if(!Nod) return 0;
    if(!Nod->Rchild && !Nod->Lchild) return 1;
    return frunze(Nod->Lchild) + frunze(Nod->Rchild);
}

void afisareRecursiv(nod* Nod, int heightNivel, int nivel, int left, int top, int right, int bottom)
{//Brassat Alexandru
    if(Nod->Lchild)
    {
        if(!Nod->Rchild) {
            line((right + left)/2, top + heightNivel/2, (right+left)/2, top + heightNivel + heightNivel/2);
            afisareRecursiv(Nod->Lchild, heightNivel, nivel+1, left, top + heightNivel, right, bottom);
        }
        else {
            int distPerNod = (right-left)/(frunze(Nod));
            int allocForLeft = (frunze(Nod->Lchild));
            line((left+right)/2, top + heightNivel/2, (distPerNod*allocForLeft)/2 + left, top + heightNivel + heightNivel/2);
            afisareRecursiv(Nod->Lchild, heightNivel, nivel+1, left, top + heightNivel, left+distPerNod * allocForLeft, bottom);
                line((right + left)/2, top + heightNivel/2, (right + left + distPerNod*allocForLeft)/2, top + heightNivel + heightNivel/2);
                afisareRecursiv(Nod->Rchild, heightNivel, nivel+1, left+distPerNod * allocForLeft, top + heightNivel, right, bottom);
        }
    }
    drawNod(Nod, (right + left)/2, top + heightNivel/2, min(heightNivel*2/3,min(right-left - 3,bottom-top-3)));
    //rectangle(left, top, right, bottom);
}

void afisareArbore(nod* A, int padding = 10, int left = 0, int top = 0, int right = 999, int bottom = 999)
{//Brassat Alexandru
    right-=padding/2;
    left+=padding/2;
    bottom-=padding/2;
    top+=padding/2;
    int inaltimeArb = inaltime(A)+1;
    int heightNivel = (bottom - top)/(inaltimeArb);
    setfillstyle(0, WHITE);
    setlinestyle(0,1,2);
    bar(left,top,right,bottom);
    afisareRecursiv(A, heightNivel, 0, left, top, right, bottom);
}

void reset_sir()
{//Brassat Alexandru
    for(int i = 0; i<= sirTipuri.nrEl; i++)
    {
        sirTipuri.v[i].tip = -1;
        strcpy(sirTipuri.v[i].valoare,"");
    }
    sirTipuri.nrEl = 0;
}

bool verificare_tipuri(sirTokeni sirTipuri)
{//Brassat Alexandru
    int ok = 1;
    if(sirTipuri.nrEl<=0)
        return 0;
    for(int i = 0; i<=sirTipuri.nrEl; i++)
    {
        switch (sirTipuri.v[i].tip)
        {
        case 66:
            if(sirTipuri.v[i+1].tip==61 || sirTipuri.v[i+1].tip==60) {ok = 1; break;}
        case 70:
            ok = apartine(sirTipuri.v[i+1].tip, 3);
            break;
        case 67:
        case 69:
            ok = apartine(sirTipuri.v[i+1].tip, 5);
            break;
        default:
            ok = apartine(sirTipuri.v[i+1].tip, sirTipuri.v[i].tip/10);
            break;
        }
        if(!ok)
        {
            throwErrorMessage("Sintaxa incorecta", i);
            return 0;
        }
    }
    return 1;
}

void rearanjare_pt_functie(char formula[], int i) {//Brassat Alexandru
    if(formula[i] == '#' && (formula[i+1] == 't' || formula[i+1] == 'b')) {
        char *nou, nou2[300] = "", c = formula[i+1];
        nou = formula+i+2;
        partitionare(nou,nou2);
        nou+=strlen(nou2);
        if(nou[0] == '#' && (nou[1] == 't' || nou[1] == 'b') && nou[1] != c) {
            nou+=2;
            partitionare(nou,nou2);
            nou+=strlen(nou2);
        }
        int j = 0, nrp = 0;
        do{
            if(nou[j] == '(' || nou[j] == '{') nrp++;
            else if(nou[j] == ')' || nou[j] == '}') nrp--;
            nou2[j] = nou[j];
            j++;
        }while(nou+j!=0 && nrp!=0);
        if(j==1) {throwErrorMessage("Sintaxa incorecta!");return;}
        char aux[300];
        int x = nou-(formula+i);
        strncpy(aux, formula+i, x);
        strncpy(formula+i,nou2,j);
        strncpy((formula+i+strlen(nou2)),aux, x);
    aux[0]=0;
    }
}

bool tokenizare_sirTip (char formula[300])
{//Brassat Alexandru
    reset_sir();
    for(unsigned int i = 0;!ErrorFlag && i<strlen(formula); i++)
    {
        if(formula[i] == '(')
        {
            if(sirTipuri.v[sirTipuri.nrEl].tip == 20 || sirTipuri.v[sirTipuri.nrEl].tip == 21 || sirTipuri.v[sirTipuri.nrEl].tip == 22 || sirTipuri.v[sirTipuri.nrEl].tip == 50 || sirTipuri.v[sirTipuri.nrEl].tip == 52 || sirTipuri.v[sirTipuri.nrEl].tip == 53)  //pe langa
            {
                sirTipuri.v[++sirTipuri.nrEl].tip = 42;
                strcpy(sirTipuri.v[sirTipuri.nrEl].valoare,"*");
            }
            sirTipuri.v[++sirTipuri.nrEl].tip = 12;
            strcpy(sirTipuri.v[sirTipuri.nrEl].valoare,"(");
        }
        else if(formula[i] == ')')
        {
            sirTipuri.v[++sirTipuri.nrEl].tip = 20;
            strcpy(sirTipuri.v[sirTipuri.nrEl].valoare,")");
        }
        else if(formula[i] == '[')
        {
            if(sirTipuri.v[sirTipuri.nrEl].tip == 20 || sirTipuri.v[sirTipuri.nrEl].tip == 21 || sirTipuri.v[sirTipuri.nrEl].tip == 22 || sirTipuri.v[sirTipuri.nrEl].tip == 50 || sirTipuri.v[sirTipuri.nrEl].tip == 52 || sirTipuri.v[sirTipuri.nrEl].tip == 53)  //pe langa
            {
                sirTipuri.v[++sirTipuri.nrEl].tip = 42;
                strcpy(sirTipuri.v[sirTipuri.nrEl].valoare,"*");
            }
            sirTipuri.v[++sirTipuri.nrEl].tip = 11;
            strcpy(sirTipuri.v[sirTipuri.nrEl].valoare,"[");
        }
        else if(formula[i] == ']')
        {
            sirTipuri.v[++sirTipuri.nrEl].tip = 21;
            strcpy(sirTipuri.v[sirTipuri.nrEl].valoare,"]");
        }
        else if(formula[i] == '{')
        {
            sirTipuri.v[++sirTipuri.nrEl].tip = 10;
            strcpy(sirTipuri.v[sirTipuri.nrEl].valoare,"{");
        }
        else if(formula[i] == '}')
        {
            sirTipuri.v[++sirTipuri.nrEl].tip = 22;
            strcpy(sirTipuri.v[sirTipuri.nrEl].valoare,"}");
        }
        else if(strchr("+-",formula[i]))
        {
            sirTipuri.v[++sirTipuri.nrEl].tip = 41;
            if(sirTipuri.v[sirTipuri.nrEl-1].tip < 20 || sirTipuri.v[sirTipuri.nrEl-1].tip/10==4 || sirTipuri.v[sirTipuri.nrEl-1].tip==66)
                sirTipuri.v[sirTipuri.nrEl].tip = 70;// +- unary
            sirTipuri.v[sirTipuri.nrEl].valoare[0]=formula[i];
            sirTipuri.v[sirTipuri.nrEl].valoare[1]='\0';
        }
        else if(formula[i] == '!')
        {
            sirTipuri.v[++sirTipuri.nrEl].tip = 55;
            strcpy(sirTipuri.v[sirTipuri.nrEl].valoare,"!");
        }
        else if(strchr("/*:",formula[i]))
        {
            sirTipuri.v[++sirTipuri.nrEl].tip = 42;
            sirTipuri.v[sirTipuri.nrEl].valoare[0]=formula[i];
            sirTipuri.v[sirTipuri.nrEl].valoare[1]='\0';
        }
        else if(strchr("<>=,",formula[i]))
        {
            sirTipuri.v[++sirTipuri.nrEl].tip = 40;
            sirTipuri.v[sirTipuri.nrEl].valoare[0]=formula[i];
            sirTipuri.v[sirTipuri.nrEl].valoare[1]='\0';
        }
        else if(isdigit(formula[i]))
        {
            sirTipuri.v[++sirTipuri.nrEl].tip = 50;
            int len = -1;
            while(isdigit(formula[i]) && i < strlen(formula))
            {
                sirTipuri.v[sirTipuri.nrEl].valoare[++len] = formula[i];
                i++;
            }
            if(formula[i]=='.')
            {
                sirTipuri.v[sirTipuri.nrEl].tip = 52;
                sirTipuri.v[sirTipuri.nrEl].valoare[++len] = formula[i];
                i++;
                while(isdigit(formula[i]) && i < strlen(formula))
                {
                    sirTipuri.v[sirTipuri.nrEl].valoare[++len] = formula[i];
                    i++;
                }
            }
            sirTipuri.v[sirTipuri.nrEl].valoare[++len]=0;
            i--;
        }
        else if(formula[i] == '#')
        {
            sirTipuri.v[++sirTipuri.nrEl].tip = 60;
            i++;
            char c[]="tbdqsp";
            if(strchr(c,formula[i]))
            {
                sirTipuri.v[sirTipuri.nrEl].tip += strchr(c,formula[i])-c;
                sirTipuri.v[sirTipuri.nrEl].valoare[0] = formula[i];
                sirTipuri.v[sirTipuri.nrEl].valoare[1] = '\0';
            }
            else if(strchr("0123456789",formula[i]) && strchr("0123456789",formula[i+1]))
            {
                sirTipuri.v[sirTipuri.nrEl].tip = 69;
                sirTipuri.v[sirTipuri.nrEl].valoare[0] = formula[i];
                sirTipuri.v[sirTipuri.nrEl].valoare[1] = formula[i+1];
                sirTipuri.v[sirTipuri.nrEl].valoare[2] = '\0';
                i = i+1;
            }
            else
            {
                throwErrorMessage("eroare de operatori speciali", i);
                return 0;
            }
        }
        else if(formula[i] == ' ');
        else if(isalpha(formula[i]))
        {
            if(sirTipuri.v[sirTipuri.nrEl].tip == 20 || sirTipuri.v[sirTipuri.nrEl].tip == 21 || sirTipuri.v[sirTipuri.nrEl].tip == 22)  //pe langa
            {
                sirTipuri.v[++sirTipuri.nrEl].tip = 42;
                strcpy(sirTipuri.v[sirTipuri.nrEl].valoare,"*");
            }
            sirTipuri.v[++sirTipuri.nrEl].tip = 53;
            int len = -1, j = 0;
            while(isalpha(formula[i]) && i < strlen(formula) && j < 6)
            {
                sirTipuri.v[sirTipuri.nrEl].valoare[++len] = formula[i];
                i++;
                j++;
            }

            sirTipuri.v[sirTipuri.nrEl].valoare[++len]=0;
            //functie
            for(int j = 0; j < nrfnctii; j++)
                if(strcmp(sirTipuri.v[sirTipuri.nrEl].valoare, functii[j])==0)
                {
                    sirTipuri.v[sirTipuri.nrEl].tip = 66;
                    rearanjare_pt_functie(formula, i);
                    break;
                }
            if(!ErrorFlag) i--;
        }
        else if(strlen(formula)-i > 2 && formula[i] == formula[i+1] && formula[i+1] == formula[i+2] && formula[i+2] == '.') {
            sirTipuri.v[++sirTipuri.nrEl].tip = 53;
            strcpy(sirTipuri.v[sirTipuri.nrEl].valoare,"...");
            i+=2;
        }
        else
        {
            throwErrorMessage("Caracter invalid");
            outtextxy(x, y+23, formula+i);
            return 0;
        }
    }
    return 1;
}

bool verificare_ordine_tipuri(char formula[300])
{//Brassat Alexandru
    return tokenizare_sirTip(formula) && verificare_tipuri(sirTipuri);
}

bool verificare_ordine_paranteze(char formula[300]) // ordine si numar
{//Maxim Matei
    char stak[40];
    int top = -1,i;
    for(i = 0; i<strlen(formula); i++)
    {
        if (strchr("([{",formula[i]))
        {
            top++;
            stak[top] = formula[i];

        }
        if (strchr(")]}",formula[i]))
        {
            top--;
        }
    }

    if (top == -1)
        return true;
    else
    {
        throwErrorMessage("Nu aveti suficiente paranteze");
        return false;

    }
}

bool verificare_formula(char formula[300], bool showAST = 0)
{//Brassat Alexandru
    char formulal[300];
    strcpy(formulal, formula);
    ErrorFlag = false;
    if (verificare_ordine_paranteze(formulal) && verificare_ordine_tipuri(formulal) && !ErrorFlag)
    {
        nod* AST = NULL;
        buildAST(sirTipuri, AST);
        if(AST)
        {
            if(showAST)
                afisareArbore(AST, 20, 0, 250, 745, 745);
            dissolve_AST(AST);
        }
        else {
            dissolve_AST(AST);
            return 0;
        }
        return 1;
    }
    return 0;

}
