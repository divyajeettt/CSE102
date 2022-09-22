# include <stdio.h>


int in(char *string, char character) {
    for (int i=0; string[i] != '\0'; i++) {
        if (string[i] == character)
            return 1;
    }
    return 0;
}


int check(char *s, char *t) {
    char vowels[5] = "aeoiu";

    int flag = 1;
    for (int i=0; t[i] != '\0'; i++) {
        if (!(in(s, t[i]) && !in(vowels, t[i])))
            flag = 0;
    }
    return flag;
}


int main() {
    char s[1000], t[1000];

    scanf("%s", &s);
    scanf("%s", &t);

    check(s, t) ? printf("Yes") : printf("No");

    return 0;
}