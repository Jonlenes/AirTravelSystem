#include "Util.h"
#include <string.h>
#include <iostream>

Util::Util()
{
}

char *Util::remove(char *strChr, char chrStop, int qtdCaracter)
{
    int length = strlen(strChr);
    int count = 0;
    int i;

    for(i = 0; i < length && count < qtdCaracter; i++)
        if(chrStop == strChr[i]) count++;
    int j;
    for(j = 0; i < length; i++, j++)
        strChr[j] = strChr[i];
    strChr[j] = 0;

    return strChr;
}
