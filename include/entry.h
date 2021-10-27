typedef void* Payload;
typedef char word[4];
typedef struct NodeTag {
    Payload payload;
    word w;                                            /*hide dummy*/
    struct NodeTag *Link;
} entry;



entry * Createentry(const char *,void *);

void Destroyentry(entry *);

void InsertWord(const char *);

entry * InsertNextEntry (entry *previous,entry *next);





