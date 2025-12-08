#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int suma_kwadratow(int x) {
    int suma = 0; 
    while (x > 0) {
        int cyfra = x % 10;
        suma += cyfra * cyfra ;
        x /= 10;
    }
    return suma;
}
bool czy_w_tablicy(int* liczby,int pojemnosc,int szukana) {
    for(int i = 0; i < pojemnosc; i++) {
        if (liczby[i] == szukana) {
            return true;
        }
    }
    return false;
}
bool czy_szczesliwa(int x){
    if (x <= 1) {
        return true;
    }
    else {
        int licznik = 1;
        int pojemnosc = 4;
        int* liczby = malloc(sizeof(int) * pojemnosc);
        if (!liczby) {
            return 0;
        }
        int i = 0;
        while (x != 1) {
            if (licznik == pojemnosc) {
                pojemnosc *= 2;
                liczby = (int*)realloc(liczby, sizeof(int) * pojemnosc);
                if (!liczby) {
                    return 0;
                }
            }
            liczby[i] = x;
            x = suma_kwadratow(x);
            if (czy_w_tablicy(liczby, pojemnosc, x)) {
                return false;
            }
            i++;
            licznik++;
        }
        free(liczby);
        return true;
    }
}
int main() {
    int a;
    printf("Podaj zakres: \n");
    scanf("%d", &a);
    for(int i = 0; i <= a; i++){
        if(czy_szczesliwa(i)){
            printf("%d \n", i);
        }
    }
    return 0;
}