typedef struct Element {
    int pad[2];
    unsigned char ***name;
} Element;

extern void func_8005A2F0(Element *, void *);

int func_80061008(void *menu, Element *element) {
    char *target;

    switch (***element->name) {
    case 'N':
        target = (char *)element - 0x140;
        break;
    case 'Z':
        target = (char *)element - 0x120;
        break;
    case 'E':
        target = (char *)element + 0x20;
        if ((**element->name)[1] == 'X') {
            target = (char *)element - 0x60;
        }
        break;
    default:
        target = (char *)element + 0x20;
        break;
    }
    func_8005A2F0(element, target);
    return 0;
}
