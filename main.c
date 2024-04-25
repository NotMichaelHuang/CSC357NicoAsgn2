#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include "readlongwords.h"
#include "dict.h"


int alpha_numeric(const void *a, const void *b)
{
	int result;
	char *char_a, *char_b;
	
	result = 0;
	char_a = NULL;
	char_b = NULL;

	char_a = (*(Node **)a)->string;
	char_b = (*(Node **)b)->string;

	result = (*(Node **)b)->val - (*(Node **)a)->val;
	if(result == 0)
	{
		result = strcmp(char_a, char_b);
	}
	return result;
}

/*
 * This is the driver code that parse the command line or takeins in 
 * command from stdin. Put all the words from valid file into hashmap
 * then sort the hashmap and put the x most common words into stdout.
 *
 * Input:
 * 	int argc: total argc
 * 	char **argv: arrays of strings that represnt the command l
 * 		     ine arguments
 * Output:
 * 	return EXIT_SUCCESS if no error occured else EXIT_FAILURE
 * */
int main(int argc, char *argv[])
{
	char c;
	FILE *stream;	
	char *filename;
	size_t echelon;
	int argument_opt;
	int exit_code;	

	size_t iterate, top_size, freq_cap, freq_size;
	int space;
	char *t_str;
	char *output_msg;
	size_t t_val;
	Dict *freq_hash;
	Node **top_list;
	Node *next;

	stream = NULL;
	filename = NULL;
	echelon = 10; 		/* Default value */
	argument_opt = 0;
	exit_code = EXIT_SUCCESS;
	freq_hash = dctcreate();

	/*
 	* Check for either STDIN or an actual file was provided via argc
 	* */	
	if(argc == 1)
	{
		stream = stdin;
		
		/* Empty String */
		if((c = fgetc(stream)) == EOF)
		{
			fprintf(stderr, ERR);
			exit_code = EXIT_FAILURE;		
		}
		else
		{	
			ungetc(c, stream);
			/* Completed Hash table */
			load_words(freq_hash, stream);
		}
	}
	else
	{
		while((argument_opt = getopt(argc, argv, "n:")) != -1)
		{
			switch(argument_opt)	
			{
				case 'n':	
					echelon = atoi(optarg);	
					if(!echelon || echelon < 1)
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
		while(optind < argc)
		{	
			filename = argv[optind];
			stream = file_stream(filename);		
						
			if(stream != NULL)
			{	
				/* Empty String */
				if((c = fgetc(stream)) == EOF)
				{
					fprintf(stderr, ERR);
					exit_code = EXIT_FAILURE;		
				}
				else
				{	
					ungetc(c, stream);
					/* Completed Hash table */
					load_words(freq_hash, stream);
				}
			}	
			optind++;
		}
	}

	top_size = 0;
	freq_cap = freq_hash->cap;
	freq_size = freq_hash->size;
	output_msg = "The top %d words (out of %d) are:\n";
	printf(output_msg, (int)echelon,(int)freq_size);
	
	if(exit_code != EXIT_FAILURE)
	{
		/* Create the array that will list the top items */
		top_list = (Node **)calloc(freq_size, sizeof(Node *));	
		for(iterate = 0; iterate < freq_cap; iterate++)
		{
			if(freq_hash->arr[iterate] != NULL)
			{
				top_list[top_size] = freq_hash->arr[iterate];
				top_size++;
					
				next = freq_hash->arr[iterate]->next;
				while(next != NULL)
				{
					top_list[top_size] = next;
					next = next->next;
					top_size++;
				}
				
			}
		}
		qsort(top_list, freq_size, sizeof(Node *), alpha_numeric);

		space = 0;
		if(freq_size < echelon)
		{
			echelon = freq_size;
		}
		for(iterate = 0; iterate < echelon; iterate++)
		{
			if(top_list[iterate] != NULL)
			{
				t_str = top_list[iterate]->string;
				t_val = top_list[iterate]->val;
				if(iterate == 0)
				{
					space = 9;
				}
				printf("%*d %s\n", space, (int)t_val, t_str);
			}	
		}	
	}	
	return exit_code;
}


