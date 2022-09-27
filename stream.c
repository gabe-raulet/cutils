#include "stream.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

struct stream_opaque
{
    char *buf;
    int fd, start, end, is_eof;
};

#define BUFLEN (16384)

int stream_open(stream_t *stream, const char *filename)
{
    int fd;

    if ((fd = open(filename, O_RDONLY)) < 0)
        return -1;

    *stream = malloc(sizeof(struct stream_opaque));

    (*stream)->fd = fd;
    (*stream)->start = (*stream)->end = (*stream)->is_eof = 0;
    (*stream)->buf = malloc(BUFLEN);

    if (!(*stream)->buf)
    {
        free(*stream);
        return -1;
    }

    return 0;
}

int stream_close(stream_t stream)
{
    close(stream->fd);
    free(stream->buf);
    free(stream);
    return 0;
}

int stream_getc(stream_t stream)
{
    if (stream->is_eof) return -1;

    if (stream->start >= stream->end)
    {
        stream->start = 0;
        stream->end = read(stream->fd, stream->buf, BUFLEN);
        if (stream->end < 0) { stream->is_eof = -1; return -1; }
        if (!stream->end) { stream->is_eof = 1; return -1; }

    }

    return stream->buf[stream->start++];
}

int stream_peek(stream_t stream)
{
    int c = stream_getc(stream);
    stream->start--;
    return c;
}

int stream_read_until(stream_t stream, string_t s, int delim)
{
    if (delim < 0) return -1;

    int c;
    while(((c = stream_getc(stream)) >= 0) && c != delim)
        if (s) string_putc(s, c);

    return (c != delim)? -1 : c;
}
