
#include "../../include/entry_list.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


rec *CreateRecord(unsigned int id) {

    rec *new_entry = (rec *) malloc(sizeof(rec));
    new_entry->next = NULL;
    new_entry->id=id;


    return new_entry;

}

void DestroyRecord(rec **e) {
    //free(e->payload);
    free((*e));
    (*e)=NULL;
}


Sort_list *CreateSortList() {
    Sort_list * New = NULL;
    New= (Sort_list *) malloc(sizeof(Sort_list));
    New->first = NULL;
    New->last = NULL;
    New->total = 0;
    return New;
}


void DestroySortList(Sort_list **L) {

    if ((*L)->total > 0) {

        rec *current = (rec *) (*L)->first;

        while (current->next) {
            rec *next = (rec *) current->next;
            DestroyRecord(&current);
            current = next;
        }

        DestroyRecord(&current);
    }

    free(*L);
    *L=NULL;
}


void InsertSortedInList(Sort_list *L,unsigned int id) {
    //printf("InsertLastEntryList\n");
    //PrintPayload(&(e->payload));
    rec *m = CreateRecord(id);

    /* Special case for the head end */
    if (L->first == NULL
        || L->first->id
           > m->id) {
        m->next = L->first;
        L->first = m;
        L->total++;
    }
    else {
        rec * current = L->first;
        while (current->next != NULL
               && current->next->id < m->id) {
            current = current->next;
        }
        m->next = current->next;
        current->next = m;
        L->total++;

    }
}

void InsertNonsortedInList(Sort_list *L,unsigned int id) {
    //printf("InsertLastEntryList\n");
    //PrintPayload(&(e->payload));
    rec *m = CreateRecord(id);

    if (L->total > 0) {
        L->last->next = m;
        L->last = m;
        m->next = NULL;
        L->total++;
        return;
    }

    if (L->total == 0) {

        L->last = m;
        L->first = m;
        m->next = NULL;
        L->total++;
        return;
    }

}



Entry_list *CreateEntryList() {
    Entry_list* New = NULL;
    New= (Entry_list *) malloc(sizeof(Entry_list));
    New->current = NULL;
    New->first = NULL;
    New->last = NULL;
    New->numOfNodes = 0;
    return New;
}


void DestroyEntryList(Entry_list **L) {

    if ((*L)->numOfNodes > 0) {

        ent *current = (ent *) (*L)->first;

        while (current->next) {
            ent *next = (ent *) current->next;
            DestroyEntry(&current);
            current = next;
        }

        DestroyEntry(&current);
    }

    free(*L);
    *L=NULL;
}


void appendList(Entry_list **l1,Entry_list **l2) {
//     printf("in appendList\n");
//     printf("in appendList list1\n");
//     PrintEntryList(*l1);
//     printf("in appendList list2\n");
//     PrintEntryList(*l2);
    
    if ((*l1)->numOfNodes> 0){
        if ((*l2)->numOfNodes==0) return;
        (*l1)->last->next = (*l2)->first;
        (*l2)->first->prev=(*l1)->last;
        (*l1)->last=(*l2)->last;
        (*l1)->numOfNodes=(*l1)->numOfNodes+(*l2)->numOfNodes;
        return;
    }

      (*l1)->last=(*l2)->last;
      (*l1)->first=(*l2)->first;
      (*l1)->numOfNodes=(*l2)->numOfNodes;
      
      return;
    
}



void InsertLastEntryList(Entry_list *L, ent *e) {
   //printf("InsertLastEntryList\n");
    //PrintPayload(&(e->payload));
    ent *m = CreateEntry(e->w, e->payload);

    if (L->numOfNodes > 0) {
        m->prev = L->last;
        L->last->next = m;
        L->last = m;
        m->next = NULL;
        L->numOfNodes++;
        return;
    }

    if (L->numOfNodes == 0) {

        L->last = m;
        L->first = m;
        m->next = NULL;
        m->prev = NULL;
        L->numOfNodes++;
        return;
    }

}

