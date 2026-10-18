typedef struct Menu {
    int pad;
    unsigned char *base;
    int pad2[3];
    short cursor;
    short x;
    short y;
} Menu;

extern Menu D_800AA2A8;
extern Menu D_800AA348;
extern Menu D_800AA3E8;
extern Menu D_800AA488;
extern Menu D_800AA4E8;
extern Menu D_800AAA18;
extern Menu D_800AAAB8;
extern Menu D_800AAB58;
extern Menu D_800AABF8;
extern Menu D_800AAC58;
extern Menu D_800AACB8;
extern signed char D_800A606C;
extern unsigned char D_800AACD4;
extern unsigned char D_800AACD5;
extern short D_800AACE6;
extern int D_800A60A4[];
extern void func_8005D638(Menu *, unsigned short);
extern void func_8005D794(Menu *, unsigned short);
extern void func_80059550(Menu *, void *, int);
extern void func_8005D494(void);

int func_8005DFBC(void *parent) {
    unsigned short i;

    D_800AACD4 = 100;
    D_800AACD5 = 100;
    D_800AACE6 = D_800A606C;
    if (D_800A606C == 1) {
        for (i = 0; i < 4; i++) {
            switch (i) {
            case 0:
                D_800A60A4[0] = 2;
                func_8005D638(&D_800AA2A8, 0);
                D_800AA2A8.cursor = 0;
                func_80059550(&D_800AA2A8, parent, 0);
                break;
            case 1:
                D_800A60A4[1] = 1;
                func_8005D794(&D_800AA348, 1);
                D_800AA348.cursor = 0;
                func_80059550(&D_800AA348, parent, 3);
                break;
            case 2:
                func_8005D794(&D_800AA3E8, 2);
                D_800AA3E8.cursor = 0;
                func_80059550(&D_800AA3E8, parent, 3);
                break;
            case 3:
                func_8005D794(&D_800AA488, 3);
                D_800AA488.cursor = 0;
                func_80059550(&D_800AA488, parent, 3);
                break;
            }
        }
        D_800AA4E8.x = 20;
        D_800AA4E8.y = 207;
        D_800AA4E8.base[0x21] = 16;
        D_800AA4E8.cursor = 0;
        func_80059550(&D_800AA4E8, parent, 3);
    } else {
        for (i = 0; i < 4; i++) {
            switch (i) {
            case 0:
                D_800A60A4[0] = 2;
                func_8005D638(&D_800AAA18, 0);
                D_800AAA18.cursor = 0;
                func_80059550(&D_800AAA18, parent, 0);
                break;
            case 1:
                D_800A60A4[1] = 2;
                func_8005D638(&D_800AAAB8, 1);
                D_800AAAB8.cursor = 1;
                func_80059550(&D_800AAAB8, parent, 0);
                break;
            case 2:
                func_8005D794(&D_800AAB58, 2);
                D_800AAB58.cursor = 0;
                func_80059550(&D_800AAB58, parent, 3);
                break;
            case 3:
                func_8005D794(&D_800AABF8, 3);
                D_800AABF8.cursor = 1;
                func_80059550(&D_800AABF8, parent, 3);
                break;
            }
        }
        D_800AAC58.x = 16;
        D_800AAC58.y = 97;
        D_800AAC58.base[0x21] = 16;
        D_800AAC58.cursor = 0;
        func_80059550(&D_800AAC58, parent, 3);
        D_800AACB8.x = 214;
        D_800AACB8.y = 210;
        D_800AACB8.base[0x21] = 16;
        D_800AACB8.cursor = 1;
        func_80059550(&D_800AACB8, parent, 3);
    }
    func_8005D494();
    return 1;
}
