struct CallbackState {
    int field_00;
    int field_04;
    int field_08;
    int field_0C;
    int field_10;
    int field_14;
};

extern unsigned short D_800B5A78;
extern unsigned char D_800B5AB0[];
extern unsigned int D_800B5AB4;
extern unsigned short *D_800B6B04;
extern unsigned short *D_800B6B08;
extern unsigned int *D_800B6B0C;

void func_80094A14(unsigned int *destination, unsigned int count);
int func_8009D74C(void *value);
void func_800945E4(void);
void func_8009D788(void *value);
int func_80096E7C(void);
int func_8009D798(void);
void func_8009DA40(struct CallbackState *state);
void func_80094168(void);

void *func_8009450C(void) {
    register unsigned short *base asm("$16") = &D_800B5A78;
    register unsigned int *link asm("$16");
    register volatile unsigned short *current asm("$2");
    register unsigned short *other asm("$3");
    register struct CallbackState *state asm("$3");
    register struct CallbackState *state_argument asm("$4");
    int result;

    asm("" : "+r"(base));
    if (*base != 0) {
        return 0;
    }

    asm("lui $3,%%hi(D_800B6B04)\n\tlw $3,%%lo(D_800B6B04)($3)" : "=r"(other));
    asm("lui $2,%%hi(D_800B6B08)\n\tlw $2,%%lo(D_800B6B08)($2)" : "=r"(current));
    *current = 0;
    *other = *current;
    *D_800B6B0C = 0x33333333;
    func_80094A14((unsigned int *)base, 0x41A);
    if (func_8009D74C(base + 0x1C) != 0) {
        asm volatile("" : : : "memory");
        func_800945E4();
    }

    asm volatile("" : : : "memory");
    asm("lui $16,%%hi(D_800B5AB4)\n\taddiu $16,$16,%%lo(D_800B5AB4)" : "=r"(link));
    *link = (unsigned int)(link + 0x3F7);
    func_8009D788(link - 1);
    *(unsigned short *)((unsigned char *)link - 0x3C) = 1;
    result = func_80096E7C();
    asm("lui $3,%%hi(D_800B6B00)\n\tlw $3,%%lo(D_800B6B00)($3)" : "=r"(state));
    state->field_14 = result;
    result = func_8009D798();
    asm("lui $4,%%hi(D_800B6B00)\n\tlw $4,%%lo(D_800B6B00)($4)" : "=r"(state_argument));
    state_argument->field_04 = result;
    func_8009DA40(state_argument);
    func_80094168();
    link = (unsigned int *)((unsigned char *)link - 0x3C);
    asm("" : "+r"(link));
    return link;
}
