#pragma once

typedef struct string_opaque *string_t;

/**
 * @func string_init
 *
 * @param s        [string_t*] - an uninitialized string_t object
 * @param capacity [long]      - starting capacity
 *
 * @returns -1 on failure, 0 on success
 *
 * Initializes a new string_t object with memory allocated
 * for at least @capacity chars.
 **/
int string_init(string_t *s, long capacity);

/**
 * @func string_free
 *
 * @param s [string_t] - an initialized string_t object
 *
 * Frees all the memory associated with a string_t object.
 **/
int string_free(string_t s);

/**
 * @func string_clear
 *
 * @param s [string_t] - an initialized string_t object
 *
 * Replaces string with the empty string, but keeps the same
 * memory capacity as before.
 **/
int string_clear(string_t s);

/**
 * @func string_reserve
 *
 * @param s        [string_t] - an initialized string_t object
 * @param capacity [long]     - new string capacity
 *
 * @returns -1 if memory allocation error, 0 on success.
 *
 * Reserves new additional memory for up to @capacity chars,
 * assuming that @capacity is larger than the previous capacity.
 **/
int string_reserve(string_t s, long capacity);

/**
 * @func string_release
 *
 * @param s [string_t] - an initialized string_t object
 *
 * @returns released char buffer
 *
 * Frees unused extra memory from char buffer, and then releases
 * ownership of char buffer to the user. The string_t object is
 * destroyed.
 **/
char* string_release(string_t s);

/**
 * @func string_putsn
 *
 * @param s   [string_t]    - an initialized string_t object
 * @param n   [long]        - number of chars to put
 * @param str [const char*] - pointer to char buffer to read from
 *
 * @returns -1 on failure, 0 on success
 *
 * Appends @n chars read from @str onto the end of string_t char
 * buffer. Allocates more memory to string_t buffer if necessary
 * to append full string.
 **/
int string_putsn(string_t s, long n, const char *str);

/**
 * @func string_puts
 *
 * @param s   [string_t]    - an initialized string_t object
 * @param str [const char*] - pointer to char buffer to read from
 *
 * @returns -1 on failure, 0 on success
 *
 * Appends @str onto the end of string_t char buffer. Allocates more
 * memory to string_t buffer if necessary to append full string.
 * Full string is determined as usual by null-terminal on @str.
 **/
int string_puts(string_t s, const char *str);

/**
 * @func string_putc
 *
 * @param s [string_t] - an initialized string_t object
 * @param c [int]      - a char code
 *
 * @returns -1 on failure, 0 on success
 *
 * Appends the char @c onto the end of string_t object. Allocates
 * more memory to string_t buffer if necessary to append @c plus
 * the null-terminal after.
 **/
int string_putc(string_t s, int c);

/**
 * @func string_size
 *
 * @param s [string_t] - an initialized string_t object
 *
 * @returns length of string_t string.
 **/
long string_size(string_t s);

/**
 * @func string_cstr
 *
 * @param s [string_t] - an initialized string_t object
 *
 * @returns the char buffer of string_t object.
 **/
char* string_cstr(string_t s);
