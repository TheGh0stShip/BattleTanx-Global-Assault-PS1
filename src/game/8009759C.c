typedef struct {
    unsigned char minute;
    unsigned char second;
    unsigned char sector;
    unsigned char track;
} CdLoc8009759C;

static inline int int_to_bcd(int v) {
    return v / 10 * 16 + v % 10;
}

CdLoc8009759C *func_8009759C(int pos, CdLoc8009759C *loc) {
    int seconds;
    int minutes;

    pos += 150;
    seconds = pos / 75;
    minutes = seconds / 60;
    loc->sector = int_to_bcd(pos % 75);
    loc->second = int_to_bcd(seconds % 60);
    loc->minute = int_to_bcd(minutes);
    return loc;
}
