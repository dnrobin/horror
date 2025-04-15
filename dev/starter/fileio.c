#include "shared.h"

#include <stdio.h>
#include <string.h>

char *f_read_text_file(const char *filename)
{
    FILE *fp;
    size_t sz;

    char *data = NULL;

    fp = fopen(filename, "r");
    if (!fp) {
        LOGTRACE_ERROR("failed to open file '%s' for reading.", filename);
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    sz = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    data = malloc(sz + 1);
    if (!data) {
        LOGTRACE_ERROR("failed to allocating memory for file '%s' with size %zu bytes.", filename, sz);
        goto err;
    }

    if (fread(data, sz, 1, fp) == 0) {
        LOGTRACE_ERROR("failed to read file '%s'.", filename);
        goto err;
    }

    data[sz] = '\0';

    fclose(fp);

    return data;

err:
    if (data) free(data);
    fclose(fp);
    return NULL;
}

void f_write_text_file(const char *filename, const char *data)
{
    FILE *fp;
    size_t sz;

    fp = fopen(filename, "w");
    if (!fp) {
        LOGTRACE_ERROR("failed to open file '%s' for writing.", filename);
        return;
    }

    sz = strlen(data);

    if (fwrite(data, sz, 1, fp) == 0) {
        LOGTRACE_ERROR("failed to write file '%s'.", filename);
    }

    fclose(fp);
}

void f_append_text_file(const char *filename, const char *data)
{
    FILE *fp;
    size_t sz;

    fp = fopen(filename, "a");
    if (!fp) {
        LOGTRACE_ERROR("failed to open file '%s' for writing.", filename);
        return;
    }

    sz = strlen(data);

    if (fwrite(data, sz, 1, fp) == 0) {
        LOGTRACE_ERROR("failed to write file '%s'.", filename);
    }

    fclose(fp);
}

void *f_read_file_binary(const char *filename, size_t *sz)
{
    FILE *fp;

    void *data = NULL;

    fp = fopen(filename, "rb");
    if (!fp) {
        LOGTRACE_ERROR("failed to open file '%s' for reading.", filename);
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    *sz = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    data = malloc(*sz);
    if (!data) {
        LOGTRACE_ERROR("failed to allocating memory for file '%s' with size %zu bytes.", filename, *sz);
        goto err;
    }

    if (fread(data, *sz, 1, fp) == 0) {
        LOGTRACE_ERROR("failed to read file '%s'.", filename);
        goto err;
    }

    fclose(fp);

    return data;

err:
    if (data) free(data);
    fclose(fp);
    return NULL;
}

void f_write_file_binary(const char *filename, const void *data, size_t sz)
{
    FILE *fp;

    fp = fopen(filename, "wb");
    if (!fp) {
        LOGTRACE_ERROR("failed to open file '%s' for writing.", filename);
        return;
    }

    if (fwrite(data, sz, 1, fp) == 0) {
        LOGTRACE_ERROR("failed to write file '%s'.", filename);
    }

    fclose(fp);
}
