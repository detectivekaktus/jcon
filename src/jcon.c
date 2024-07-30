#include "jcon.h"

Jcon_Serializer *jcon_begin(const char *filename)
{
  Jcon_Serializer *s = malloc(sizeof(Jcon_Serializer));
  s->scope = JCON_OBJ;
  s->state = WAITING_FOR_KEY;
  s->size = 0;
  s->arr_size = 0;
  s->indent = 2;
  s->f = fopen(filename, "w");
  fprintf(s->f, "{\n");
  return s;
}

void jcon_end(Jcon_Serializer *s)
{
  fprintf(s->f, "\n}\n");
  fclose(s->f);
  free(s);
  s = NULL;
}

// TODO: Check for already existing keys.
void jcon_add_key(Jcon_Serializer *s, const char *key)
{
  if (s->state != WAITING_FOR_KEY && s->scope != JCON_OBJ) assert(0 && "Invalid JSON syntax. Expected value.");
  if (s->size++ > 0) fprintf(s->f, ",\n");
  jcon_indent(s->f, s->indent);
  fprintf(s->f, "\"%s\": ", key);
  s->scope = JCON_KEY;
  s->state = WAITING_FOR_VALUE;
}

void jcon_null(Jcon_Serializer *s)
{
  if (s->state != WAITING_FOR_VALUE && s->scope == JCON_OBJ) assert(0 && "Invalid JSON syntax. Expected key.");
  if (s->scope == JCON_ARR) {
    if (s->arr_size++ > 0) fprintf(s->f, ",\n");
    jcon_indent(s->f, s->indent);
  }
  fprintf(s->f, "null");
  s->scope = s->scope == JCON_ARR ? JCON_ARR : JCON_OBJ;
  s->state = WAITING_FOR_KEY;
}

void jcon_int(Jcon_Serializer *s, int64_t val)
{
  if (s->state != WAITING_FOR_VALUE && s->scope == JCON_OBJ) assert(0 && "Invalid JSON syntax. Expected key.");
  if (s->scope == JCON_ARR) {
    if (s->arr_size++ > 0) fprintf(s->f, ",\n");
    jcon_indent(s->f, s->indent);
  }
  fprintf(s->f, "%ld", val);
  s->scope = s->scope == JCON_ARR ? JCON_ARR : JCON_OBJ;
  s->state = WAITING_FOR_KEY;
}

void jcon_float(Jcon_Serializer *s, float val, int precision)
{
  if (s->state != WAITING_FOR_VALUE && s->scope == JCON_OBJ) assert(0 && "Invalid JSON syntax. Expected key.");
  if (s->scope == JCON_ARR) {
    if (s->arr_size++ > 0) fprintf(s->f, ",\n");
    jcon_indent(s->f, s->indent);
  }
  fprintf(s->f, "%.*f", precision, val);
  s->scope = s->scope == JCON_ARR ? JCON_ARR : JCON_OBJ;
  s->state = WAITING_FOR_KEY;
}

void jcon_double(Jcon_Serializer *s, double val, int precision)
{
  if (s->state != WAITING_FOR_VALUE && s->scope == JCON_OBJ) assert(0 && "Invalid JSON syntax. Expected key.");
  if (s->scope == JCON_ARR) {
    if (s->arr_size++ > 0) fprintf(s->f, ",\n");
    jcon_indent(s->f, s->indent);
  }
  fprintf(s->f, "%.*F", precision, val);
  s->scope = s->scope == JCON_ARR ? JCON_ARR : JCON_OBJ;
  s->state = WAITING_FOR_KEY;
}

void jcon_cstr(Jcon_Serializer *s, const char *cstr)
{
  if (s->state != WAITING_FOR_VALUE && s->scope == JCON_OBJ) assert(0 && "Invalid JSON syntax. Expected key.");
  if (s->scope == JCON_ARR) {
    if (s->arr_size++ > 0) fprintf(s->f, ",\n");
    jcon_indent(s->f, s->indent);
  }
  fprintf(s->f, "\"%s\"", cstr);
  s->scope = s->scope == JCON_ARR ? JCON_ARR : JCON_OBJ;
  s->state = WAITING_FOR_KEY;
}

void jcon_arr_begin(Jcon_Serializer *s)
{
  if (s->state != WAITING_FOR_VALUE && s->scope == JCON_OBJ) assert(0 && "Invalid JSON syntax. Expected key.");
  fprintf(s->f, "[\n");
  s->indent += 2;
  s->scope = JCON_ARR;
  s->state = WAITING_FOR_VALUE;
}

void jcon_arr_end(Jcon_Serializer *s)
{
  if (s->state != WAITING_FOR_VALUE && s->scope != JCON_ARR) assert(0 && "Invalid JSON syntax. Can't end an array.");
  fprintf(s->f, "\n");
  s->indent -= 2;
  jcon_indent(s->f, s->indent);
  fprintf(s->f, "]");
  s->scope = JCON_OBJ;
  s->state = WAITING_FOR_KEY;
  s->arr_size = 0;
}
