#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "readlongwords.h"


/*
 * Read string and return a file descriptor if valid.
 *
 * Input:
 * 	char *pot_file: potential file name
 *
 * Output:
 * 	returns a valid file descriptor else NULL
 * */
FILE *file_stream(char *pot_file)
{
	FILE *valid_fd;
	
	valid_fd = fopen(pot_file, "r");	
	if(valid_fd == NULL)
	{
		perror(ERR);
	}
	return valid_fd;
}


/*
 * This funcation reads in a char at a time to construct a word.
 * Only stopping if it encoutners space, newline, or EOF. In addition,
 * EOF and/or newline are not included in the constructed string
 * from the file stream.
 *
 * Input:
 * 	FILE *stream: This is a file descriptor in the open file index.
 *
 * Output:
 * 	char *output_str: This char * points to the completed word which
 * 			  then would be return form this function.	
 * 			  NOTE: the "complete" word does not contain spaces,
 * 			        newline, or EOF.
 * */
char *read_long_words(FILE *stream)
{
	char *output_str;
	char c;
	size_t index, buffer;

	/* Priming the first Letter */
	index = 0;
	buffer = INT_BUFFER_SIZE;
	output_str = (char *)calloc(buffer, sizeof(char));

	while(isalpha((c = fgetc(stream))))
	{	
		/* Need more memory on the HEAP!!!!
		 * This max index in the array include 0 so buffer needs to be
		 * -1. In addition, we need to account of a null-terminator, so
		 * another -1, hence index max "safe range" is at max
		 * buffer -2
		 * */
		if(index == (buffer - 2))
		{
			/* Increase the current buffer 2x per convention */
			buffer *= 2;

			output_str = resize_buffer(output_str, buffer);	
		}
		/* lower case if char is capital */
		/* 97 is lowercase a and 32 is the offset between the
 		 * uppercase and their respected lower case counter part
 		 * */
		if(c < 97)
		{
			c += 32;
		}
		output_str[index] = c;
		index++;
	}	
	/* Give it a null terminator */
	output_str[index] = '\0';
	if(strlen(output_str) < 1)
	{
		output_str = NULL;
	}	
	return output_str;
}


/*
 * This function resize the HEAP memory via realloc with the given new buffer.
 * Notes by convention the new buffer should be double of the current buffer.
 *
 * Input:
 * 	char *str: char * ptr that contains the current char array
 * 	size_t new_buffer: New buffer the user want the current string to
 * 		           occupy
 * 
 * Output:
 * 	char *new_str: char * ptr containing the same char array with 
 * 	               a increase size on success else -1 if failed.	
 * */
char *resize_buffer(char *str, size_t new_buffer)
{
	char *new_str;

	new_str = realloc(str, sizeof(char) * new_buffer);
	if(new_str == NULL)
	{
		fprintf(stderr, "Failed to realloc\n");
	
		/* Realloc does not free on failure */
		free(str);

		exit(EXIT_FAILURE);
	}
	return new_str;
}


