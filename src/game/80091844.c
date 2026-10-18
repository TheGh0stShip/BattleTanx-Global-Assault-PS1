extern unsigned int D_800EEE3C;

int func_8009702C(void);
int func_80091604(int value);
void func_8009759C(int type, void *data);
void func_800973AC(int type, void *data, int extra);
void func_80088870(int value);

void func_80091844(int next) {
    unsigned char data[8];
    unsigned char event;
    int previous;
    int callback;
    register int changed asm("$16");
    register int active asm("$3");
    register int difference asm("$3");
    register int *small_data asm("$28");

    previous = func_8009702C();
    if (previous == next) {
        return;
    }

    callback = func_80091604(0);
    asm("" : "+r"(previous));
    previous &= 0x80;
    difference = previous ^ (next & 0x80);
    asm("" : "+r"(difference));
    asm("sltu $16,$0,$3" : "=r"(changed) : "r"(difference));
    active = small_data[0x12];
    if (active == 0 && changed != 0 && (next & 0x80) != 0) {
        small_data[0x12] = 1;
        func_8009759C(0x10, data);
        func_800973AC(2, data, 0);
    }

    event = next;
    func_800973AC(0xE, &event, 0);
    if (changed != 0) {
        D_800EEE3C++;
        func_80088870(0);
        func_80088870(0);
        func_80088870(0);
        func_80088870(0);
    }
    func_80091604(callback);
}
