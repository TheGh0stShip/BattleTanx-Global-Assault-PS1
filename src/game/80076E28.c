typedef struct SaveHeader {
    char title[58];
    unsigned char difficulty;
    unsigned char options[18];
    unsigned char vibration[2];
    char pad4F;
    unsigned short music;
    unsigned short sfx;
    unsigned short pad_mode[2];
} SaveHeader;

extern unsigned char D_800A60D8;
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
extern char *func_8008DA04(char *, char *);
extern int func_800862D4(int);

void func_80076E28(SaveHeader *save) {
    char title[58] = "BattleTanx Global Assault, Copyright 1999 The 3DO Company";
    int i;

    func_8008DA04(save->title, title);
    save->difficulty = D_800A60D8;
    save->options[0] = D_800AED48;
    save->options[1] = D_800AED49;
    save->options[2] = D_800AED4A;
    save->options[3] = D_800AED4B;
    save->options[4] = D_800AED4C;
    save->options[5] = D_800AED4D;
    save->options[6] = D_800AED4E;
    save->options[7] = D_800AED4F;
    save->options[8] = D_800AED50;
    save->options[9] = D_800AED51;
    save->options[10] = D_800AED52;
    save->options[11] = D_800AED53;
    save->options[12] = D_800AED54;
    save->options[13] = D_800AED55;
    save->options[14] = D_800AED56;
    save->options[15] = D_800AED57;
    save->options[16] = D_800AED58;
    save->options[17] = D_800AED59;
    if (func_800862D4(0)) {
        save->vibration[0] = 1;
    } else {
        save->vibration[0] = 0;
    }
    if (func_800862D4(1)) {
        save->vibration[1] = 1;
    } else {
        save->vibration[1] = 0;
    }
    save->music = D_800E4654;
    save->sfx = D_800E540C;
    save->pad_mode[0] = D_800EC0F8[0];
    save->pad_mode[1] = D_800EC0F8[1];
}
