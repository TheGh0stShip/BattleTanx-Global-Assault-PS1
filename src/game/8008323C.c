extern int func_80090184(const unsigned char *text);

unsigned char *func_8008323C(unsigned char *text) {
    unsigned char *result = text + func_80090184(text);
    unsigned char *cursor = result - 1;

    if (text < cursor) {
        do {
            unsigned int value = *cursor;

            if (value == '.') {
                result = cursor;
                break;
            }
            if (value == '\\' || value == '/' || value == ':') {
                break;
            }
            cursor--;
        } while (text < cursor);
    }
    return result;
}
