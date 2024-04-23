#include <stdio.h>
#include <stdib.h>
#include <string.h>
#include "dict.h"


Dict *dctcreate();
Node *nodelookup(Dict *, char *);
Node **dct_resize(Node **, size_t, size_t);
unsigned int dctlookup(Dict *);
void transfer(Node *, Node **, size_t);
void chain_node(Node *, Node *, size_t);
size_t hash_index(char *, size_t);


size_t hash_index(char *str, size_t cap)
{
	size_t index, hash;
	hash = dcthash(str);
	index = hash_index(str, cap);

	return index
}


size_t dcthash(char *key)
{
	size_t code, i;
	
	code = 0;
	for(i = 0; i < 8 && key[i] != '\0'; i++)
	{
		code = key[i] + 31 * code;
	}
	return code;
}


Dict *dctcreate()
{
	size_t i, d_size;

	/* Constructor */
	d_size = 10; 		/* Inital array size */
	Dict *initialize;

	initialize = (Dict *)malloc(sizeof(Dict));
	initialize->cap = d_size;
	initialize->arr = (Node **)calloc(sizeof(Node *) * d_size);
	initialize->size = 0;

	return initialize;
}


Dict *load_words(FILE*fd)
{
	char c;
	char *str;
	Dict *dct;
	Node *exist_node;
	
	dct = dctcreate();
	exist_node = NULL;

	/* Loading words */
	while((c = fgetc(fd)) != EOF)
	{
		ungetc(c, fd);
		str = read_long_words(fd);
		exist_node = nodelookup(dct);
		if(exist_node != NULL)
		{
			exist_node0->val++;
		}
		else
		{
			dctinsert(dct, str, freq);
		}	
	}
	
	return dct;
}


void dctinsert(Dict *dct, char *string, void *val)
{
	int arr_size, arr_cap;
	size_t index;

	/* Create need entry */
	Node *new_node;

	arr_size = dct->size;
	arr_cap = dct->cap;

	/* Need resize? */
	if(arr_size >= arr_cap)
	{
		int neo_size;
		neo_size = arr_cap *= 2;

		dct->arr = dct_resize(dct->arr, arr_cap, neo_cap);	
	}

	/* Getting the proper collisionless key */
	index = hash_index(string, arr_cap);
	
	new_node = (Node *)malloc(sizeof(Node));	
	new_node->string = string;
	new_node->val = val;
	new_node->next = NULL;

	arr_size++;

	/* Need Chaining? */
	if(dct->arr[index] != NULL)
	{
		chain_node(dct->arr[index], new_node, index);
	}
}


Node **dct_size(Node **dct, size_t cap, size_t new_cap)
{
	size_t iterate;

	/* Need to create tmp Node arr for transfer */
	Node **tmp;
	tmp = (Node **)calloc(new_cap, sizeof(Node *));	

	for(iterate = 0; iterate <= cap; iterate++)
	{
		if(dct[iterate] != NULL)
		{
			transfer(dct[index], tmp, new_cap);			
		}
	}	
	/* No Longer need the old array */
	free(dct);

	return tmp;
}


void transfer(Node *linked_nodes, Node **node_array, size_t cap)
{
	size_t index;
	char *string;
	Node *current, *next;

	current = linked_nodes;
	while(current->next != NULL)
	{
		next = current->next;

		/* Transfer current node to new array */
		string = current->string;
		index = hash_index(string, cap);
		
		if(node_array[index] != NULL)
		{
			chain_node(node_array[index], current);
		}
		else
		{
			node_array[index] = current;
		}	
		current = next; /* Next node */		
	}
	/* Last node does not contain an address to next node */
	string = current->string;
	index = hash_index(string, cap);

	if(node_array[index] != NULL)
	{
		chain_node(node_array[index], current)
	}
	else
	{
		node_array[index] = current;
	}	
}


void chain_node(Dict *dct, Node *new_entry, size_t index)
{
	/* Get the head of the link list in the array */
	Node *head;	
	
	/* Find the end of the list */	
	head = dct->arr[index];
	while(head->next != NULL)	
	{
		/* Keep going until end of list */
		head = head->next;
	}
	
	/* Should be at the end of the list by now */
	head->next = new_entry;
}


Node *nodelookup(Dict *dct, char *str)
{
	size_t index;
	Node **node_list;
	Node *return_node;

	index = hash_index(str);
	node_list = dct->arr[index];
	return_node = NULL;
	while(node_list->next != NULL)
	{
		if(strcmp(node_list->string, str) == 0)	
		{
			return_node = node_list;
			break;
		}
		node_list = node_list->next;
	}	
	return return_node;
}


