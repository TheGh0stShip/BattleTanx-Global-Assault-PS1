typedef struct MenuObject {
    int unused;
    char *data;
} MenuObject;

extern void func_8005A2F0(void *event, void *target);

int func_80063BAC(MenuObject *object, void *event) {
    func_8005A2F0(event, object->data + 0x20);
    return 0;
}