entry * getFirstEntryOfList(Entry_list* e){
    e->current=e->first;
    return &e->current;
};

entry * getNextEntryOfList(Entry_list* e){
    e->current=e->current->next;
    return e->current == NULL ? NULL : &e->current;
};


void PrintEntryList(Entry_list *L) {

    printf("(");

    ent *N = (ent *) L->first;
    if (!N) {
        printf("())\n");
        return;
    }
    while (N->next != NULL) {

        printf("%s", N->w);
        if (N->next != NULL) printf(",");
        N = (ent *) N->next;
    }
    printf("%s", N->w);
    if (N->next != NULL) printf(",");

    printf(")\n");
}

ent *searchEntryList(Entry_list *L, word w) {
    ent *N = (ent *) L->first;
    while (N->next != NULL) {
        N = N->next;
        if (!strcmp(N->w, w))
            L->current=N->prev->next;
            return N;
    }
    if (!strcmp(N->w, w)) return N;
    return NULL;
}


/* MAYBE FUTURE USE


void InsertAfter(Entry_list *L, word A, ent *node) {
    ent *temp, *new;
    temp = node->next;
    new = (ent *) malloc(sizeof(ent));
    strcpy(new->w, A);
    new->next = temp;
    node->next = new;
}




void InsertFirstEntryList(Entry_list *L, ent *e) {
    ent *new_entry = CreateEntry(e->w, e->payload);
    if (L->numOfNodes > 0) {
        ent *m = L->first;
        m->prev = new_entry;
        L->first = new_entry;
        new_entry->next = m;
        L->numOfNodes++;
        return;
    }

    if (L->numOfNodes == 0) {
        L->last = new_entry;
        L->first = new_entry;
        new_entry->next = NULL;
        new_entry->prev = NULL;
        L->numOfNodes++;
    }


}


void DeleteLastEntryList(Entry_list *L) {
    ent *d = (ent *) L->last;

    L->last = d->prev;
    if (L->numOfNodes == 1) {
        L->first = NULL;
        L->last = NULL;
        L->numOfNodes--;
        free(d);
        return;
    }
    if (L->numOfNodes > 1) {
        ((ent *) L->last)->next = NULL;
        L->numOfNodes--;
        free(d);
        return;
    }
}

void DeleteFirstEntryList(Entry_list *L) {
    ent *d = (ent *) L->first;

    L->first = d->next;
    if (L->numOfNodes == 1) {
        L->first = NULL;
        L->last = NULL;
        L->numOfNodes--;
        DestroyEntry(&d);
        return;
    }
    if (L->numOfNodes > 1) {
        ((ent *) L->first)->prev = NULL;
        L->numOfNodes--;
        DestroyEntry(&d);
        return;
    }
}


void DeleteEntryEntryList(Entry_list *L, ent *node) {
    printf("Entry List\n");
    ent *e = (ent *) L->first;


    if (L->numOfNodes == 1) {
        if (!strcmp(e->w, node->w)) {


            DestroyEntry(&e);
            L->numOfNodes--;
            L->first = NULL;
            L->last = NULL;
        }

        return;
    }

    printf("Entry List 2\n");


    while (strcmp(e->w, node->w)) {
        printf("strcmp %s %s\n", e->w, node->w);
        if (!(e = e->next)) return;
    }

    printf("Entry List 3\n");


    if ((e->prev) && (e->next)) {

        e->prev->next = e->next;
        e->next->prev = e->prev;
        DestroyEntry(&e);
        L->numOfNodes--;
        return;

    }

    if (!e->prev) {
        e->next->prev = e->prev;
        DestroyEntry(&e);
        L->numOfNodes--;
        return;

    }

    if (!e->next) {
        e->prev->next = e->next;
        DestroyEntry(&e);
        L->numOfNodes--;
        return;

    }

}

     */

