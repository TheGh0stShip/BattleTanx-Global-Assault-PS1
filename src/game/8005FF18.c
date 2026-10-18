typedef unsigned char u8;
typedef unsigned short u16;

typedef struct MenuObject {
    u8 pad[0x14];
    u16 sound;
} MenuObject;

extern u8 D_800A605C[];
extern int func_800862D4(u16 sound);
extern void func_80086270(u16 sound, int enabled);
extern void func_8008634C(u16 sound, void *data, int value);

int func_8005FF18(MenuObject *object) {
    if (func_800862D4(object->sound)) {
        func_80086270(object->sound, 0);
    } else {
        func_80086270(object->sound, 1);
        func_8008634C(object->sound, D_800A605C, 0);
    }
    return 0;
}
