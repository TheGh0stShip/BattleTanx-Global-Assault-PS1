typedef struct RequestTable {
    int default_port;
    int default_unit;
    unsigned int port_count;
    int (*io[10])(int, char *, int *, int *);
} RequestTable;

extern RequestTable D_800EDC9C;
extern char func_80094AAC(int);

void func_80081E94(char *path, int *port, int *unit, char **name) {
    char device[16];
    int found;
    char *rest = path;
    int has_device = 0;
    unsigned int i = 0;
    char c;
    int result;

    for (; i < 9; i++) {
        c = path[i];
        device[i] = func_80094AAC(c);
        if (c == ':') {
            i++;
            rest = path + i;
            has_device = 1;
            break;
        }
        if (c == 0) {
            break;
        }
    }
    device[i] = 0;
    if (has_device) {
        result = -1;
        for (i = 0; i < D_800EDC9C.port_count; i++) {
            found = 0;
            if (D_800EDC9C.io[i](1, device, unit, &found)) {
                result = i;
                if (found != 0) {
                    rest = path;
                }
                break;
            }
        }
        *port = result;
    } else {
        *port = D_800EDC9C.default_port;
        *unit = D_800EDC9C.default_unit;
    }
    if (name != 0) {
        *name = rest;
    }
}
