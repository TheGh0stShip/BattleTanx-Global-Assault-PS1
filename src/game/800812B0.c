int func_800812B0(const unsigned int *source, int count) {
    register int remaining asm("$6") = count - 1;
    register unsigned int *control asm("$3");
    register unsigned int command asm("$2");

    asm("" : "+r"(remaining));
    control = (unsigned int *)0x800B0000;
    asm("" : "+r"(control));
    control = *(unsigned int **)((unsigned char *)control + 0x0D38);
    asm("" : "+r"(control));
    command = 0x04000000;
    asm("" : "+r"(command));
    *control = command;
    if (count != 0) {
        count = -1;
        do {
            register unsigned int data asm("$3") = *source;
            register unsigned int *port asm("$2");
            asm("" : "+r"(data));
            source++;
            port = (unsigned int *)0x800B0000;
            asm("" : "+r"(port));
            port = *(unsigned int **)((unsigned char *)port + 0x0D34);
            asm("" : "+r"(port));
            remaining--;
            *port = data;
        } while (remaining != count);
    }
    return 0;
}
