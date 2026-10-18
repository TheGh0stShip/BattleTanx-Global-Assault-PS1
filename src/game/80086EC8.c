extern unsigned char D_800EE588[];
extern int func_80086E38(int value);

int func_80086EC8(void) {
    int result = func_80086E38(D_800EE588[238]);
    if (D_800EE588[8] != 0) {
        result += 4;
    }
    return result;
}
