int func_8009D07C(int, int, int, char *);

int func_800941A8(int fd, char *buf, unsigned int size)
{
    int total = 0;
    int chunk;
    int n;

    while (size != 0) {
        chunk = size;
        if (size > 0x8000) {
            chunk = 0x8000;
        }
        total += n = func_8009D07C(0, fd, chunk, buf);
        if (n == -1) {
            return -1;
        }
        buf += n;
        size -= n;
        if (n < chunk) {
            return total;
        }
    }
    return total;
}
