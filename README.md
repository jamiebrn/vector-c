# vector-c
Small vector/dynamic array "library" in C, similar to C++ vectors

Add .h and .c file to project to use

Usage:
```c
// Create vector of floats
vector numbers = vector_create(float);

// Add some preallocated floats
vector_push_back(&numbers, &float_one);
vector_push_back(&numbers, &float_two);
vector_push_back(&numbers, &float_three);

// Iterate using iterator
for (vector_iter iter = vector_iter_begin(&numbers); !vector_iter_is_at_end(iter); vector_iter_inc(&iter))
{
    // Get value and cast to float
    float value = *(float*)vector_iter_get(iter);
    printf("%f\n", value);
}
```

Default vector preallocated size can be changed, e.g. to 30:
```c
#define VECTOR_DEFAULT_SIZE 30
#include <vector.h>
...
```
