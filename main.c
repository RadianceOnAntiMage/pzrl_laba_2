#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lab.h"

int main(int argc, char *argv[]) {
    
    if (argc < 4) {
        fprintf(stderr, "Использование: ./prog <filename> -<режим> [args...]\n");
        return 1;
    }

    const char *filename = argv[1];
    const char *mode = argv[2];

    
    if (strcmp(mode, "-r") == 0) {
        if (argc != 5) {
            fprintf(stderr, "Использование: ./prog <filename> -r <старый текст> <новый текст>\n");
            return 1;
        }
        const char *old_text = argv[3];
        const char *new_text = argv[4];
        replace_text(filename, old_text, new_text);
    }
    
    else if (strcmp(mode, "-d") == 0) {
        if (argc != 4) {
            fprintf(stderr, "Использование: ./prog <filename> -d <текст для удаления>\n");
            return 1;
        }
        const char *text_to_delete = argv[3];
        delete_lines(filename, text_to_delete);
    }
    
    else if (strcmp(mode, "-i") == 0) {
        if (argc != 5) {
            fprintf(stderr, "Использование: ./prog <filename> -i <вариант: -f или -b> <текст для вставки>\n");
            return 1;
        }
        const char *text_to_insert = argv[4];
        
        if (strcmp(argv[3], "-f") == 0) {
            insert_text(filename, text_to_insert, 1);  
        } else if (strcmp(argv[3], "-b") == 0) {
            insert_text(filename, text_to_insert, 0);  
        } else {
            fprintf(stderr, "Недопустимый параметр для -i. Используйте -f или -b.\n");
            return 1;
        }
    }
    
    else {
        fprintf(stderr, "Недопустимые аргументы.\n");
        return 1;
    }

    return 0;
}
