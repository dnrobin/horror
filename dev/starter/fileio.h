#ifndef __FILE_IO_H__
#define __FILE_IO_H__

char *f_read_text_file(const char *filename);
void f_write_text_file(const char *filename, const char *data);
void f_append_text_file(const char *filename, const char *data);
void *f_read_file_binary(const char *filename, size_t *sz);
void f_write_file_binary(const char *filename, const void *data, size_t sz);

#endif