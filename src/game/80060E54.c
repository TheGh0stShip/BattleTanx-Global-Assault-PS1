typedef struct Element {
    int pad[2];
    unsigned char ***name;
} Element;

extern char D_800A8F44[];
extern Element *func_8005A2A0(void *);
extern void func_8005A2F0(Element *, void *);

void func_80060E54(void *menu) {
    Element *element;
    char *target;

    element = func_8005A2A0(menu);
    switch (***element->name) {
    case 'C':
        switch ((**element->name)[1]) {
        case 'L':
            target = (char *)element - 0x140;
            break;
        case 'O':
            target = 0;
            break;
        default:
            target = D_800A8F44;
            break;
        }
        break;
    case 'E':
        if ((**element->name)[1] == 'R') {
            target = (char *)element - 0x120;
        } else if ((**element->name)[1] == 'N') {
            target = (char *)element - 0xE0;
        } else {
            target = (char *)element - 0xC0;
        }
        break;
    case 'P':
    case 'Q':
    case 'R':
    case 'S':
    case 'T':
    case 'V':
    case 'W':
    case 'X':
    case 'Y':
    case 'Z':
        target = (char *)element - 0x160;
        break;
    default:
        target = D_800A8F44;
        break;
    }
    if (target != 0) {
        func_8005A2F0(element, target);
    }
}
