struct Command {
    unsigned char type;
    unsigned char pad_01;
    unsigned short value;
};

struct Command *func_8004A794(unsigned int value);

struct Command *func_8004BE44(void *owner, struct Command *command) {
    for (;;) {
        if (command == 0) {
            return (struct Command *)((unsigned char *)owner + 0x11C);
        }
        if (command->type == 3) {
            return command + 1;
        }
        command = func_8004A794(command->value);
    }
}
