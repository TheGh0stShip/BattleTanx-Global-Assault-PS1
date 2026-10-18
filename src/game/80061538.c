typedef struct Group {
    int pad[5];
    short value;
} Group;

typedef struct Element {
    int pad[2];
    int *style;
} Element;

typedef struct Profile {
    int pad;
    int id;
} Profile;

extern Group D_800AB604;
extern unsigned char D_800ABA5A;
extern int D_800EAF38;
extern short D_800ABA54[];
extern short D_800ABA58;
extern int func_80022814(void);
extern Profile *func_8006A7FC(void);
extern int func_80022ABC(int);
extern int func_80022ADC(void);
extern void func_80063E3C(int, int, unsigned short);
extern void func_80059550(void *, void *, int);
extern Element *func_8005A2A0(void *);
extern void func_8005A54C(void *);

void func_80061538(void) {
    int value;
    Group *group;

    if (func_80022814()) {
        value = func_80022ABC(func_8006A7FC()->id);
    } else {
        value = func_80022ADC();
    }
    func_80063E3C(value, 100000 << 12, 1);
    group = &D_800AB604;
    group->value = D_800ABA5A;
    func_80059550(group, 0, 1);
    if (func_8005A2A0(group)->style != &D_800EAF38) {
        do {
            func_8005A54C(group);
        } while (func_8005A2A0(group)->style != &D_800EAF38);
    }
    D_800ABA54[0] = 1;
    D_800ABA54[1] = 1;
    D_800ABA58 = 1;
}
