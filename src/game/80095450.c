extern int D_800EF0A4;
extern void func_8009F71C(int handle);

void func_80095450(void) {
    register int *slot asm("$16") = &D_800EF0A4;
    asm("" : "+r"(slot));

    if (*slot >= 0) {
        func_8009F71C(*slot);
        *slot = -1;
    }
}
