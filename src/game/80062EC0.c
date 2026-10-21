typedef struct Messages {
    unsigned short count;
    short pad;
    int timers[4];
    char text[1];
} Messages;

extern int D_800E47F4;

int func_80062EC0(Messages *messages) {
    unsigned short i;
    unsigned short j;
    int timer;
    char *dst;
    char *src;

    for (i = 0; i < messages->count; i++) {
        timer = messages->timers[i];
        messages->timers[i] = timer - D_800E47F4;
        if (messages->timers[i] < 0) {
            dst = messages->text;
            for (j = 0; j < i; j++) {
                while (*dst != '<') {
                    dst++;
                }
            }
            for (j = i + 1; j < messages->count; j++) {
                messages->timers[j - 1] = messages->timers[j];
            }
            src = dst + 1;
            while (*src != '<') {
                src++;
            }
            src++;
            while (*src != 0) {
                *dst++ = *src++;
            }
            *dst = 0;
            messages->count--;
        }
    }
    return messages->count == 0;
}
