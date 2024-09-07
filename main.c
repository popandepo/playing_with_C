#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person Person;
typedef struct Name Name;
typedef struct MemoryHolder MemoryHolder;
typedef struct MemorySafe MemorySafe;

int GetLen(const char* str);
int GetChars(const char* str[]);
void Add(MemoryHolder* mem, void* ptr);
void AddPersonToMemory(void* obj, MemoryHolder* mem);
void AddNameToMemory(void* obj, MemoryHolder* mem);
Person* CreatePerson(int id, Name* name);
Name* CreateName(char* first, char* middle, char* last);

/// MemorySafe - a struct that contains a function pointer to add an object to memory
/// @param AddToMemory - a function pointer to add an object to memory
/// @return a MemorySafe struct
/// @note this struct is used to add objects to memory
struct MemorySafe {
    void(*AddToMemory)(void* obj, MemoryHolder* mem);
};

/// Name - a struct that contains a first, middle, and last name
/// @param First - the first name
/// @param Middle - the middle name
/// @param Last - the last name
/// @param MemorySafe - a MemorySafe struct that contains a function pointer to add the name to memory
/// @return a Name struct
/// @note this struct is used to store a person's name
struct Name {
    char* First;
    char* Middle;
    char* Last;
    MemorySafe MemorySafe;
};

/// CreateName - creates a new name struct
/// @param first - the first name
/// @param middle - the middle name
/// @param last - the last name
/// @return a new Name struct
/// @note this function is used to create a new name struct
Name* CreateName(char* first, char* middle, char* last) {
    Name* n = malloc(sizeof(Name));
    n->First = strdup(first);
    n->Middle = strdup(middle);
    n->Last = strdup(last);

    n->MemorySafe.AddToMemory = AddNameToMemory;

    return n;
}

/// AddNameToMemory - adds a name to memory
/// @param obj - the name to add to memory
/// @param mem - the memory holder to add the name to
/// @note this function is used to add a name to memory
void AddNameToMemory(void* obj, MemoryHolder* mem) {
    Name* n = obj;
    if (n == NULL || mem == NULL) {
        return;
    }
    Add(mem, n->First);
    Add(mem, n->Middle);
    Add(mem, n->Last);
    Add(mem, n);
}

/// Person - a struct that contains an ID and a name
/// @param ID - the ID of the person
/// @param Name - the name of the person
/// @param MemorySafe - a MemorySafe struct that contains a function pointer to add the person to memory
/// @return a Person struct
/// @note this struct is used to store a person's ID and name
struct Person {
    int ID;
    Name* Name;
    MemorySafe MemorySafe;
};

/// CreatePerson - creates a new person struct
/// @param id - the ID of the person
/// @param name - the name of the person
/// @return a new Person struct
/// @note this function is used to create a new person struct
Person* CreatePerson(int id, Name* name) {
    Person* p = malloc(sizeof(Person));
    p->ID = id;
    p->Name = name;

    p->MemorySafe.AddToMemory = AddPersonToMemory;

    return p;
}

/// AddPersonToMemory - adds a person to memory
/// @param obj - the person to add to memory
/// @param mem - the memory holder to add the person to
/// @note this function is used to add a person to memory
void AddPersonToMemory(void* obj, MemoryHolder* mem) {
    Person* p = obj;
    if (p == NULL || mem == NULL || p->Name == NULL) {
        return;
    }

    p->Name->MemorySafe.AddToMemory(p->Name, mem);
    Add(mem, p);
}

/// MemoryHolder - a struct that contains an array of pointers and a count of pointers
/// @param pointers - an array of pointers
/// @param count - the number of pointers in the array
/// @return a MemoryHolder struct
/// @note this struct is used to store pointers to memory for later freeing
struct MemoryHolder {
    void** pointers;
    int count;
};

/// Add - adds a pointer to the memory holder
/// @param mem - the memory holder to add the pointer to
/// @param ptr - the pointer to add to the memory holder
/// @return the memory holder with the new pointer added
void Add(MemoryHolder* mem, void* ptr) {
    if (mem == NULL) {
        return;
    }

    void** newArr = realloc(mem->pointers, (mem->count + 1) * sizeof(void*));

    if (newArr == NULL) {
        return;
    }

    mem->pointers = newArr;
    mem->pointers[mem->count] = ptr;
    mem->count++;
}

/// CreateMemoryHolder - creates a new memory holder struct
/// @return a new MemoryHolder struct
/// @note this function is used to create a new memory holder struct
MemoryHolder* CreateMemoryHolder() {
    MemoryHolder* mem = malloc(sizeof(MemoryHolder));
    mem->pointers = NULL;
    mem->count = 0;
    return mem;
}

/// FreeMemory - frees the memory in the memory holder
/// @param mem - the memory holder to free the memory of
/// @note this function is used to free the memory in the memory holder
void FreeMemory(MemoryHolder* mem) {
    if (mem == NULL) {
        return;
    }
    for (int i = 0; i < mem->count; i++) {
        printf("Freeing %p\n", mem->pointers[i]);
        free(mem->pointers[i]);
    }
    free(mem->pointers);
    free(mem);
}

int main(void) {
    MemoryHolder* mem = CreateMemoryHolder();

    Person* p = CreatePerson(1, CreateName("John", "Doe", "Smith"));
    Person* p2 = CreatePerson(2, CreateName("Jane", "Doe", "Smith"));

    p->MemorySafe.AddToMemory(p, mem);
    p2->MemorySafe.AddToMemory(p2, mem);

    printf("ID: %d\n", p->ID);
    printf("Name: %s %s %s\n", p->Name->First, p->Name->Middle, p->Name->Last);

    //read memory locations
    printf("\nMemory Locations:\n");
    for (int i = 0; i < mem->count; i++) {
        printf("Pointer %d: %p\n", i, mem->pointers[i]);
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