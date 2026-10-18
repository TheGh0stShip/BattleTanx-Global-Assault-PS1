static inline char *put_number(char *p, int n) {
    int tens;

    if (n >= 100) {
        n = 99;
    }
    tens = n / 10;
    if (tens != 0) {
        *p++ = tens + '0';
    }
    n -= tens * 10;
    *p++ = n + '0';
    return p;
}

static inline char *put_two_digits(char *p, int n) {
    int tens;

    if (n >= 100) {
        n = 99;
    }
    tens = n / 10;
    n -= tens * 10;
    p[0] = tens + '0';
    p[1] = n + '0';
    return p + 2;
}

void func_800642C0(int frames, char *text) {
    int hours;
    int minutes;
    int seconds;

    hours = frames / 216000;
    frames -= hours * 216000;
    minutes = frames / 3600;
    frames -= minutes * 3600;
    seconds = frames / 60;
    if (hours == 0) {
        text = put_number(text, minutes);
        *text++ = ':';
        text = put_two_digits(text, seconds);
    } else {
        text = put_number(text, hours);
        *text++ = ':';
        text = put_two_digits(text, minutes);
        *text++ = ':';
        text = put_two_digits(text, seconds);
    }
    *text = 0;
}
