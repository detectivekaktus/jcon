#define EXTEND_C
#include "jcon.h"

Jcon_Serializer *jcon_begin(const char *filename)
{
  Jcon_Serializer *s = malloc(sizeof(Jcon_Serializer));
  if (s == NULL) CRASH("buy more ram, lol");
  s->scopes = da_heap_alloc(Scopes);
  if (s->scopes == NULL) CRASH("buy more ram, lol");
  da_append(s->scopes, JCON_OBJ);
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
  da_heap_free(s->scopes);
  fclose(s->f);
  free(s);
  s = NULL;
}

// TODO: Check for already existing keys.
void jcon_add_key(Jcon_Serializer *s, const char *key)
{
  if (s->state != WAITING_FOR_KEY && s->scopes->items[s->scopes->size - 1] != JCON_OBJ)
    assert(0 && "Invalid JSON syntax. Expected value.");
  if (s->size++ > 0) fprintf(s->f, ",\n");
  jcon_indent(s->f, s->indent);
  fprintf(s->f, "\"%s\": ", key);
  da_append(s->scopes, JCON_KEY);
  s->state = WAITING_FOR_VALUE;
}

void jcon_null(Jcon_Serializer *s)
{
  if (s->state != WAITING_FOR_VALUE && s->scopes->items[s->scopes->size - 1] == JCON_OBJ)
    assert(0 && "Invalid JSON syntax. Expected key.");
  if (s->scopes->items[s->scopes->size - 1] == JCON_ARR) {
    if (s->arr_size++ > 0) fprintf(s->f, ",\n");
    jcon_indent(s->f, s->indent);
  }
  else s->scopes->size--;
  fprintf(s->f, "null");
  s->state = WAITING_FOR_KEY;
}

void jcon_int(Jcon_Serializer *s, int64_t val)
{
  if (s->state != WAITING_FOR_VALUE && s->scopes->items[s->scopes->size - 1] == JCON_OBJ)
    assert(0 && "Invalid JSON syntax. Expected key.");
  if (s->scopes->items[s->scopes->size - 1] == JCON_ARR) {
    if (s->arr_size++ > 0) fprintf(s->f, ",\n");
    jcon_indent(s->f, s->indent);
  }
  else s->scopes->size--;
  fprintf(s->f, "%ld", val);
  s->state = WAITING_FOR_KEY;
}

void jcon_bool(Jcon_Serializer *s, bool val)
{
  if (s->state != WAITING_FOR_VALUE && s->scopes->items[s->scopes->size - 1] == JCON_OBJ)
    assert(0 && "Invalid JSON syntax. Expected key.");
  if (s->scopes->items[s->scopes->size - 1] == JCON_ARR) {
    if (s->arr_size++ > 0) fprintf(s->f, ",\n");
    jcon_indent(s->f, s->indent);
  }
  else s->scopes->size--;
  fprintf(s->f, "%s", val ? "true" : "false");
  s->state = WAITING_FOR_KEY;
}

void jcon_float(Jcon_Serializer *s, float val, int precision)
{
  if (s->state != WAITING_FOR_VALUE && s->scopes->items[s->scopes->size - 1] == JCON_OBJ)
    assert(0 && "Invalid JSON syntax. Expected key.");
  if (s->scopes->items[s->scopes->size - 1] == JCON_ARR) {
    if (s->arr_size++ > 0) fprintf(s->f, ",\n");
    jcon_indent(s->f, s->indent);
  }
  else s->scopes->size--;
  fprintf(s->f, "%.*f", precision, val);
  s->state = WAITING_FOR_KEY;
}

void jcon_double(Jcon_Serializer *s, double val, int precision)
{
  if (s->state != WAITING_FOR_VALUE && s->scopes->items[s->scopes->size - 1] == JCON_OBJ)
    assert(0 && "Invalid JSON syntax. Expected key.");
  if (s->scopes->items[s->scopes->size - 1] == JCON_ARR) {
    if (s->arr_size++ > 0) fprintf(s->f, ",\n");
    jcon_indent(s->f, s->indent);
  }
  else s->scopes->size--;
  fprintf(s->f, "%.*F", precision, val);
  s->state = WAITING_FOR_KEY;
}

void jcon_cstr(Jcon_Serializer *s, const char *cstr)
{
  if (s->state != WAITING_FOR_VALUE && s->scopes->items[s->scopes->size - 1] == JCON_OBJ)
    assert(0 && "Invalid JSON syntax. Expected key.");
  if (s->scopes->items[s->scopes->size - 1] == JCON_ARR) {
    if (s->arr_size++ > 0) fprintf(s->f, ",\n");
    jcon_indent(s->f, s->indent);
  }
  else s->scopes->size--;
  fprintf(s->f, "\"%s\"", cstr);
  s->state = WAITING_FOR_KEY;
}

void jcon_arr_begin(Jcon_Serializer *s)
{
  if (s->state != WAITING_FOR_VALUE && s->scopes->items[s->scopes->size - 1] == JCON_OBJ)
    assert(0 && "Invalid JSON syntax. Expected key.");
  if (s->scopes->items[s->scopes->size - 1] == JCON_ARR) {
    if (s->arr_size++ > 0) fprintf(s->f, ",\n");
    jcon_indent(s->f, s->indent);
  }
  fprintf(s->f, "[\n");
  da_append(s->scopes, JCON_ARR);
  s->indent += 2;
  s->state = WAITING_FOR_VALUE;
  s->arr_size = 0;
}

void jcon_arr_end(Jcon_Serializer *s)
{
  if (s->state != WAITING_FOR_VALUE && s->scopes->items[s->scopes->size - 1] != JCON_ARR)
    assert(0 && "Invalid JSON syntax. Can't end an array.");
  fprintf(s->f, "\n");
  s->indent -= 2;
  jcon_indent(s->f, s->indent);
  fprintf(s->f, "]");
  s->scopes->size--;
  s->state = WAITING_FOR_KEY;
}
