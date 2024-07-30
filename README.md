# jcon
jcon is a JSON serializer library that allows you to load JSON objects from `.json` files and write the changes of your own to `.json` files.

Here are the goals of the library as a checklist:
- [ ] Create an install `.sh` script.
- [X] Support null type.
- [X] Support integer types.
- [X] Support float types.
- [X] Support string types.
- [X] Support array types.
- [ ] Deserialize `.json` files into the memory.
- [X] Serialize `.json` files to the disk.

## Examples
### Serialization
```c
#include <jcon.h>

int main(void) {
    Jcon_Serializer *s = jcon_begin("example.json");
        jcon_add_key(s, "null");
        jcon_null(s);
        jcon_add_key(s, "hello");
        jcon_cstr(s, "world");
        jcon_add_key(s, "array");
        jcon_arr_begin(s);
            jcon_int(s, 69);
            jcon_int(s, 420);
        jcon_arr_end(s);
    jcon_end(s);
}
```

```json
{
    "null": null,
    "hello": "world",
    "array": [
        69,
        420
    ]
}
```

## Compilation
The library is available in two different versions: static and dynamic.

To compile the library from source, you need to have *GNU Make* tool installed on your computer, as well as a C compiler that supports C99 standard.

**Dynamic library**
```console
make
```

**Static library**
```console
make static
```

## Contrubution
To help the project, you can contribute to it after reading the [CONTRIBUTING.md](https://github.com/detectivekaktus/jcon/blob/main/CONTRIBUTING.md) file in the root directory of the repository.
