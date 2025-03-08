#include "shared.h"
#include "file.h"

#include <stdio.h>
#include <stdlib.h>

int f_read_text_file(const char *filename, const char **text, int *len)
{
    FILE *fp = fopen(filename, "r");

    if (fp == NULL) {
        LOG_ERR("failed to load file '%s' not found.", filename);
        return 1;
    }

    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *buf = (char*)calloc(1, size);

    if (buf == NULL) {
        LOG_ERR("failed to load file '%s' memory error.", filename);
        fclose(fp);
        return 1;
    }

    if (fread(buf, size, 1, fp) == 0) {
        LOG_ERR("failed to load file '%s' reading file.", filename);
        fclose(fp);
        return 1;
    }

    *text = buf;
    *len = size;

    fclose(fp);

    return 0;
}