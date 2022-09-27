#include "strings.h"
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

struct string_opaque
{
    char *s;
    long l, m;
};

static uint32_t u32up(uint32_t x)
{
    --x;
    for (int i = 1; i != 16; i *= 2)
        x |= x>>i;
    return ++x;
}

int string_init(string_t *s, long capacity)
{
    *s = malloc(sizeof(struct string_opaque));

    (*s)->l = 0;
    (*s)->m = u32up(++capacity);
    (*s)->s = malloc((*s)->m);

    return (!(*s)->s)? -1 : 0;
}

int string_free(string_t s)
{
    s->l = s->m = 0;
    free(s->s);
    free(s);
    return 0;
}

int string_clear(string_t s)
{
    if (s->l) s->l = 0, *(s->s) = 0;
    return 0;
}

int string_reserve(string_t s, long capacity)
{
    capacity = u32up(++capacity);

    if (capacity <= s->m)
        return 0;

    s->m = capacity;
    s->s = realloc(s->s, s->m);

    if (!s->s) return -1;
    return 0;
}

char* string_release(string_t s)
{
    if (!s) return NULL;

    if (s->m > s->l + 1)
        s->s = realloc(s->s, s->l + 1);

    char *cstr = s->s;

    s->l = s->m = 0, s->s = NULL;
    free(s);
    return cstr;
}

int string_putsn(string_t s, long n, const char *str)
{
    if (!n || !str) return -1;
    if (!*str) return (n > 0) ? -1 : 0;

    if (string_reserve(s, s->l + n + 2) < 0)
        return -1;

    memcpy(s->s + s->l, str, n);

    s->l += n;
    s->s[s->l] = 0;

    return 0;
}

int string_puts(string_t s, const char *str)
{
    if (!str) return -1;
    return string_putsn(s, strlen(str), str);
}

int string_putc(string_t s, int c)
{
    if (c < 0) return -1;
    if (string_reserve(s, s->l + 2) < 0) return -1;

    s->s[s->l++] = c;
    s->s[s->l] = 0;

    return 0;
}

long string_size(string_t s)
{
    return s->l;
}

char* string_cstr(string_t s)
{
    return s->s;
}
