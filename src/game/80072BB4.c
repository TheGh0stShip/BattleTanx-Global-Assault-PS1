typedef struct {
    char pad[0x16];
    short kind;
    char pad2[0x4];
} Entry;

extern Entry D_800AE184[];
extern void func_8007224C(int *obj);
extern void func_800728E8(int *obj);
extern void func_80071ECC(int *obj);

void func_80072BB4(int *obj) {
    switch (D_800AE184[obj[2]].kind) {
    case 0:
        func_8007224C(obj);
        break;
    case 1:
        func_800728E8(obj);
        break;
    case 2:
        func_80071ECC(obj);
        break;
    }
}
