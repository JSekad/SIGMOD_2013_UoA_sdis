
typedef void* Payload;
typedef char* word;



typedef struct NodeTag{
    Payload payload;
    word w;                                            /*hide dummy*/
    struct NodeTag *next; 
    struct NodeTag *prev;
} entry;



entry * CreateEntry(char *,Payload );

void DestroyEntry(entry *);

void InsertWord(const char *);

entry * InsertNextEntry (entry *previous,entry *next);





