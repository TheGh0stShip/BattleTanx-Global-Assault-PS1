extern unsigned char D_800B0520[];
extern void func_80039094(void *object, void *entry);

void func_800393C0(unsigned char *object, int index) {
    func_80039094(object, D_800B0520 + index * 24);
    *(int *)(object + 0x204) = index;
}
