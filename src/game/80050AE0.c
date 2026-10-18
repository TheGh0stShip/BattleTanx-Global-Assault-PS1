typedef struct AngleObject {
    unsigned char unused[0x2C];
    unsigned short angle;
} AngleObject;

typedef struct TargetObject {
    int unused;
    void *target;
} TargetObject;

extern int func_80047B8C(int scale, unsigned int angle);
extern void func_80043F40(AngleObject *object, void *target,
                          unsigned int first, unsigned int second);

void func_80050AE0(AngleObject *object, TargetObject *target) {
    unsigned int value = (unsigned short)func_80047B8C(0x4000, object->angle);

    func_80043F40(object, target->target, value, value);
}
