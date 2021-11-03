#include "entry_list.h"
#include "core.h"
#include <stdio.h>

typedef struct {
} bktree;
typedef bktree index;

enum error_code {
    Working = 0,
    Failed = 1,
    Freezed = 2
};

enum error_code create_entry(const word w, entry *e);

enum error_code destroy_entry(ent *e);

enum error_code create_entry_list(entry_list *el);

unsigned int get_number_entries(const entry_list *el);

enum error_code add_entry(entry_list *el, const ent *e);

ent *get_first(const entry_list *el);

ent *get_next(const entry_list *el);

enum error_code destroy_entry_list(entry_list *el);

enum error_code build_entry_index(const entry_list *el, MatchType type, index *ix);

enum error_code lookup_entry_index(const word *w, index *ix, int threshold, entry_list *result);

enum error_code destroy_entry_index(index *ix);