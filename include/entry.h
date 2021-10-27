typedef void* Payload;
typedef char word[4];
typedef struct NodeTag {
    Payload payload;
    word w;                                            /*hide dummy*/
    struct NodeTag *Link;
} Entry;


typedef struct NodeTag {
    int numOfNodes;
    struct NodeTag *first;                                             /*hide dummy*/
    struct NodeTag *last;
} Entry_List;

Entry * CreateEntry(const char *,void *);

void DestroyEntry(Entry *);

void InsertWord(const char *);

Entry * InsertNextEntry (Entry *previous,Entry *next);





