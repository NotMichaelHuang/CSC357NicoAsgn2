/* Represents one key-value pair. */
/* Mqke link list */
typedef struct Node 
{
    char *string;
    unsigned int val;
    struct Node *next;
} Node;

/* Represents a collection of key-value pairs. */
typedef struct Dict 
{
    int cap;
    Node **arr;
    int size;
} Dict;


Dict *dctcreate();
void load_words(Dict *, FILE *);


