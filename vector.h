#pragma once

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#ifndef VECTOR_DEFAULT_SIZE
#define VECTOR_DEFAULT_SIZE 10
#endif

typedef struct vector
{
    void* data;
    unsigned int element_size;
    unsigned int size;
    unsigned int capacity;
} vector;

vector vector_create(unsigned int element_size);

void vector_push_back(vector* vector, void* item);

void vector_pop_back(vector* vector);

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