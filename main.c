#include <stdio.h>
#include <string.h>

int GetLen(const char *str);
int GetChars(const char *str[]);
int main(void) {
    char *holder[] = {"Hello", " ", "world", "!"};

    int characters = GetChars(holder);

    char string[characters + 1];
    int counter = 0;
    for (int i = 0; i < sizeof(holder)/sizeof(holder[0]); i++) {
        char * temp = holder[i];
        for (int j = 0; j < GetLen(temp); j++) {
            string[counter] = temp[j];
            counter++;
        }
    }
    string[counter] = '\0';

    printf("%s\n", string);
    return 0;
}

/// GetLen - returns the human-readable length of a string
/// @param str - the string to get the length of
/// @return the length of the string (excluding the null terminator)
int GetLen(const char *str) {
    if (str == NULL) {
        return 0;
    }
    int i = 0;
    for (i = 0; str[i] != '\0'; i++) {
        //empty statement to increment i
    }
    return i;
}

int GetChars(const char *str[]) {
    if (str == NULL) {
        return 0;
    }
    int c = 0;
    for (int i = 0; i < 3; i++) {
        c += GetLen(str[i]);
    }
    return c;
}