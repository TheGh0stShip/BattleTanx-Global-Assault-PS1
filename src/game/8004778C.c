typedef struct ProbeHit {
    int owner;
    char pad04[0x24 - 4];
} ProbeHit;
extern short D_800C628C;
unsigned short func_80017AAC(unsigned short, int, ProbeHit *, int, int);
int func_8004778C(unsigned short id, int arg, int owner) {
    ProbeHit hits[8];
    ProbeHit *list;
    int count;
    int remaining;
    int i;

    if (owner != 0) {
        list = hits;
        D_800C628C = 0;
        remaining = func_80017AAC(id, arg, list, 0, 0);
        count = remaining;
        for (i = 0; i < count; i++) {
            if (list[i].owner != owner) {
                return remaining;
            }
            remaining--;
        }
        return 0;
    } else {
        D_800C628C = 0;
        count = func_80017AAC(id, arg, hits, 0, 1);
        remaining = count;
        if (remaining != 0) {
            return remaining;
        }
    }
    return 0;
}
