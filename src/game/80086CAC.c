extern unsigned int func_80088870(int a);
extern int func_8009601C(int a, int *b, int *c);

void func_80086CAC(int timeout, int *result, int *status) {
    unsigned int end = func_80088870(-1) + 1;
    int done;

    do {
        done = func_8009601C(1, result, status);
        if (done != 0) {
            break;
        }
    } while (func_80088870(-1) < end + timeout);
    if (done != 1) {
        *result = 0;
        *status = -1;
    }
}
