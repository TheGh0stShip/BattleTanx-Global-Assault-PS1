typedef struct {
    char pad00[0x1C];
    int w1c;
    char pad20[8];
    int w28;
    char pad2c[6];
    volatile unsigned char b32;
    volatile unsigned char b33;
    char pad34[4];
    volatile unsigned char b38;
    volatile unsigned char b39;
    volatile unsigned char b3a;
    volatile unsigned char b3b;
    volatile unsigned char b3c;
    volatile unsigned char b3d;
    volatile unsigned char b3e;
    char pad3f[3];
    volatile unsigned char b42;
    char pad43[0xD];
    unsigned int w50;
    unsigned int w54;
    unsigned int w58;
    unsigned int w5c;
    char pad60[0x10];
    char *w70;
    int w74;
    int w78;
    int w7c;
    char pad80[4];
    int w84;
    char pad88[4];
    unsigned int w8c;
    int w90;
    char pad94[4];
    char *w98;
} StreamState;

extern StreamState D_800EEAE8;
extern void func_80091618(void (*cb)(void));
extern void func_80088BC0(int sector);
extern void func_8008A7BC(void *dst, void *src, int len);
extern void func_80088DC8(int mode);
extern void func_80088E48(int mode);

void func_80089518(void) {
    StreamState *s;
    StreamState *t;
    int done;
    int last;

    done = 0;
    func_80091618(0);
    s = &D_800EEAE8;
    s->b42 = 1;
    s->w1c++;
    if (s->b3a) {
        s->b3b = 1;
        return;
    }
    func_80088BC0(s->w90);
    if (s->b39 == 0) {
        last = s->b3c == 1;
        if (s->w70 != 0 && !last) {
            func_8008A7BC(s->w70, s->w98 + s->w78, s->w7c);
            s->w70 += s->w7c;
        }
        s = &D_800EEAE8;
        s->w78 = 0;
        s->w84 += s->w7c;
        if (s->w84 < s->w74) {
            s->w7c = s->w74 - s->w84;
            if (s->w7c > 2048) {
                s->w7c = 2048;
            }
            done = 1;
        } else {
            s->w84 = s->w74;
            func_80088DC8(2);
            if (s->b33 != 0 && !last) {
                done = 0;
                if (s->w50 != s->w54 || s->w58 == s->w5c || s->w8c < s->w58 || s->w8c >= s->w58 + 2048) {
                    done = 1;
                }
            } else {
                t = &D_800EEAE8;
                if (t->b3d == 0) {
                    t->b3c = 0;
                } else {
                    done = 1;
                }
            }
        }
    } else if (s->w50 != s->w54 || s->w58 == s->w5c || s->w8c < s->w58 || s->w8c >= s->w58 + 2048) {
        done = 1;
    }
    t = &D_800EEAE8;
    if (t->b38) {
        if (done) {
            if (t->b3e == 0) {
                t->w90 += 2048;
            }
            t->b3e = 0;
            if (t->b33 && !t->b3c) {
                t->b39 = 1;
            }
        } else {
            if (t->b39) {
                t->b39 = 0;
                t->w28++;
            }
            if (t->b33 && t->b32 && !t->b39 && !t->b3c) {
                func_80088E48(2);
            }
        }
    }
}
