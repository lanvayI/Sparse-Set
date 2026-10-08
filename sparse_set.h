#ifndef SPARSE_SET_H
#define SPARSE_SET_H

#define INVALID_ID 99999
typedef unsigned int uint32_t;

typedef struct SSET{
    uint32_t *dense;
    size_t *sparse;
    size_t n,max,element_size;
}SSET;

SSET* ss_init(size_t capacity, size_t sizeOfElement);
int ss_has(SSET* s, size_t id);
int ss_insert(SSET* s, size_t id, void* value);
void *ss_getPtr(SSET* s, size_t id);
int ss_remove(SSET* s,size_t id);
int ss_free(SSET* s);

#endif