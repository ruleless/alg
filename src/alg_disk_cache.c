#include "alg_disk_cache.h"

int
alg_disk_cache_open(alg_disk_cache_t *dcache)
{
    dcache->file = tmpfile();
    
    return dcache->file != NULL;
}

void
alg_disk_cache_close(alg_disk_cache_t *dcache)
{
    if (dcache->file) {
        fclose(dcache->file);
    }
}

ssize_t
alg_disk_cache_write(alg_disk_cache_t *dcache, const void *data, size_t size)
{
    long curpos;
    
    if (NULL == dcache->file &&
        !alg_disk_cache_open(dcache)) {
        return -1;
    }

    curpos = ftell(dcache->file);
    if (curpos < 0) {
        return -10;
    }
    if (fseek(dcache->file, 0, SEEK_END)) {
        return -11;
    }

    if (fwrite(&size, , size_t __n, FILE *restrict __s))
}

ssize_t
alg_disk_cache_read(alg_disk_cache_t *dcache, void *data, size_t size)
{}

void
alg_disk_cache_rollback(alg_disk_cache_t *dcache, size_t n)
{}
