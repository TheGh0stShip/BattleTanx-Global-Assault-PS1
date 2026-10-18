int func_80086D3C(unsigned char *name, int *port) {
    int ok = 0;

    if (name[3] == ':' && name[0] == 'b' && name[1] == 'k') {
        ok = 1;
        *port = (name[2] - '0') << 4;
    } else if (name[4] == ':' && name[0] == 'b' && name[1] == 'k') {
        ok = 1;
        *port = ((name[2] - '0') << 4) | (name[3] - '0');
    }
    return ok;
}
