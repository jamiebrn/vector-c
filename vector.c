#include "vector.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

vector vector_create_impl(uint64_t element_size) {
    vector vector;
    vector.data = malloc(element_size * VECTOR_DEFAULT_SIZE);
    vector.element_size = element_size;
    vector.size = 0;
    vector.capacity = VECTOR_DEFAULT_SIZE;
    return vector;
}

void vector_push_back_amount(vector* vector, void* item, uint64_t amount) {
    if (vector->size + amount >= vector->capacity) {
        vector_change_capacity(vector, (vector->size + amount) * 2);
    }

    memcpy((char*)vector->data + vector->size * vector->element_size, item, vector->element_size * amount);
    vector->size += amount;
}

void vector_resize(vector* vector, uint64_t size) {
    if (size <= vector->size) {
        return;
    }
    
    vector_change_capacity(vector, size);

    // Zero remaining memory
    void* size_top = ((char*)vector->data + vector->element_size * vector->size);
    void* capacity_top = ((char*)vector->data + vector->element_size * vector->capacity);
    memset(size_top, 0, (char*)capacity_top - (char*)size_top);

    vector->size = vector->capacity;
}

void vector_reserve(vector* vector, uint64_t capacity) {
    if (vector->capacity >= capacity) {
        return;
    }
    
    vector_change_capacity(vector, capacity);
}

void vector_change_capacity(vector* vector, uint64_t capacity) {
    void* old_data = vector->data;
    vector->capacity = capacity;
    vector->data = malloc(vector->element_size * vector->capacity);
    memcpy(vector->data, old_data, vector->element_size * vector->size);
    free(old_data);
}

void vector_pop_back(vector* vector) {
    if (vector->size <= 0) {
        return;
    }
    
    vector->size--;
    memset((char*)vector->data + vector->size * vector->element_size, 0, vector->element_size);
}

void vector_erase_index(vector* vector, uint64_t index) {
    if (index >= vector->size) {
        return;
    }
    
    char* move_ptr = (char*)vector->data + index * vector->element_size;
    memmove(move_ptr, move_ptr + vector->element_size, (vector->size - 1 - index) * vector->element_size);
    vector->size--;
}

void vector_clear(vector* vector) {
    vector->size = 0;
    memset((char*)vector->data, 0, vector->element_size * vector->capacity);
}

void vector_destroy(vector* vector) {
    free(vector->data);
    vector->element_size = 0;
    vector->size = 0;
    vector->capacity = 0;
}

void* vector_get(vector* vector, uint64_t index) {
    assert(index < vector->size);
    return ((char*)vector->data + vector->element_size * index);
}

void vector_set(vector* vector, uint64_t index, void* item) {
    assert(index < vector->size);
    memcpy((char*)vector->data + vector->element_size * index, item, vector->element_size);
}

vector_iter vector_iter_begin(vector* vector) {
    vector_iter iter;
    iter.vector_iterating = vector;
    iter.index = 0;
    return iter;
}

vector_iter vector_iter_end(vector* vector) {
    vector_iter iter;
    iter.vector_iterating = vector;
    iter.index = vector->size - 1;
    return iter;
}

bool vector_iter_is_positive(vector_iter iter) {
    return iter.index >= 0;
}

bool vector_iter_is_at_end(vector_iter iter) {
    return iter.index >= (int)iter.vector_iterating->size;
}

void vector_iter_inc(vector_iter* iter) {
    iter->index++;
}

void vector_iter_dec(vector_iter* iter) {
    iter->index--;
}

void* vector_iter_get(vector_iter iter) {
    return vector_get(iter.vector_iterating, iter.index);
}

char* vector_serialise(const vector* vector, uint64_t* data_size) {
    *data_size = sizeof(uint64_t) * 2 + vector->size * vector->element_size;

    char* data = malloc(*data_size);
    char* head = data;

    memcpy(head, &vector->size, sizeof(uint64_t));
    head += sizeof(uint64_t);
    memcpy(head, &vector->element_size, sizeof(uint64_t));
    head += sizeof(uint64_t);

    memcpy(head, vector->data, vector->size * vector->element_size);

    return data;
}

vector vector_deserialise(const char* data, uint64_t data_size) {
    uint64_t size;
    uint64_t element_size;

    memcpy(&size, data, sizeof(uint64_t));
    memcpy(&element_size, data + sizeof(uint64_t), sizeof(uint64_t));
    
    vector vec = vector_create_impl(element_size);

    vector_resize(&vec, size);

    memcpy(vec.data, data + sizeof(uint64_t) * 2, size * element_size);

    return vec;
}