#ifndef STACK_H_
#define STACK_H_

#include <string.h>
#include <stdlib.h>

typedef enum {
    INT,
    CHARACTER,
    STRING,
    FLOAT,
    DECIMAL,
    JSON,
    ARRAY,
    RAW,
    INVALID,
} VariantType;

typedef union {
    int integer;
    char character;
    double decimal;
    float real;
    char* string;
    void* array;
} Variant;

typedef struct {
    void* prev; // this is Item ptr
    Variant value;
    VariantType type;
} Item;

void ItemInit(Item *item, Variant value, VariantType type) {
    item->value = value;
    item->type = type;
}

typedef struct {
    int size;
    Item* top;

} Stack;

void StackInit(Stack *stack) {
    stack->size = 0;
    stack->top = NULL;
}

Item StackPop(Stack *stack) {
    Item i;
    if(stack->size > 0) {
        Item *ptr;
        memcpy(&i, stack->top, sizeof(Item));
        ptr = stack->top;
        stack->top = ptr->prev;
        free(ptr);
        stack->size--;
    } else {
        i.type = INVALID;
    }
     return i;
}

void StackAppend(Stack *stack, Variant value, VariantType type) {
    Item *item;
    item = (Item*) malloc(sizeof(Item));
    ItemInit(item, value, type);

    item->prev = stack->top;
    stack->top = item;
    stack->size++;
}

#endif