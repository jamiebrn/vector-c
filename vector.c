#include "vector.h"

vector vector_create(unsigned int element_size)
{
    vector vector;
    vector.data = malloc(element_size * VECTOR_DEFAULT_SIZE);
    vector.element_size = element_size;
    vector.size = 0;
    vector.capacity = VECTOR_DEFAULT_SIZE;
    return vector;
}

void vector_push_back(vector* vector, void* item)
{
    if (vector->size >= vector->capacity)
    {
        void* old_data = vector->data;
        vector->capacity *= 2;
        vector->data = malloc(vector->element_size * vector->capacity);
        memcpy(vector->data, old_data, vector->element_size * vector->size);
        free(old_data);
    }

    memcpy((char*)vector->data + vector->size * vector->element_size, item, vector->element_size);
    vector->size++;
}

void vector_pop_back(vector* vector)
{
    if (vector->size <= 0) return;
    vector->size--;
    memset((char*)vector->data + vector->size * vector->element_size, 0, vector->element_size);
}

void vector_clear(vector* vector)
{
    vector->size = 0;
    memset((char*)vector->data, 0, vector->element_size * vector->capacity);
}

void vector_destroy(vector* vector)
{
    free(vector->data);
    vector->element_size = 0;
    vector->size = 0;
    vector->capacity = 0;
}

void* vector_get(vector* vector, unsigned int index)
{
    assert(index < vector->size);
    return ((char*)vector->data + vector->element_size * index);
}

void vector_set(vector* vector, unsigned int index, void* item)
{
    assert(index < vector->size);
    memcpy((char*)vector->data + vector->element_size * index, item, vector->element_size);
}

vector_iter vector_iter_begin(vector* vector)
{
    vector_iter iter;
    iter.vector_iterating = vector;
    iter.index = 0;
    return iter;
}

vector_iter vector_iter_end(vector* vector)
{
    vector_iter iter;
    iter.vector_iterating = vector;
    iter.index = vector->size - 1;
    return iter;
}

bool vector_iter_is_positive(vector_iter iter)
{
    return iter.index >= 0;
}

bool vector_iter_is_at_end(vector_iter iter)
{
    return iter.index >= iter.vector_iterating->size;
}

void vector_iter_inc(vector_iter* iter)
{
    iter->index++;
}

void vector_iter_dec(vector_iter* iter)
{
    iter->index--;
}

void* vector_iter_get(vector_iter iter)
{
    return vector_get(iter.vector_iterating, iter.index);
}