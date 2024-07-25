#ifndef PARSER_H_
#define PARSER_H_

#include "stack.h"
#include "stdio.h"

typedef struct {
    void* parent; // This is a json ptr
    Variant value;
    VariantType type;
} Json;

void JsonInit(Json *obj, Json *parent, Variant value, VariantType type) {
    obj->parent = parent;
    obj->type = type;
    obj->value = value;
}

void CalculateJsonSize(int *buffer, char* string) {
    Stack stack;
    char character;
    Variant value;
    VariantType type;
    int i;
    int len;
    
    StackInit(&stack);
    i = 0;
    len = 1;
    type = CHARACTER;
    
    do {
        character = string[i];

        switch (character)
        {
        case '{':
        case '[':
            value.character = character;
            StackAppend(&stack, value, type);
            break;
        case '}':
        case ']':
            StackPop(&stack);
            break;
        case ',':
            len++;
            break;
        default:
            break;
        }
        i++;
    } while(i < strlen(string));

    *buffer = len;

}

int IsValidJson(char* string) {
    Stack stack;
    char character;
    Variant value;
    int iter, offset;
    
    StackInit(&stack);
    iter = 0;
    offset = 0;
    char* buff;

    do {
        character = string[iter+offset];
        offset++;
        
        #ifdef DEBUG_MODE
        printf("i: %u, o: %u, c: \'%c\', s: %u", iter, offset, character, stack.size);
        if(stack.top == NULL) {
            printf("\n");
        } else if(stack.top->type == CHARACTER) {
            printf(" , top: %c\n", stack.top->value.character);
        } else {
            printf(" , top: %s\n", stack.top->value.string);
        }
        #endif

        switch (character) {
            case '\"':
                if(stack.top != NULL) {
                    if(stack.top->type == STRING && (strchr(stack.top->value.string, (int)'\"') != NULL)) {
                        StackPop(&stack);
                    } else if (stack.top->type == CHARACTER && stack.top->value.character == '\"') {
                        StackPop(&stack);
                    }
                }
            case '{':
            case '[':
                if(offset > 1) {
                    buff = malloc(16*sizeof(char));

                    strncpy(buff, string+(sizeof(char)*iter), offset);
                    buff[offset] = '\0';
                    value.string = buff;
                    StackAppend(&stack, value, STRING);
                    iter += offset;
                } else {
                    value.character = character;
                    StackAppend(&stack, value, CHARACTER);
                    iter++;
                }
                offset = 0;
                break;
            case '}':
                StackPop(&stack);
                iter += offset;
                offset = 0;
                break;
            case ']':
                StackPop(&stack);
                iter += offset;
                offset = 0;
                break;
            case ',':
                if(stack.top->value.character == '\'' || stack.top->value.character == '\"' ) {
                    StackPop(&stack);
                    StackPop(&stack);
                }
                iter += offset;
                offset = 0;
                break;
            case ':':
                StackPop(&stack);
                iter += offset;
                offset = 0;
                break;
            default:
                break;
        }
    
    } while(iter < strlen(string) && stack.size > 0);

    #ifdef DEBUG_MODE
    printf("size: %u, i: %u, len: %llu\n", stack.size, iter, strlen(string));
    printf("s: \"%s\", l: %llu\n", string, strlen(string));
    printf("   ");
    for(int i=0; i < iter; i++) {
        printf("-");
    }
    printf("^\n");
    #endif
    
    return (iter == strlen(string) && stack.size == 0);
}

/*void ParseJson(Json* obj, char* string) {
    if(!IsValidJson(string)) {
        return;
    }

    Stack stack;
    Variant value;
    VariantType type;
    int iter, offset;
    char character;
    char buffer[32];
    
    iter = 0;
    offset = 0;

    while(iter < strlen(string)) {
        character = string[iter];
        iter++;
        switch (character)
        {
        case '{':
        case '[':
            value.character = iter;
            type = CHARACTER;
            StackAppend(&stack, value, type);
            break;

        default:
            offset++;
        }
    }
}*/

#endif