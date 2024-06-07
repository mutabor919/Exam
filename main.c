#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct Vector {
    int *data;
    int size;
    int capacity;
    struct Vector *next;
} Vector;

Vector* createVector(int capacity) {
    Vector *vec = (Vector*)malloc(sizeof(Vector));
    vec->data = (int*)malloc(capacity * sizeof(int));
    vec->size = 0;
    vec->capacity = capacity;
    vec->next = NULL;
    return vec;
}

void addElement(Vector *vec, int element) {
    if (vec->size == vec->capacity) {
        Vector *newVec = createVector(vec->capacity * 2);
        vec->next = newVec;
        addElement(newVec, element);
    } else {
        vec->data[vec->size] = element;
        vec->size++;
    }
}

int getElement(Vector *vec, int index) {
    Vector *current = vec;
    while (index >= current->size) {
        index -= current->size;
        current = current->next;
    }
    return current->data[index];
}

void deleteVector(Vector *vec) {
    if (vec->next != NULL) {
        deleteVector(vec->next);
    }
    free(vec->data);
    free(vec);
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    Vector *vec = createVector(3);
    addElement(vec, 1);
    addElement(vec, 2);
    addElement(vec, 3);
    addElement(vec, 4);

    printf("Элемент по индексу 2: %d\n", getElement(vec, 2));

    deleteVector(vec);

    return 0;
}