#pragma once

typedef struct store_opaque *store_t;

/**
 * @func store_read
 *
 * @param store    [store_t*]    - an unitialized store_t object
 * @param filename [const char*] - fasta filename
 *
 * Initializes a store_t object with the read sequences contained in
 * the fasta file.
 **/
int store_read(store_t *store, const char *filename);

/**
 * @func store_free
 *
 * @param store [store_t] - an initialized store_t object
 *
 * Frees all the memory associated with @store.
 **/
int store_free(store_t store);

/**
 * @func store_get_seq
 *
 * @param store [const store_t] - an initialized store_t object
 * @param id    [long]          - sequence index
 *
 * Returns the sequence in @store with index @id.
 **/
char* store_get_seq(const store_t store, long id);

/**
 * @func store_get_name
 *
 * @param store [const store_t] - an initialized store_t object
 * @param id    [long]          - sequence index
 *
 * Returns the name of the sequence in @store with index @id.
 **/
char* store_get_name(const store_t store, long id);

/**
 * @func store_get_seqlen
 *
 * @param store [const store_t] - an initialized store_t object
 * @param id    [long]          - sequence index
 *
 * Returns the length of the sequence in @store with index @id.
 **/
int store_get_seqlen(const store_t store, long id);

/**
 * @func store_size
 *
 * @param store [const store_t store] - an initialized store_t object
 *
 * Returns the number of sequences stored in @store.
 **/
long store_size(const store_t store);

/**
 * @func store_stats
 *
 * @param store           [const store_t store] - an initialized store_t object
 * @param numreads        [long*]               - pointer to where number of reads is written
 * @param min_read_length [long*]               - pointer to where minimum read size is written
 * @param max_read_length [long*]               - pointer to where maximum read size is written
 * @param avg_read_length [double*]             - pointer to where avg_read_length is written
 *
 * Returns the associated statistic to each passed pointer parameter that is not NULL.
 **/
void store_stats(const store_t store, long *numreads, long *min_read_length, long *max_read_length, double *avg_read_length);
