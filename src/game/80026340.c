typedef struct {
    short x;
    short y;
    short z;
    unsigned short angle;
    int key;
} Marker;

typedef struct {
    unsigned short count;
    unsigned short start;
} Range;

typedef struct {
    int pad0;
    Range *range;
    Marker *markers;
} MarkerSet;

typedef struct {
    int x;
    int z;
    short angle;
    unsigned char used;
    char pad;
} Spot;

int func_80026340(MarkerSet **setp, int key, Spot *out, int max) {
    MarkerSet *set = *setp;
    Range *range = set->range;
    int found = 0;
    int i;

    for (i = range->start; i < range->start + range->count; i++) {
        Marker *m = &set->markers[i];

        if (m->key == key) {
            out[found].x = m->x;
            out[found].z = m->z;
            out[found].angle = m->angle;
            out[found].used = 0;
            found++;
            if (found == max) {
                return found;
            }
        }
    }
    return found;
}
