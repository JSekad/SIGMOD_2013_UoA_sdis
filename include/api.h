#ifndef LISTOFENTRY_H
#define LISTOFENTRY_H
#include "bktree.h"
#include "core.h"
#include <stdio.h>
#include <string.h>

enum error_code {
    Working = 0,
    Failed = 1,
};

enum error_code create_entry(const word w, entry *e);

enum error_code destroy_entry(entry *e);

enum error_code create_entry_list(entry_list *el);

enum error_code add_entry(entry_list *el, const entry *e);

unsigned int get_number_entries(const entry_list *el);

entry *get_first(const entry_list *el);

entry *get_next(const entry_list *el);

enum error_code destroy_entry_list(entry_list *el);

enum error_code build_entry_index(const entry_list *el, MatchType type, inDex *ix);

enum error_code lookup_entry_index(const word *w, inDex *ix, int threshold, entry_list *result);

enum error_code destroy_entry_index(inDex *ix);

#endif /* GRANDPARENT_H */