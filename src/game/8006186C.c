extern signed char D_800A606C;
extern unsigned int D_800A6084[];
extern int func_80022814(void);

int func_8006186C(unsigned short slot) {
    unsigned short index;
    unsigned short count;
    unsigned short i;

    index = slot;
    if (func_80022814()) {
        if (D_800A606C == 1 && index != 0) {
            index = slot + 1;
        }
        switch (index) {
        case 0:
            return 1;
        case 1:
            return 2;
        case 2:
            return 3;
        case 3:
            return 4;
        case 4:
            return 5;
        }
    } else if (index < 4) {
        count = 0;
        i = 0;
        do {
            if (D_800A6084[i] != 0) {
                count++;
            }
            i++;
        } while (index >= count);
        i--;
        switch (D_800A6084[i]) {
        case 0:
            break;
        case 2:
            return 3;
        case 3:
            return 1;
        case 4:
            return 4;
        case 1:
            return 5;
        }
    }
    return 0;
}
