unsigned short func_80056A40(unsigned char c) {
    if ((unsigned char)(c - 'A') < 26) {
        return c - 'A';
    }
    if ((unsigned char)(c - 'a') < 26) {
        return c - 'a' + 26;
    }
    if ((unsigned char)(c - '0') < 10) {
        return c - '0' + 52;
    }
    switch (c) {
    case '.':
        return 62;
    case ',':
        return 63;
    case '!':
        return 64;
    case '?':
        return 65;
    case '+':
        return 66;
    case '-':
        return 67;
    case '*':
        return 68;
    case '/':
        return 69;
    case '=':
        return 70;
    case '"':
        return 71;
    case '\'':
        return 72;
    case '@':
        return 73;
    case '%':
        return 74;
    case '(':
        return 75;
    case ')':
        return 76;
    case '^':
        return 77;
    case '~':
        return 78;
    case '#':
        return 79;
    case ':':
        return 80;
    }
    return 0xFFFF;
}
