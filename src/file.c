#include "shared.h"
#include "file.h"

#include <stdio.h>
#include <stdlib.h>

int f_read_text_file(const char *filename, char **data, size_t *len)
{
	FILE *fp = fopen(filename, "r");

	if (!fp) {
		FATAL_RET("Error loading file '%s'!\n", filename);
	}
	
    fseek(fp, 0, SEEK_END);
    size_t n = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *p = (char*)calloc(1, n + 1);

    if (!p) {
        FATAL_RET("Error allocating memory for file '%s'!\n", filename);
    }

    if (fread(p, n, 1, fp) == 0) {
        FATAL_RET("Failed to read text file '%s'!\n", filename);
    }
    
    *data = p;
    *len = n;

    fclose(fp);

    return 0;
}