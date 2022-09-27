#pragma once

#include "strings.h"

typedef struct stream_opaque *stream_t;

/**
 * @func stream_open
 *
 * @param stream   [stream_t*]   - an uninitialized stream_t object
 * @param filename [const char*] - stream filename
 *
 * @returns -1 on failure, 0 on success.
 *
 * Initializes a new stream_t object with file named @filename.
 **/
int stream_open(stream_t *stream, const char *filename);

/**
 * @func stream_close
 *
 * @param stream [stream_t] - an initialized stream_t object
 *
 * Closes an initialized stream_t object.
 **/
int stream_close(stream_t stream);

/**
 * @func stream_getc
 *
 * @param stream [stream_t] - an initialized stream_t object
 *
 * @returns -1 on failure, otherwise returns the char code
 * read from stream.
 *
 * Reads the next char code from stream, and increments stream pointer.
 **/
int stream_getc(stream_t stream);

/**
 * @func stream_peek
 *
 * @param stream [stream_t] - an initialized stream_t object
 *
 * @returns -1 on failure, otherwise returns the char code
 * read from stream.
 *
 * Reads the next char code from stream, but does not increment
 * stream pointer.
 **/
int stream_peek(stream_t stream);

/**
 * @func stream_read_until
 *
 * @param stream [stream_t] - an initialized stream_t object
 * @param s      [string_t] - an initialized string_t object
 * @param delim  [int]      - char code delimiter
 *
 * @returns -1 if failure (if @delim < 0 or if @delim is not reached
 * before the end of the stream.
 *
 * Reads all chars from stream up to and not including the delimiter
 * @delim, if it is found. The stream pointer is incremented to the
 * char right after the delimiter. If @s is not NULL, then the chars
 * read will be appended onto @s.
 **/
int stream_read_until(stream_t stream, string_t s, int delim);
