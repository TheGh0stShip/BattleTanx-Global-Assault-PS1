extern void func_80098530(unsigned int angle, void *matrix);

void func_8008A4B8(void *matrix, unsigned int angle) {
    func_80098530((unsigned short)angle >> 4, matrix);
}
