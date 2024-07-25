#include "parser.h"

FILE* open_file(char* filename) {
    return fopen(filename, "r");
}

void validate_json_file(FILE *file) {
    char* buff;
    int size;


    fseek(file, 0, SEEK_END);
    size = ftell(file);
    
    fseek(file, 0, SEEK_SET);
    buff = calloc(size+1, sizeof(char));

    fgets(buff, size+1, file);

    if(IsValidJson(buff)) {
        printf("This file is a vaild json\n");
        return;
    }
    
    printf("This file is not a vaild json\n");
};

int main(int argc, char** argv) {
    FILE *file;
    switch (argv[1][0])
    {
    case 'V':
    case 'v':
        file = open_file(argv[2]);
        if(file == NULL) {
            printf("This file doesn't exist\n");
            return -1;
        }
        
        validate_json_file(file);
    
    default:
        break;
    }

    fclose(file);

    return 0;
}