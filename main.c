#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lab.h"

int main(int argc, char *argv[]) {
    // Проверка на минимальное количество аргументов
    if (argc < 4) {
        fprintf(stderr, "Usage: prog.exe <filename> -<mode> [args...]\n");
        return 1;
    }

    const char *filename = argv[1];
    const char *mode = argv[2];

    // Обработка режима замены текста
    if (strcmp(mode, "-r") == 0) {
        if (argc != 5) {
            fprintf(stderr, "Usage: prog.exe <filename> -r <old_text> <new_text>\n");
            return 1;
        }
        const char *old_text = argv[3];
        const char *new_text = argv[4];
        replace_text(filename, old_text, new_text);
    }
    // Обработка режима удаления строк
    else if (strcmp(mode, "-d") == 0) {
        if (argc != 4) {
            fprintf(stderr, "Usage: prog.exe <filename> -d <text_to_delete>\n");
            return 1;
        }
        const char *text_to_delete = argv[3];
        delete_lines(filename, text_to_delete);
    }
    // Обработка режима вставки текста
    else if (strcmp(mode, "-i") == 0) {
        if (argc != 5) {
            fprintf(stderr, "Usage: prog.exe <filename> -i <option: -f or -b> <text_to_insert>\n");
            return 1;
        }
        const char *text_to_insert = argv[4];
        // Проверка на флаг вставки в начало или в конец
        if (strcmp(argv[3], "-f") == 0) {
            insert_text(filename, text_to_insert, 1);  // Вставка в начало строки
        } else if (strcmp(argv[3], "-b") == 0) {
            insert_text(filename, text_to_insert, 0);  // Вставка в конец строки
        } else {
            fprintf(stderr, "Invalid option for -i. Use -f or -b.\n");
            return 1;
        }
    }
    // Если переданы неверные аргументы
    else {
        fprintf(stderr, "Invalid arguments.\n");
        return 1;
    }

    return 0;
}
