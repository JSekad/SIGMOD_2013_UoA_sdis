
typedef void *Payload;
typedef char *word;


typedef struct NodeTag {
    Payload payload;
    word w;                                            /*hide dummy*/
    struct NodeTag *next;
    struct NodeTag *prev;
} ent;

typedef ent *entry;


ent *CreateEntry(char *, Payload);

void DestroyEntry(ent **);





