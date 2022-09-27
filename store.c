#include "store.h"
#include "array.h"
#include "strings.h"
#include "stream.h"
#include <string.h>
#include <limits.h>
#include <stdio.h>

struct store_opaque
{
    char *bufs[2];
    long *offsets[2];
    int *seqlens;
    long n;
};

#define MIN(a, b) ( ((a) < (b))? (a) : (b) )
#define MAX(a, b) ( ((a) > (b))? (a) : (b) )

void store_stats(const store_t store, long *numreads, long *min_read_length, long *max_read_length, double *avg_read_length)
{
    if (numreads) *numreads = store->n;

    long maxsize = 0;
    long minsize = LONG_MAX;
    long nts = 0;

    for (long i = 0; i < store->n; ++i)
    {
        nts += store->seqlens[i];
        minsize = MIN(minsize, store->seqlens[i]);
        maxsize = MAX(maxsize, store->seqlens[i]);
    }

    if (min_read_length) *min_read_length = minsize;
    if (max_read_length) *max_read_length = maxsize;
    if (avg_read_length) *avg_read_length = (nts + 0.0) / (store->n + 0.0);
}

int store_read(store_t *store, const char *filename)
{
    int c;
    long readlen;
    stream_t fasta_stream;
    string_t seq, name;
    array_t(long) seq_offsets, name_offsets;
    array_t(int) seqlens;

    if (stream_open(&fasta_stream, filename) < 0)
        return -1;

    array_init(seq_offsets);
    array_init(name_offsets);
    array_init(seqlens);
    string_init(&seq, 512);
    string_init(&name, 128);

    for (;;)
    {
        while ((c = stream_getc(fasta_stream)) >= 0 && c != '>');

        if (c < 0) break;

        *array_push(name_offsets) = string_size(name);

        if ((c = stream_read_until(fasta_stream, name, '\n')) < 0)
            break;

        string_putc(name, '\0');
        *array_push(seq_offsets) = string_size(seq);

        while (stream_read_until(fasta_stream, seq, '\n') != -1)
            if (stream_peek(fasta_stream) == '>')
                break;

        readlen = string_size(seq) - array_top(seq_offsets);
        *array_push(seqlens) = (int)readlen;

        string_putc(seq, '\0');
    }

    stream_close(fasta_stream);

    *store = malloc(sizeof(struct store_opaque));
    (*store)->n = array_size(seq_offsets);
    (*store)->bufs[0] = string_release(seq);
    (*store)->bufs[1] = string_release(name);
    (*store)->offsets[0] = array_release(seq_offsets);
    (*store)->offsets[1] = array_release(name_offsets);
    (*store)->seqlens = array_release(seqlens);

    return 0;
}

char *store_get_seq(const store_t store, long id)
{
    return store->bufs[0] + store->offsets[0][id];
}

char *store_get_name(const store_t store, long id)
{
    return store->bufs[1] + store->offsets[1][id];
}

int store_get_seqlen(const store_t store, long id)
{
    return store->seqlens[id];
}

long store_size(const store_t store)
{
    return store->n;
}

int store_free(store_t store)
{
    if (!store) return -1;

    store->n = 0;
    free(store->seqlens);
    free(store->bufs[0]);
    free(store->bufs[1]);
    free(store->offsets[0]);
    free(store->offsets[1]);
    free(store);

    return 0;
}
