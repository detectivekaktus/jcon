# jcon
***WARNING! THIS LIBRARY IS A WORK-IN-PROGRESS. DON'T EXPECT IT TO BE FUNCTIONAL AT THIS POINT!***

jcon is a JSON serializer library that allows you to load JSON objects from `.json` files and write the changes of your own to `.json` files.

Here are the goals of the library as a checklist:
- [ ] Create an install `.sh` script.
- [X] Support null type.
- [ ] Support integer types.
- [ ] Support float types.
- [ ] Support string types.
- [ ] Load `.json` files into the memory.
- [X] Write `.json` files to the disk.

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
