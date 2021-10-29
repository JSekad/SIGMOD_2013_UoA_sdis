#include "entry_list.h"
#include "core.h"

typedef struct {} bktree;
typedef bktree index;

ErrorCode create_entry(const word* w, entry* e);

enum error_code create_entry(const word w, entry** e);

ErrorCode create_entry_list(entry_list* el);

unsigned int get_number_entries(const entry_list* el);
ErrorCode add_entry(entry_list* el, const entry* e);

entry* get_first(const entry_list* el);

entry* get_next(const entry_list* el);

ErrorCode destroy_entry_list(entry_list* el);

ErrorCode build_entry_index(const entry_list* el,MatchType type, index* ix);

ErrorCode lookup_entry_index(const word* w, index* ix, int threshold, entry_list* result);

ErrorCode destroy_entry_index(index* ix);