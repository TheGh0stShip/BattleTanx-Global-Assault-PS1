extern unsigned char D_800C5AC4[];
extern volatile unsigned int * volatile D_800B8BA0;
extern volatile unsigned int * volatile D_800B8B74;
extern volatile unsigned int * volatile D_800B8B80;
extern void func_800943B0(void *state, int value);

int func_8009C938(int value) {
    register void *state asm("$4") = D_800C5AC4;
    register int argument asm("$5") = value;
    register int result asm("$2");

    asm("" : "+r"(state), "+r"(argument));
    func_800943B0(state, argument);
    {
        register volatile unsigned int *pointer asm("$3");
        register unsigned int command asm("$2");
        asm volatile("lui %0,%%hi(D_800B8BA0)\n\t"
                     "lw %0,%%lo(D_800B8BA0)(%0)"
                     : "=r"(pointer) : : "memory");
        command = 0x80000000U;
        *pointer = command;
    }
    {
        register volatile unsigned int *pointer asm("$2");
        asm volatile("lui %0,%%hi(D_800B8B74)\n\t"
                     "lw %0,%%lo(D_800B8B74)(%0)\n\t"
                     "nop"
                     : "=r"(pointer) : : "memory");
        *pointer = 0;
    }
    {
        register volatile unsigned int *pointer asm("$2");
        asm volatile("lui %0,%%hi(D_800B8B80)\n\t"
                     "lw %0,%%lo(D_800B8B80)(%0)\n\t"
                     "nop"
                     : "=r"(pointer) : : "memory");
        *pointer = 0;
    }
    result = 0;
    asm("" : "+r"(result));
    {
        register volatile unsigned int *sync asm("$3");
        register volatile unsigned int *target asm("$4");
        register unsigned int command asm("$3");
        asm volatile("lui %0,%%hi(D_800B8B80)\n\t"
                     "lw %0,%%lo(D_800B8B80)(%0)"
                     : "=r"(sync) : : "memory");
        asm volatile("lui %0,%%hi(D_800B8BA0)\n\t"
                     "lw %0,%%lo(D_800B8BA0)(%0)"
                     : "=r"(target) : : "memory");
        command = *sync;
        command = 0x60000000U;
        *target = command;
    }
    return result;
}
