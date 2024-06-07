#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <assert.h>

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

//Тесты.
void testCreateVector() {
    Vector *vec = createVector(5);

    assert(vec != NULL);  // Проверка, что вектор создан
    assert(vec->data != NULL);  // Проверка, что данные выделены
    assert(vec->size == 0);  // Проверка начального размера
    assert(vec->capacity == 5);  // Проверка начальной емкости
    assert(vec->next == NULL);  // Проверка, что следующий узел пуст

    deleteVector(vec);
}

void testAddElement() {
    Vector *vec = createVector(2);

    addElement(vec, 1);
    addElement(vec, 2);
    addElement(vec, 3);

    // Проверка размера и данных в первом узле
    assert(vec->size == 2);
    assert(vec->data[0] == 1);
    assert(vec->data[1] == 2);

    // Проверка наличия и данных в следующем узле
    assert(vec->next != NULL);
    assert(vec->next->size == 1);
    assert(vec->next->data[0] == 3);

    deleteVector(vec);
}

void testGetElement() {
    Vector *vec = createVector(4);

    addElement(vec, 1);
    addElement(vec, 2);
    addElement(vec, 3);
    addElement(vec, 4);

    // Проверка получения элементов по индексам
    assert(getElement(vec, 0) == 1);
    assert(getElement(vec, 1) == 2);
    assert(getElement(vec, 2) == 3);
    assert(getElement(vec, 3) == 4);

    deleteVector(vec);  // Освобождение памяти
}

void testDeleteVector() {
    Vector *vec = createVector(2);

    addElement(vec, 1);
    addElement(vec, 2);
    addElement(vec, 3);

    // Здесь проверяем, что deleteVector не вызывает сбоев
    deleteVector(vec);

    assert(1);
}

void  test() {
    testCreateVector();
    testAddElement();
    testGetElement();
    testDeleteVector();
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    test();

    return 0;
}