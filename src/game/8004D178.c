int func_8004C678(unsigned char *object);
int func_8004CB94(unsigned char *object);
void func_8004BF64(unsigned char *object);
void func_8004CCE8(unsigned char *object);

void func_8004D178(unsigned char *object) {
    if (func_8004C678(object) != 0) {
        return;
    }
    if (func_8004CB94(object) != 0) {
        return;
    }
    func_8004BF64(object);
    func_8004CCE8(object);
}
