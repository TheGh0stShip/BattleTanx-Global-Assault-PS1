typedef struct {
    unsigned char minute;
    unsigned char second;
    unsigned char sector;
    unsigned char track;
} CdlLOC;

typedef struct {
    unsigned short id;
    unsigned short type;
    unsigned short secCount;
    unsigned short nSectors;
    unsigned long frameCount;
    unsigned long frameSize;
    unsigned short width;
    unsigned short height;
    unsigned long dummy1;
    unsigned long dummy2;
    CdlLOC loc;
} StHEADER;

extern StHEADER *D_800EF230;
extern int D_800EF238;
extern int D_800EF234;
extern void (*D_800EF1F8)(void);
extern int D_800EF228;
extern CdlLOC D_800EFE20;
extern int D_800EFE24;

void func_800A2FF0(void)
{
    StHEADER *ptr = &D_800EF230[D_800EF238];
    do {
    } while (0);

    ptr->id = 2;
    D_800EFE20 = ptr->loc;
    D_800EFE24 = ptr->frameCount;
    D_800EF238 = D_800EF234;
    if (D_800EF1F8 != 0) {
        D_800EF1F8();
    }
    D_800EF228 = 0;
}
