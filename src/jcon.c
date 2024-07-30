#include "jcon.h"

Jcon_Serializer *jcon_begin(const char *filename, uint8_t mode)
{
  Jcon_Serializer *s = malloc(sizeof(Jcon_Serializer));
  s->scope = JCON_OBJ;
  s->state = WAITING_FOR_KEY;
  s->size = 0;
  s->indent = 2;
  switch (mode) {
    case JCON_WRITE_MODE: {
      s->f = fopen(filename, "w");
      fprintf(s->f, "{\n");
    } break;
    case JCON_APPEND_MODE: {
      s->f = fopen(filename, "a");
    } break;
    case JCON_READ_MODE: {
      assert(0 && "not implemented");
    } break;
    default: {
      assert(0 && "unreachable");
    } break;
  }
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
  fprintf(s->f, "null");
  s->scope = JCON_OBJ;
  s->state = WAITING_FOR_KEY;
}

void jcon_int(Jcon_Serializer *s, int64_t val)
{
  if (s->state != WAITING_FOR_VALUE && s->scope == JCON_OBJ) assert(0 && "Invalid JSON syntax. Expected key.");
  fprintf(s->f, "%ld", val);
  s->scope = JCON_OBJ;
  s->state = WAITING_FOR_KEY;
}

void jcon_float(Jcon_Serializer *s, float val, int precision)
{
  if (s->state != WAITING_FOR_VALUE && s->scope == JCON_OBJ) assert(0 && "Invalid JSON syntax. Expected key.");
  fprintf(s->f, "%.*f", precision, val);
  s->scope = JCON_OBJ;
  s->state = WAITING_FOR_KEY;
}

void jcon_double(Jcon_Serializer *s, double val, int precision)
{
  if (s->state != WAITING_FOR_VALUE && s->scope == JCON_OBJ) assert(0 && "Invalid JSON syntax. Expected key.");
  fprintf(s->f, "%.*F", precision, val);
  s->scope = JCON_OBJ;
  s->state = WAITING_FOR_KEY;
}
