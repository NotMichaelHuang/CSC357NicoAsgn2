#define ERR "Usage: fw [-n integer] filename\n"
#define INT_BUFFER_SIZE 256 /* Educated guess */

FILE *file_stream(char *);
char *read_long_words(FILE *);
char *resize_buffer(char *, size_t);


