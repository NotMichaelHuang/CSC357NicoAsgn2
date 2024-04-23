#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include "readlongwords.h"
#include "dict.h"


/*
 * 1. Read a file or a redirect
 * 	Input:
 * 		fopen, fclose(), etc. or STDIN
 * 		process input with read_long_line(FILE *fd);
 * 		Notes Read long word can take STDIN as the compiler buffer
 * 		      user inputs which can be in replacement of fd
 * 2. Store word
 * 	Parse the string provided by read long line and store it in a hashmap
 * 	Method of storage: a dynamic array of linked list
 * 		sruct taht contains the word and it's frequency
 * 	
 * */
int main(int argc, char *argv[])
{
	FILE *stream;	
	char *filename;
	char *long_word;
	size_t echelon;
	int argument_opt;
	Dict *freq_hash;

	stream = NULL;
	filename = NULL;
	long_word = NULL;
	echelon = 10;
	argument_opt = 0;

	/*
 	* Check for either STDIN or an actual file was provided via argc
 	* */
	if(argc == 1)
	{
		/* stdin */
	}
	else if(argc == 4 || argc == 2)
	{	
		while((argument_opt = getopt(argc, argv, "n:")) != -1)
		{
			switch(argument_opt)	
			{
				case 'n':	
					echelon = atoi(optarg);	
					if(!echelon)
					{
						fprintf(stderr, ERR);
						exit(EXIT_FAILURE);
					}
					break;
	
				default:
					fprintf(stderr, ERR);
					exit(EXIT_FAILURE);
			}
		}
		printf("%s %d\n", argv[optind], echelon);
		filename = argv[optind];
		stream = file_stream(filename);
	}
	else
	{
		fprintf(stderr, "Invalid arguments\n");
		fprintf(stderr, ERR);
		exit(EXIT_FAILURE);
	}
	freq_hash = load_words(stream);

	/* TODO: pet program */
	char c;	
	char *str;
	while((c = fgetc(stream)) != EOF)
	{
		ungetc(c, stream);	
		str = read_long_words(stream);
		printf("-%s\n", str);
		free(str);
	}

	return EXIT_SUCCESS;
}


