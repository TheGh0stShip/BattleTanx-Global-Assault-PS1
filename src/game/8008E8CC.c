typedef unsigned int u32;

extern u32 D_800EEC34;
extern void (*D_800EEC3C)(int, void *);
extern void (*D_800EEC40)(int, void *);
extern void func_8008A7BC(void *destination, const void *source, u32 size);
extern int func_80090184(const char *text);
extern void func_8009940C(void *owner, int event, void *data, int size,
                          void (*callback)(void));
extern void func_8008E860(void);
extern void func_8008EA00(void);

void func_8008E8CC(void *owner, int event, void *data, u32 size, void *active)
{
    register void *saved_owner asm("$18") = owner;
    register int saved_event asm("$5") = event;
    register void *saved_data asm("$8") = data;
    register u32 saved_size asm("$6") = size;
    register void *saved_active asm("$7") = active;
    register int cleanup asm("$17") = 1;
    register u32 *flags asm("$4") = &D_800EEC34;

    *flags &= ~2U;
    asm volatile("" : : : "memory");
    if (saved_active != 0) {
        switch (saved_event) {
        case 6: {
            register unsigned char *state asm("$16") = (unsigned char *)&D_800EEC34;
            u32 maximum = *(u32 *)(state + 0x1a4);
            if (saved_size >= maximum) {
                saved_size = maximum;
            }
            func_8008A7BC(*(void **)(state + 0x1a0), saved_data, saved_size);
            {
                register u32 end asm("$2") = *(u32 *)(state + 0x1a4);
                register u32 start asm("$3") = *(u32 *)(state + 0x1a0);
                *(unsigned char *)(start + end - 1) = 0;
            }
            cleanup = 0;
            {
                register int length asm("$7") =
                    func_80090184(*(char **)(state + 0x19c)) + 1;
                register void *payload asm("$6") = *(void **)(state + 0x19c);
                register void (*callback)(void) asm("$2") = func_8008E860;
                asm("" : "+r"(length));
                func_8009940C(saved_owner, 6, payload, length, callback);
            }
            break;
        }
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
            break;
        case 15: {
            void (*callback)(int, void *) = D_800EEC3C;
            if (callback != 0) {
                callback(saved_event, saved_data);
            }
            break;
        }
        case 16: {
            void (*callback)(int, void *) = D_800EEC40;
            if (callback != 0) {
                callback(saved_event, saved_data);
            }
            break;
        }
        case 17:
            break;
        }
    }
    if (cleanup != 0) {
        asm volatile("");
        func_8008EA00();
    }
}
