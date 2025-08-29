#pragma once

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>

#ifndef VECTOR_DEFAULT_SIZE
#define VECTOR_DEFAULT_SIZE 10
#endif

#define vector_create(T) vector_create_impl(sizeof(T))
#define vector_push_back(vec_ptr, item_ptr) vector_push_back_amount(vec_ptr, item_ptr, 1)
#define vector_get_value(T, vec_ptr, index) *(T*)vector_get(vec_ptr, index)

typedef struct vector
{
    void* data;
    unsigned int element_size;
    unsigned int size;
    unsigned int capacity;
} vector;

vector vector_create_impl(unsigned int element_size);

void vector_push_back_amount(vector* vector, void* item, unsigned int amount);

// New memory will be zeroed
void vector_resize(vector* vector, unsigned int size);

void vector_reserve(vector* vector, unsigned int capacity);

void vector_change_capacity(vector* vector, unsigned int capacity);

void vector_pop_back(vector* vector);

void vector_erase_index(vector* vector, unsigned int index);

void vector_clear(vector* vector);

void vector_destroy(vector* vector);

void* vector_get(vector* vector, unsigned int index);

void vector_set(vector* vector, unsigned int index, void* item);

typedef struct vector_iter
{
    vector* vector_iterating;
    int index;
} vector_iter;

vector_iter vector_iter_begin(vector* vector);

vector_iter vector_iter_end(vector* vector);

bool vector_iter_is_positive(vector_iter iter);

bool vector_iter_is_at_end(vector_iter iter);

void vector_iter_inc(vector_iter* iter);

void vector_iter_dec(vector_iter* iter);

void* vector_iter_get(vector_iter iter);

// Serialisation
char* vector_serialise(const vector* vector, unsigned int* data_size);

vector vector_deserialise(const char* data, unsigned int data_size);