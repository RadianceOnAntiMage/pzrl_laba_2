#ifndef LAB_H
#define LAB_H


void replace_text(const char *filename, const char *old_text, const char *new_text);


void delete_lines(const char *filename, const char *text_to_delete);


void insert_text(const char *filename, const char *insert_text, int position_front);

#endif 
