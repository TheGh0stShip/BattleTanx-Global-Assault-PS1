struct RenderState {
    unsigned char pad_00[8];
    unsigned int value_08;
    void *context;
    unsigned char pad_10[4];
    unsigned char payload[0x28];
    unsigned int active_3C;
    unsigned int active_40;
};

extern struct RenderState D_800EE510;

void func_8008AA48(void *destination, int value, unsigned int size);
void func_80094D6C(void *payload, void *value, void *context, int enabled);

void func_80086BF4(void *value, void *context) {
    func_8008AA48(&D_800EE510, 0, 0x78);
    D_800EE510.value_08 = 0;
    D_800EE510.context = context;
    D_800EE510.active_3C = 1;
    D_800EE510.active_40 = 1;
    func_80094D6C(D_800EE510.payload, value, context, 1);
}
