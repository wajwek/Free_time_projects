#include <stdio.h>
#include <stdlib.h>

int* generate_table(int range) {
    int *tab = malloc(sizeof(int) * (range));
    if(!tab) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    return tab;
}

void fill_the_table(int *tab, int range) {

    for(int x = 0; x <= range; x++) {
        tab[x] = x;
    }
    tab[1] = 0; // 1 is not prime
    for(int i = 2; i <= range; i++) {
        if(tab[i] == 0) {
            continue;
        }
        for(int j = i * i; j <= range; j += i) {
            tab[j] = 0;
        }
    }

    for(int x = 0; x <= range; x++) {
        if(tab[x] != 0) {
            printf("[%d] ", tab[x]);
        }
    }
}

int main() {
    int range;

    printf("Set range: \n");
    scanf("%d", &range);

    if(range < 2) {
        printf("Range must be at least 2.\n");
        return 1;
    }
    int *tab = generate_table(range);
    fill_the_table(tab, range);

    free(tab);
    
    return 0;
}