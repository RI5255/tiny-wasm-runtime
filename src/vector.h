#pragma once

#include "error.h"
#include <stddef.h>

typedef struct {
    size_t  n;
    void    *elem;
} vector_t;

void vector_init(vector_t *vec);
error_t vector_new(vector_t *vec, size_t ent_size, size_t n);
void vector_copy(vector_t *dst, vector_t *src);
error_t vector_concat(vector_t *dst, vector_t *src1, vector_t *src2, size_t ent_size);

// useful macros
#define VECTOR(type)                                                                    \
    struct {                                                                            \
        size_t    n;                                                                    \
        type        *elem;                                                              \
    }
 
#define VECTOR_INIT(vec)                                                                \
    vector_init((vector_t *)vec)

#define VECTOR_NEW(vec, n)                                                              \
    vector_new((vector_t *)vec, sizeof(__typeof__(*(vec)->elem)), n)

#define VECTOR_COPY(dst, src)                                                           \
    vector_copy((vector_t *)dst, (vector_t *)src)

#define VECTOR_CONCAT(dst, src1, src2)                                                  \
    vector_concat(                                                                      \
        (vector_t *)dst,                                                                \
        (vector_t *)src1,                                                               \
        (vector_t *)src2,                                                               \
        sizeof(__typeof__(*(src1)->elem))                                               \
    )                                                                                   \

#define VECTOR_FOR_EACH(iter, vec)                                                      \
    for(__typeof__((vec)->elem) iter = &(vec)->elem[0];                                 \
        iter != &(vec)->elem[(vec)->n];                                                 \
        iter++                                                                          \
    )

#define VECTOR_FOR_EACH_REVERSE(iter, vec)                                              \
    for(__typeof__((vec)->elem) iter = &(vec)->elem[(vec)->n - 1];                      \
        (vec)->n != 0 &&  iter != &(vec)->elem[-1];                                     \
        iter--                                                                          \
    )

#define VECTOR_ELEM(vec, idx)                                                           \
    ({                                                                                  \
        size_t __i = (idx);                                                             \
        (vec)->n != 0 && 0 <= __i && __i <= ((vec)->n - 1) ? &(vec)->elem[__i] : NULL;  \
    })
