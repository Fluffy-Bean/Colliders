#pragma once

#include <stdlib.h>
#include <stddef.h>
#include <assert.h>

#include "common.h"
#include "types.h"

#define ARRAY_START_SIZE 8
#define ARRAY_GROW_SIZE  2

#define DEFINE_ARRAY(T, PREFIX)                                                                                        \
    typedef struct {                                                                                                   \
        T      *data;                                                                                                  \
        size_t  capacity;                                                                                              \
        size_t  count;                                                                                                 \
    } PREFIX##_array_t;                                                                                                \
    void PREFIX##_array_Create(PREFIX##_array_t *array);                                                               \
    void PREFIX##_array_Destroy(PREFIX##_array_t *array);                                                              \
    void PREFIX##_array_Grow(PREFIX##_array_t *array);                                                                 \
    void PREFIX##_array_Push(PREFIX##_array_t *array, T item);                                                         \
    T    PREFIX##_array_Pop(PREFIX##_array_t *array);                                                                  \
    void PREFIX##_array_Set(PREFIX##_array_t *array, size_t index, T item);                                            \
    T*   PREFIX##_array_Get(PREFIX##_array_t *array, size_t index);

#define IMPLEMENT_ARRAY(T, PREFIX)                                                                                     \
    void PREFIX##_array_Create(PREFIX##_array_t *array)                                                                \
    {                                                                                                                  \
        array->capacity = ARRAY_START_SIZE;                                                                            \
        array->data     = malloc(array->capacity * sizeof(T));                                                         \
        array->count    = 0;                                                                                           \
    }                                                                                                                  \
    void PREFIX##_array_Destroy(PREFIX##_array_t *array)                                                               \
    {                                                                                                                  \
        free(array->data);                                                                                             \
        array->capacity = 0;                                                                                           \
        array->count    = 0;                                                                                           \
    }                                                                                                                  \
    void PREFIX##_array_Grow(PREFIX##_array_t *array)                                                                  \
    {                                                                                                                  \
        array->capacity = array->capacity * ARRAY_GROW_SIZE;                                                           \
        array->data     = realloc(array->data, array->capacity * sizeof(T));                                           \
    }                                                                                                                  \
    void PREFIX##_array_Push(PREFIX##_array_t *array, T item)                                                          \
    {                                                                                                                  \
        if (array->count == array->capacity)                                                                           \
            PREFIX##_array_Grow(array);                                                                                \
                                                                                                                       \
        array->data[array->count] = item;                                                                              \
        array->count += 1;                                                                                             \
    }                                                                                                                  \
    T PREFIX##_array_Pop(PREFIX##_array_t *array)                                                                      \
    {                                                                                                                  \
        assert(array->count > 0);                                                                                      \
        T popped = array->data[array->count - 1];                                                                      \
        array->count -= 1;                                                                                             \
        return popped;                                                                                                 \
    }                                                                                                                  \
    void PREFIX##_array_Set(PREFIX##_array_t *array, size_t index, T item)                                             \
    {                                                                                                                  \
        assert(index >= 0 && index < array->count);                                                                     \
        array->data[index] = item;                                                                                     \
    }                                                                                                                  \
    T* PREFIX##_array_Get(PREFIX##_array_t *array, size_t index)                                                       \
    {                                                                                                                  \
        assert(index >= 0 && index < array->count);                                                                     \
        return array->data + index;                                                                                    \
    }

DEFINE_ARRAY(rectangle_t, rectangle);
