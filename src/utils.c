#include "../include/utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file(const char *filename) {
    FILE *file = NULL;
    long file_size = 0;
    char *buffer = NULL;
    size_t result = 0;

    file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    rewind(file);

    if (file_size < 0) {
        perror("Error getting the file size");
        fclose(file);
        return NULL;
    }

    buffer = (char*)malloc(file_size+1);
    if (buffer == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    result = fread(buffer, file_size, 1, file);
    if (result != 1) {
        perror("Error reading file content");
        free(buffer);
        fclose(file);
        return NULL;
    }

    buffer[file_size] = '\0';
    fclose(file);

    return buffer;
}
