typedef struct NodeTag {
    int numOfNodes;
    struct entry *first;                                             /*hide dummy*/
    struct entry *last;
} entry_list;


void  Delete(entry_list *,entry *);
  void InsertLast(entry_list * ,word);
  void PrintList(entry_list *);
  entry_list *Create(void);
  entry *search(entry_list *,word);
  void InsertAfter(entry_list *,word,entry *);
  void DeleteLast(entry_list *);
  void Destroy(entry_list *);