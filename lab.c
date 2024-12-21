#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void replace_text(const char *filename, const char *old_text, const char *new_text) {
    FILE *file = fopen(filename, "r+"); 
    if (!file) {
        perror("ошибка открытия файла");
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
            fseek(file, pos + strlen(line), SEEK_SET); 
            break; 
        }
    }
    fclose(file);
}

void delete_lines(const char *filename, const char *text_to_delete) {
    FILE *file = fopen(filename, "r"); 
    if (!file) {
        perror("ошибка открытия файла");
        return;
    }

    
    FILE *temp_file = fopen("temp.txt", "w");
    if (!temp_file) {
        perror("Ошибка открытия временого файла");
        fclose(file);
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, text_to_delete) == NULL) {
            fputs(line, temp_file); 
        }
    }

    fclose(file);
    fclose(temp_file);

    
    remove(filename);

    
    rename("temp.txt", filename);
}


void insert_text(const char *filename, const char *insert_text, int position_front) {
    FILE *file = fopen(filename, "r+"); 
    if (!file) {
        perror("Ошибка при открытии файла");
        return;
    }

    
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t line_size;
    char *line = NULL;
    long pos = 0;

    
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    
    buffer = (char *)malloc(file_size + 1);
    if (!buffer) {
        perror("Ошибка выделения памяти");
        fclose(file);
        return;
    }

    
    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0'; 

    
    fseek(file, 0, SEEK_SET);

    
    char *line_start = buffer;
    char *line_end;
    
    while ((line_end = strchr(line_start, '\n')) != NULL) {
        *line_end = '\0';  
        line = line_start;

        if (position_front) {
            fprintf(file, "%s%s\n", insert_text, line);  
        } else {
            fprintf(file, "%s%s\n", line, insert_text);  
        }

        line_start = line_end + 1;  
    }

    
    if (*line_start != '\0') {
        if (position_front) {
            fprintf(file, "%s%s\n", insert_text, line_start);
        } else {
            fprintf(file, "%s%s\n", line_start, insert_text);
        }
    }

    
    fclose(file);
    free(buffer);  
}
