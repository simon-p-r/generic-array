#ifndef GENERIC_ARRAY_GENERIC_ARRAY_H
#define GENERIC_ARRAY_GENERIC_ARRAY_H

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>


#define define_array_h(typeName, valueType)                                         \
                                                                                    \
    typedef struct typeName {                                                     \
        valueType* entries;                                                          \
        void *user;                                                                  \
        size_t length;                                                               \
        size_t capacity;                                                             \
        size_t size;                                                                 \
    } typeName;                                                                      \
                                                                                        \
    typedef void (*typeName ## _iter_t)(typeName *array, valueType entry, size_t index);  \
                                                                                     \
    typeName *typeName ## _new();                                                    \
    void typeName ## _free(typeName *array);                                         \
    void typeName ## _push(typeName *array, valueType value);                        \
    void typeName ## _foreach(typeName *array, void *func);                          \
    void typeName ## _set(typeName *array, size_t index, valueType value);            \
    valueType typeName ## _get(typeName *array, size_t index);                        \
    valueType typeName ## _pop(typeName *array);                                 

#define define_array_c(typeName, valueType, compareFn, defaultVal)                   \
    typeName *typeName ## _new(void *user) {                                        \
        const size_t initial_size = 16;                                             \
        typeName *array = calloc(1, sizeof(*array));                               \
        array->user = user;                                                          \
        array->length = 0;                                                          \
        array->capacity = initial_size;                                             \
        array->size = sizeof(valueType);                                            \
        array->entries = calloc(initial_size, sizeof(valueType));                   \
        return array;                                                                \
    }                                                                                \
                                                                                     \
    void typeName ## _free(typeName *array) { \
        free(array->entries);                                                        \
        free(array);                                                                 \
        array = NULL;                                                                 \
    };                                                                               \
                                                                                     \
    void typeName ## _push(typeName *array, valueType value) {                       \
        if (array->length >= array->capacity) {                                      \
            array->capacity *= 2;                                                     \
            array->entries = realloc(array->entries, array->size * array->capacity);  \
        }                                                                             \
        array->entries[array->length] = value;                                        \
        array->length++;                                                               \
    };                                                                                 \
                                                                                       \
    void typeName ## _foreach(typeName *array, typeName ## _iter_t func) {            \
        for (size_t i = 0; i < array->length; ++i)  {                                 \
            valueType var = array->entries[i];                                        \
            func(array->user, var, i);                                                \
        }                                                                             \
    }                                                                                 \
                                                                                      \
    void typeName ## _set(typeName *array, size_t index, valueType value) {           \
        if (index <= array->length) {                                                  \
            array->entries[index] = value;                                            \
        }                                                                             \
    };                                                                                \
                                                                                      \
    valueType typeName ## _get(typeName *array, size_t index) {                       \
        if (index <= array->length) {                                                  \
            return array->entries[index];                                             \
        }                                                                            \
        return defaultVal;                                                            \
    }                                                                                 \
                                                                                      \
    valueType typeName ## _pop(typeName *array) {                                       \
        if(array->length > 0) {                                                         \
            array->length--;                                                           \
            return array->entries[array->length];                                      \
        }                                                                               \
        return defaultVal;                                                               \
    }                 


// The name is type of object and type is element within array.
define_array_h(void_ptr_array, void *)
define_array_h(string_array, char *)
define_array_h(int_array, int)
define_array_h(char_array, char)
define_array_h(float_array, float)
define_array_h(double_array, double)
                                                                

#endif //GENERIC_ARRAY_GENERIC_ARRAY_H