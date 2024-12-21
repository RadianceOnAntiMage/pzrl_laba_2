#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void replace_text(const char *filename, const char *old_text, const char *new_text) {
    FILE *file = fopen(filename, "r+"); // Open for reading and writing
    if (!file) {
        perror("Error opening file");
        return;
    }

    char line[1024];
    long pos;
    while ((pos = ftell(file)) != -1 && fgets(line, sizeof(line), file)) {
        char *temp = NULL;
        while ((temp = strstr(line, old_text)) != NULL) {
            fseek(file, pos, SEEK_SET);
            *temp = '\0';
            fprintf(file, "%s%s%s", line, new_text, temp + strlen(old_text));
            fseek(file, pos + strlen(line), SEEK_SET); // move file pointer back after modification
            break; // modify the first occurrence, then stop
        }
    }
    fclose(file);
}

void delete_lines(const char *filename, const char *text_to_delete) {
    FILE *file = fopen(filename, "r"); // Open for reading
    if (!file) {
        perror("Error opening file");
        return;
    }

    // Create a temporary file to write the modified content
    FILE *temp_file = fopen("temp.txt", "w");
    if (!temp_file) {
        perror("Error opening temporary file");
        fclose(file);
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, text_to_delete) == NULL) {
            fputs(line, temp_file); // Write line to temp file if it doesn't contain text_to_delete
        }
    }

    fclose(file);
    fclose(temp_file);

    // Remove the original file
    remove(filename);

    // Rename the temporary file to the original file name
    rename("temp.txt", filename);
}


void insert_text(const char *filename, const char *insert_text, int position_front) {
    FILE *file = fopen(filename, "r+"); // Открываем файл для чтения и записи
    if (!file) {
        perror("Ошибка при открытии файла");
        return;
    }

    // Прочитаем все строки в память
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t line_size;
    char *line = NULL;
    long pos = 0;

    // Сначала получаем размер файла
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Создаем буфер для хранения всего содержимого файла
    buffer = (char *)malloc(file_size + 1);
    if (!buffer) {
        perror("Ошибка выделения памяти");
        fclose(file);
        return;
    }

    // Читаем содержимое файла в буфер
    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0'; // Завершаем строку

    // Перезаписываем файл, начиная с первого байта
    fseek(file, 0, SEEK_SET);

    // Разбиваем файл на строки, чтобы вставить текст в нужное место
    char *line_start = buffer;
    char *line_end;
    
    while ((line_end = strchr(line_start, '\n')) != NULL) {
        *line_end = '\0';  // Заменяем символ новой строки на конец строки
        line = line_start;

        if (position_front) {
            fprintf(file, "%s%s\n", insert_text, line);  // Вставляем в начало строки
        } else {
            fprintf(file, "%s%s\n", line, insert_text);  // Вставляем в конец строки
        }

        line_start = line_end + 1;  // Переходим к следующей строке
    }

    // Записываем последнюю строку (если она есть)
    if (*line_start != '\0') {
        if (position_front) {
            fprintf(file, "%s%s\n", insert_text, line_start);
        } else {
            fprintf(file, "%s%s\n", line_start, insert_text);
        }
    }

    // Закрываем файл
    fclose(file);
    free(buffer);  // Освобождаем память
}
