typedef struct Element {
    int pad[2];
    unsigned char ***name;
} Element;

extern void func_8005A2F0(Element *, void *);

int func_80060F6C(void *menu, Element *element) {
    char *target;

    switch (***element->name) {
    case 'B':
        target = (char *)element + 0x140;
        break;
    case 'P':
        target = (char *)element + 0x120;
        break;
    case 'C':
        if ((**element->name)[1] == 'L') {
            target = (char *)element + 0x60;
        } else {
            target = (char *)element - 0x20;
        }
        break;
    default:
        target = (char *)element - 0x20;
        break;
    }
    func_8005A2F0(element, target);
    return 0;
}
