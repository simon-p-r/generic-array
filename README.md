# generic-array

Project heavily inspired by GenericMap as found here https://github.com/mystborn/GenericMap

This project contains a pair of macros that will generate a strongly typed dynamic array type. To add this to your project you can just copy the `generic_arrah` files from the source folder, or add the whole source folder somewhere in your source tree.

## Defining a Type

In a header file, use the macro `arrah_define_h` to generate the type and function definitions. It has the following arguments:

| Argument | Description |
| --- | --- |
| typeName | The name of the generated type. This will also prefix all of the function names. |
| valueType | The type of the map elements. |

In the corresponding source file, use the macro `array_define_c` to generate the function implementations.

| Argument | Description |
| --- | --- |
| typeName | The name of the generated type. This will also prefix all of the function names. |
| valueType | The type of the map elements. |
| compareFn | Currently unused param. |
| defaultValue | The value to return when you try to access a key that doesn't exist. |

The first 2 arguments of `array_define_c` *MUST* be the same as those used in `array_define_h`.

```c
// array.h
#include "generic_array.h"

// The name uint8_array means an array of uint8_t.
define_array_h(uint8_array, uint8_t)



// array.c
#include <string.h>

#include "array.h"

define_array_c(uint8_array, uint8_t, NULL, 0)
```

That's all you need to define the arrays.

## Functions

The macros define the following functions to use the maps.

| Function | Description | Return |
| --- | --- | --- |
| \<typeName>_new(void *user) | Initializes the data needed for the map. Returns the result of `calloc` used to initialize the data buffer.  Pass user defined void pointer to func for use with iterator foreach callback | pointer to array_struct_type  |
| \<typeName>_free(\<typeName>\ *array) | Frees the data used by the array plus the array is freed and set to NULL. | void |
| \<typeName>_push(\<typeName>\ *array, \<valueType> value) | Pushes value onto end of array.| void |
| \<typeName>_pop(\<typeName>\ *array | Pops value from end of array, function returns value.| <valueType> |
| \<typeName>_set(\<typeName>\ *array, \size_t index, \<valueType> value) | Sets the value at index of array. Overwrites the previous value. | void |
| \<typeName>_get(\<typeName>\ *array, \size_t index) | Gets the value associated with the specified index. Returns `defaultValue` if the key isn't found. | \<valueType> |
| \<typeName>_foreach(\<typeName>\ *array, \<typeName_iter_t> callback) | Iterates over array memembers. | void |

```c
#include <stdio.h>
#include "generic_array.h"


void iter_cb(void *user, char *entry, size_t index) {

}


int main() {

    char *user = "some info";

    string_array *array = string_array_new((void*)user);

    string_array_push(array, "hello");
    string_array_push(array, "from");
    string_array_push(array, "my");
    string_array_push(array, "generic");
    string_array_push(array, "string");
    string_array_push(array, "array");

    char *entry = NULL;
    string_array_foreach(array, &iter_cb);

    string_array_set(array, 6, "last");

    entry = string_array_get(array, 10);
    if(entry != NULL) {
        puts(entry);
    }
    
        
    entry = string_array_pop(array);
    puts(entry);

    string_array_set(array, 0, "hello");
    string_array_set(array, 1, "world");

    string_array_free(array);

};

```

<!-- ## Fields

The only useful field of the generated type is the `count` field, which can be used to get the number of elements added to the map.

```c
#include <stdio.h>
#include "map.h"

int main() {
    SSMap map;
    SSMapInit(&map);

    printf("%d\n", map.count);
    SSMapAdd(&map, "hello", "world");
    printf("%d\n", map.count);

    SSMapFree(&map);
}
``` -->