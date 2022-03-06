#include <iostream>
#include <string.h>
#include <fstream>
#include <graphics.h>
#include <conio.h>


void efectuare_calcule(char ecuatie[100],int n)
{
    char operator_pr[6][20];
    strcpy(operator_pr[0],"()");
    strcpy(operator_pr[1],"+,-");
    strcpy(operator_pr[2],"*,/");
    strcpy(operator_pr[3],"^");
    strcpy(operator_pr[4],"#=<>");
    strcpy(operator_pr[5],"cos,sin,ln,exp,abs,sqr");
    for (int i=0;i<n;i++)
        cout <<ecuatie[i];

}






