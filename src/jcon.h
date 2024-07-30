#ifndef JCON_IMPLEMENTATION
#define JCON_IMPLEMENTATION

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define JCON_WRITE_MODE  0
#define JCON_READ_MODE   1

typedef enum {
  JCON_OBJ,
  JCON_KEY,
  JCON_ARR
} Jcon_Scope;

typedef enum {
  WAITING_FOR_KEY,
  WAITING_FOR_VALUE
} Jcon_State;

typedef struct {
  FILE *f;
  Jcon_Scope scope;
  Jcon_State state;
  size_t size;
  size_t arr_size;
  size_t indent;
} Jcon_Serializer;

#define jcon_indent(f, ind) for (size_t i = 0; i < (ind); i++) fputc(' ', f);

Jcon_Serializer *jcon_begin(const char *filename, uint8_t mode);
void jcon_end(Jcon_Serializer *s);
void jcon_add_key(Jcon_Serializer *s, const char *key);
void jcon_null(Jcon_Serializer *s);
void jcon_int(Jcon_Serializer *s, int64_t val);
void jcon_float(Jcon_Serializer *s, float val, int precision);
void jcon_double(Jcon_Serializer *s, double val, int precision);
void jcon_cstr(Jcon_Serializer *s, const char *cstr);
void jcon_arr_begin(Jcon_Serializer *s);
void jcon_arr_end(Jcon_Serializer *s);

#endif
