void func_80096F6C(unsigned int *destination, unsigned int count) {
    int index = count - 1;

    if (count != 0) {
        do {
            *destination = 0;
            index--;
            destination++;
        } while (index != -1);
    }
}
