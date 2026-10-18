typedef struct SaveHeader {
    char title[58];
    unsigned char difficulty;
    unsigned char options[18];
    unsigned char vibration[2];
    char pad4F;
    unsigned short music;
    unsigned short sfx;
    short pad_mode[2];
} SaveHeader;

extern short D_800A60D8;
extern unsigned char D_800AED48;
extern unsigned char D_800AED49;
extern unsigned char D_800AED4A;
extern unsigned char D_800AED4B;
extern unsigned char D_800AED4C;
extern unsigned char D_800AED4D;
extern unsigned char D_800AED4E;
extern unsigned char D_800AED4F;
extern unsigned char D_800AED50;
extern unsigned char D_800AED51;
extern unsigned char D_800AED52;
extern unsigned char D_800AED53;
extern unsigned char D_800AED54;
extern unsigned char D_800AED55;
extern unsigned char D_800AED56;
extern unsigned char D_800AED57;
extern unsigned char D_800AED58;
extern unsigned char D_800AED59;
extern unsigned short D_800E4654;
extern unsigned short D_800E540C;
extern int D_800EC0F8[];
extern unsigned char D_800A6080;
extern unsigned char D_800A6081;
extern void func_80086270(int, int);
extern void func_8005BFCC(void);

void func_80076B80(SaveHeader *save) {
    unsigned short music;
    unsigned short sfx;

    D_800A60D8 = 0;
    D_800AED48 = 0;
    D_800AED49 = 0;
    D_800AED4A = 0;
    D_800AED4B = 0;
    D_800AED4C = 0;
    D_800AED4D = 0;
    D_800AED4E = 0;
    D_800AED4F = 0;
    D_800AED50 = 0;
    D_800AED51 = 0;
    D_800AED52 = 0;
    D_800AED53 = 0;
    D_800AED54 = 0;
    D_800AED55 = 0;
    D_800AED56 = 0;
    D_800AED57 = 0;
    D_800AED58 = 0;
    D_800AED59 = 0;
    D_800A60D8 = save->difficulty;
    D_800AED48 = save->options[0];
    D_800AED49 = save->options[1];
    D_800AED4A = save->options[2];
    D_800AED4B = save->options[3];
    D_800AED4C = save->options[4];
    D_800AED4D = save->options[5];
    D_800AED4E = save->options[6];
    D_800AED4F = save->options[7];
    D_800AED50 = save->options[8];
    D_800AED51 = save->options[9];
    D_800AED52 = save->options[10];
    D_800AED53 = save->options[11];
    D_800AED54 = save->options[12];
    D_800AED55 = save->options[13];
    D_800AED56 = save->options[14];
    D_800AED57 = save->options[15];
    D_800AED58 = save->options[16];
    D_800AED59 = save->options[17];
    if (save->vibration[0]) {
        func_80086270(0, 1);
    } else {
        func_80086270(0, 0);
    }
    if (save->vibration[1]) {
        func_80086270(1, 1);
    } else {
        func_80086270(1, 0);
    }
    music = save->music;
    sfx = save->sfx;
    D_800E4654 = music;
    D_800E540C = sfx;
    D_800EC0F8[0] = save->pad_mode[0];
    D_800EC0F8[1] = save->pad_mode[1];
    D_800A6080 = (short)music / 60;
    D_800A6081 = (short)sfx / 360;
    func_8005BFCC();
}
