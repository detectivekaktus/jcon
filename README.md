# jcon
jcon is a JSON serializer library that allows you to write the changes of your own to `.json` files.
The project is not maintained anymore. If you want to continue working on it (e.g. add deserialization), please consider forking the repository.

Here are the goals of the library as a checklist:
- [X] Create an install `.sh` script.
- [X] Support null type.
- [X] Support integer types.
- [X] Support float types.
- [X] Support string types.
- [X] Support boolean types.
- [X] Support array types.
- [X] Support object types.
- [ ] Deserialize `.json` files into the memory.
- [X] Serialize `.json` files to the disk.

## Examples
### Serialization
```c
#include "src/jcon.h"

int main(void)
{
  Jcon_Serializer *s = jcon_begin("example.json");
    jcon_add_key(s, "null");
    jcon_null(s);
    jcon_add_key(s, "boolean");
    jcon_bool(s, true);
    jcon_add_key(s, "integer");
    jcon_int(s, 69);
    jcon_add_key(s, "float");
    jcon_float(s, 3.14f, 2);
    jcon_add_key(s, "string");
    jcon_cstr(s, "hello world");
    jcon_add_key(s, "array");
    jcon_arr_begin(s);
      jcon_int(s, 69);
      jcon_int(s, 420);
      jcon_int(s, 69420);
    jcon_arr_end(s);
    jcon_add_key(s, "object");
    jcon_obj_begin(s);
      jcon_add_key(s, "inner-double");
      jcon_double(s, 3.1415, 4);
      jcon_add_key(s, "greeting");
      jcon_cstr(s, "hi, i'm binary");
    jcon_obj_end(s);
  jcon_end(s);
  return 0;
}
```

```json
{
  "null": null,
  "boolean": true,
  "integer": 69,
  "float": 3.14,
  "string": "hello world",
  "array": [
    69,
    420,
    69420
  ],
  "object": {
    "inner-double": 3.1415,
    "greeting": "hi, i'm binary"
  }
}
```

## Compilation
The library is available in two different versions: static and dynamic.

To compile the library from source, you need to have *GNU Make* tool installed on your computer, as well as a C compiler that supports C99 standard.

The project relies on my own header-only library `c-extended`. You don't need to install anything.

**Dynamic library**
```console
make
```

**Static library**
```console
make static
```

To install the library, run the `install.sh` script with the root privilege.

If `ldd` shows that the reference to the library is not found, you need to update your `LD_LIBRARY_PATH` environment variable.

## Contrubution
To help the project, you can contribute to it after reading the [CONTRIBUTING.md](https://github.com/detectivekaktus/jcon/blob/main/CONTRIBUTING.md) file in the root directory of the repository.
