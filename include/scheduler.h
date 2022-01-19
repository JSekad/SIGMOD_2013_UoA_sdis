#ifndef __TPOOL_H__
#define __TPOOL_H__
#include <cstdlib>
#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>
#include <pthread.h>
#include "../sigmod_run/final-testdriver/include/core.h"

typedef void (*thread_func_t)(void *arg);

struct tpool_work {
    thread_func_t      func;
    void              *arg;
    struct tpool_work *next;
};
typedef struct tpool_work tpool_work_t;



typedef struct args{
    DocID idarg;
    char* docarg;
} args_t;

typedef args_t * pt_args;




struct tpool {
    tpool_work_t    *work_first;
    tpool_work_t    *work_last;
    pthread_mutex_t  work_mutex;
    pthread_cond_t   work_cond;
    pthread_cond_t   working_cond;
    size_t           working_cnt;
    size_t           thread_cnt;
    bool             stop;
};



struct tpool;
typedef struct tpool tpool_t;


void worker(void *arg);


void *tpool_worker(void *arg);

tpool_work_t *tpool_work_get(tpool_t *tm);
tpool_work_t *tpool_work_create(thread_func_t func, void *arg);
void tpool_work_destroy(tpool_work_t *work);
tpool_t *tpool_create(size_t num);
void tpool_destroy(tpool_t *tm);

bool tpool_add_work(tpool_t *tm, thread_func_t func, void *arg);
void tpool_wait(tpool_t *tm);

#endif /* __TPOOL_H__ */