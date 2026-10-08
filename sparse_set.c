#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "sparse_set.h"

SSET* ss_init(size_t capacity, size_t sizeOfElement){
    SSET *s = malloc(sizeof(SSET));
    if(s==NULL){return NULL;}
    uint32_t *d = calloc(capacity,sizeOfElement);
    if(d==NULL){free(s);return NULL;}
    size_t* sp = malloc(sizeof(size_t)*INVALID_ID);
    if(sp==NULL){free(d);free(s); return NULL;}

    for(size_t i=0; i < INVALID_ID; i++){
        sp[i] = INVALID_ID;
    }

    s->dense = d;
    s->sparse = sp;
    s->n = 0;
    s->max = capacity;
    s->element_size = sizeOfElement;
    return s;
}

int ss_has(SSET*s, size_t id){
    if(s->sparse[id]==INVALID_ID){return 0;}
    return 1;
}

int ss_insert(SSET *s, size_t id,void* value){
    if(ss_has(s,id)){return 0;}
    memcpy(
        s->dense + s->n,
        (uint32_t*)value,
        s->element_size
    );
    s->sparse[id] = s->n++;
    return 1;
}

void *ss_getPtr(SSET *s, size_t id){
    if(!ss_has(s,id)){return NULL;}
    return &(s->dense[s->sparse[id]]);
}

int ss_remove(SSET *s,size_t id){
    if(!ss_has(s,id)){return 0;}

    size_t lastDense = s->n - 1;
    size_t lastId = s->sparse[lastDense];
    size_t index = s->sparse[id];
    if(lastId != index){
        memcpy(
            s->dense + index * s->element_size,
            s->dense + lastId * s->element_size,
            s->element_size
        );
        s->dense[index] = lastDense;
        s->sparse[lastDense] = index;
    }
    s->sparse[id] = INVALID_ID;
    s->n--;
    return 1;
}

int ss_free(SSET* s){
    if(s==NULL){return 0;}
    free(s->dense);
    free(s->sparse);
    s->dense = NULL;
    s->sparse = NULL;
    free(s);
    return 1;
}