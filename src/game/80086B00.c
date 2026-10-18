extern int D_80086088;
extern int D_800C60A8;

void func_80086B00(void *allocation) {
    register void *volatile *global_pointer asm("$28");

    if (allocation != 0) {
        void *last = global_pointer[0x34 / 4];

        asm volatile("" : : : "memory");
        asm("" : "+r"(last));
        {
            register int *block_end asm("$5") = &D_800C60A8;

            asm("" : "+r"(block_end));
            if (allocation == last) {
                int saved = block_end[-1];

                block_end[-1] = 0;
                global_pointer[0x34 / 4] = 0;
                D_80086088 = saved;
            }
        }
    }
}
