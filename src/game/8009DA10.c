void func_8009DA10(unsigned int *destination, unsigned int count) {
    int index = count - 1;

    if (count != 0) {
        do {
            *destination = 0;
            index--;
            destination++;
        } while (index != -1);
    }
}
