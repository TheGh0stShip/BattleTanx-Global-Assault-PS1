typedef struct Element {
    int pad[2];
    unsigned char ***name;
} Element;

extern char D_800A8B64[];
extern Element *func_8005A2A0(void *);
extern void func_8005A2F0(Element *, void *);

void func_80060D60(void *menu) {
    Element *element;
    char *target;

    element = func_8005A2A0(menu);
    target = 0;
    switch (***element->name) {
    case 'C':
        switch ((**element->name)[1]) {
        case 'L':
            break;
        case 'O':
            target = D_800A8B64;
            break;
        default:
            target = (char *)element + 0x160;
            break;
        }
        break;
    case 'B':
    case 'D':
    case 'F':
    case 'G':
    case 'H':
    case 'J':
    case 'K':
    case 'L':
    case 'M':
    case 'P':
        target = (char *)element + 0x160;
        break;
    case 'N':
    case 'Q':
    case 'R':
        target = (char *)element + 0x140;
        break;
    case 'S':
        target = (char *)element + 0x120;
        break;
    case 'T':
    case 'V':
        target = (char *)element + 0x100;
        break;
    case 'W':
        target = (char *)element + 0xE0;
        break;
    case 'X':
    case 'Y':
        target = (char *)element + 0xC0;
        break;
    case 'Z':
        target = (char *)element + 0xA0;
        break;
    }
    if (target != 0) {
        func_8005A2F0(element, target);
    }
}
