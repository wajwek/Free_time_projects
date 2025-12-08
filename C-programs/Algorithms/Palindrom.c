#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *str;
    int len;
} String;

String read_string() {
    printf("Word to check: \n");
    int size = 16;
    int len = 0;
    char *str = malloc(size);

    if (!str) {
        printf("Memory error");
        exit(1);
    }

    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        str[len++] = c; //najpierw zapisze str[len], potem doda 1 do len
        
        if (len >= size) {
            size *= 2;
            str = realloc(str, size);
            if (!str) {
                printf("Memory error");
                exit(1);
            }
        }
    }
    str[len] = '\0';

    String result = {str, len};
    return result;
}

bool isPalindrome(char *word, int len) {
    for(int i = 0; i < len / 2; i++) {
        if(word[i] != word[len - i - 1]) {
            printf("%c    ", word[i]);
            printf("%c", word[len - i - 1]);
            return false;
        }
    }
    return true;
}

int main() {
    String word = read_string();
    if(isPalindrome(word.str, word.len)) {
        printf("This word is a palindrome");
    }
    else {
        printf("This word isnt a palindrome");
    }
    free(word.str);
    return 0;
}