#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

/* stubs for libc */
int _write(int file, char *ptr, int len)
{
    (void)file;

    for (int i = 0; i < len; i++)
    {
        /* TODO: redirect to UART if needed */
    }
    return len;
}

int _close(int file)
{
    (void)file;
    return -1;
}

int _fstat(int file, struct stat *st)
{
    (void)file;
    st->st_mode = S_IFCHR;
    return 0;
}

int _isatty(int file)
{
    (void)file;
    return 1;
}

int _lseek(int file, int ptr, int dir)
{
    (void)file;
    (void)ptr;
    (void)dir;
    return 0;
}

int _read(int file, char *ptr, int len)
{
    (void)file;
    (void)ptr;
    (void)len;
    return 0;
}
