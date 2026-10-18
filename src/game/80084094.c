typedef struct Stream {
    int single;
    int wrapped;
    unsigned int size;
    unsigned int mark;
    unsigned int pos;
    int pad14;
    int header_words;
    int step;
} Stream;

typedef struct StreamState {
    char pad00[0x54];
    int mode;
} StreamState;

extern StreamState D_800EDF78;

unsigned short *func_80084094(Stream *s, unsigned short *p) {
    s->pos += s->step;
    p = (unsigned short *)((char *)p + s->step);
    if (s->pos >= s->size) {
        if (s->single != 0) {
            if (D_800EDF78.mode == 1) {
                D_800EDF78.mode = 3;
            } else {
                D_800EDF78.mode = 0;
            }
        } else {
            s->wrapped = 1;
            s->pos = s->header_words * 4 + 32;
            p = (unsigned short *)((char *)s + s->pos);
        }
    }
    if (s->wrapped != 0) {
        if (D_800EDF78.mode == 1) {
            s->mark = s->pos + s->step;
            if (s->mark >= s->size) {
                s->mark = s->header_words * 4 + 32;
            }
        } else if (s->pos == s->mark) {
            D_800EDF78.mode = 0;
        }
    }
    if (D_800EDF78.mode == 4 && *p == 0xFFFF) {
        D_800EDF78.mode = 0;
    }
    return p;
}
