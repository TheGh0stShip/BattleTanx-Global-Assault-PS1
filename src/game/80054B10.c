typedef struct {
    unsigned long addr;
    char pad4[0x14 - 4];
} Sound;
typedef struct {
    int pad0;
    int data_offset;
    int data_size;
    int table_size;
    unsigned int count;
    Sound table[1];
} Bank;
extern Sound *D_800E4658;
extern Bank *func_8003DD08(int);
extern Sound *func_80068FC8(int);
extern void func_8008A7BC(void *, void *, int);
extern unsigned long func_80090984(int);
extern void func_800902B4(int);
extern void func_800902E4(unsigned long);
extern void func_80090344(void *, int);
extern void func_80090D60(int);
extern void func_80069030(void *);

static inline void upload(unsigned long base, void *data, int size) {
    func_800902B4(0);
    func_800902E4(base);
    func_80090344(data, size);
    func_80090D60(1);
}

void func_80054B10(int file) {
    Bank *bank;
    int table_size;
    int offset;
    int size;
    unsigned int count;
    unsigned long base;
    unsigned short i;

    bank = func_8003DD08(file);
    table_size = bank->table_size;
    offset = bank->data_offset;
    size = bank->data_size;
    count = bank->count;
    D_800E4658 = func_80068FC8(table_size);
    func_8008A7BC(D_800E4658, bank->table, table_size);
    base = func_80090984(size);
    upload(base, (char *)bank + offset, size);
    for (i = 0; i < count; i++) {
        D_800E4658[i].addr += base;
    }
    func_80069030(bank);
}
