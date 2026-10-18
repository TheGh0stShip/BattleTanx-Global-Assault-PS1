void func_80039064(unsigned char *object, int *result) {
    unsigned short *counter = (unsigned short *)(object + 0x14);

    *counter -= 1;
    if ((short)*counter <= 0) {
        *result = 1;
    }
}
