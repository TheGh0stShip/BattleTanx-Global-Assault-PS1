int func_8008FE78(unsigned char *name, int *port) {
    int found = 0;

    if (name[3] == ':' && name[0] == 'c' && name[1] == 'o' && name[2] == 'm') {
        *port = 1;
        found = 1;
    } else if (name[4] == ':' && name[0] == 'c' && name[1] == 'o' && name[2] == 'm') {
        *port = name[3] - '0';
        found = 1;
    }
    return found;
}
