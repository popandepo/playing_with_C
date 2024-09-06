#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int GetLen(const char* str);
int GetChars(const char* str[]);
typedef struct Person Person;
typedef struct Name Name;
typedef struct MemoryHolder MemoryHolder;

struct Person {
    int ID;
    Name* Name;
};

void FreePerson(Person* p) {
    free(p->Name);
    free(p);
}

struct Name {
    char* First;
    char* Middle;
    char* Last;
};

Name* CreateName(char* first, char* middle, char* last) {
    Name* n = malloc(sizeof(Name));
    n->First = first;
    n->Middle = middle;
    n->Last = last;
    return n;
}

struct MemoryHolder {
    void** ptr;
    int count;
};

/// Add - adds a pointer to the memory holder
/// @param mem - the memory holder to add the pointer to
/// @param ptr - the pointer to add to the memory holder
/// @return the memory holder with the new pointer added
MemoryHolder* Add(MemoryHolder* mem, void* ptr) {
    void** newArr = realloc(mem->ptr, (mem->count + 1) * sizeof(void*));

    if (newArr == NULL) {
        return NULL;
    }

    mem->ptr = newArr;
    mem->ptr[mem->count] = ptr;
    mem->count++;
    return mem;
}

MemoryHolder* CreateMemoryHolder() {
    MemoryHolder* mem = malloc(sizeof(MemoryHolder));
    mem->ptr = NULL;
    mem->count = 0;
    return mem;
}

void FreeMemory(MemoryHolder* mem) {
    if (mem == NULL) {
        return;
    }
    for (int i = 0; i < mem->count; i++) {
        printf("Freeing %p\n", mem->ptr[i]);
        free(mem->ptr[i]);
    }
    free(mem->ptr);
    free(mem);
}

int main(void) {
    MemoryHolder* mem = CreateMemoryHolder();
    Person* p = malloc(sizeof(Person));
    p->ID = 1;
    p->Name = CreateName("John", "Doe", "Smith");

    Person* p2 = malloc(sizeof(Person));
    p2->ID = 2;
    p2->Name = CreateName("Jane", "Doe", "Smith");
    mem = Add(mem, p->Name);
    mem = Add(mem, p);
    mem = Add(mem, p2->Name);
    mem = Add(mem, p2);

    printf("ID: %d\n", p->ID);
    printf("Name: %s %s %s\n", p->Name->First, p->Name->Middle, p->Name->Last);

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

    //read memory locations
    printf("\nMemory Locations:\n");
    for (int i = 0; i < mem->count; i++) {
        printf("Pointer %d: %p\n", i, mem->ptr[i]);
    }

    FreeMemory(mem);
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

/// GetChars - returns the number of characters in an array of strings
/// @param str - the array of strings to get the characters of
/// @return the number of characters in the array of strings
int GetChars(const char *str[]) {
    if (str == NULL) {
        return 0;
    }
    int c = 0;
    for (int i = 0; i < sizeof(str)/sizeof(str[0]); i++) {
        c += GetLen(str[i]);
    }
    return c;
}