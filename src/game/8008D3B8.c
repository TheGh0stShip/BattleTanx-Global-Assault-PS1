typedef struct Block {
    struct Block *next;
    struct Block *prev;
    unsigned short x;
    unsigned short y;
    unsigned short w;
    unsigned short h;
} Block;

typedef struct {
    Block *free;
    Block *used;
    Block *buckets[32];
} BlockPool;

extern void func_8008D258(BlockPool *pool, Block *block);
extern Block *func_8008D2CC(BlockPool *pool, int x, int y, int w, int h);

Block *func_8008D3B8(BlockPool *pool, int w, int h, int mode, int flags)
{
    Block *b;
    int area;
    int index;
    int ok;
    int f;
    int x;
    int y;
    int bw;
    int bh;
    int x0;
    int y0;
    int x1;
    int y1;
    int right;
    int bottom;
    int rw;
    int rh;
    int top_a;
    int top_b;
    int left_a;
    int left_b;
    int side_a;
    int low_a;
    int side_b;
    int low_b;

    if (mode == 0) {
        w = (w + 3) >> 2;
    }
    if (mode == 1) {
        w = (w + 1) >> 1;
    }
    area = w * h;
    index = area >> 10;
    if (index >= 32) {
        index = 31;
    }
    do {
        for (b = pool->buckets[index]; b != 0; b = b->next) {
            if (b->w * b->h < area || b->w < w || b->h < h) {
                continue;
            }
            ok = 1;
            f = flags;
            x = b->x;
            y = b->y;
            rw = w;
            rh = h;
            bw = b->w;
            bh = b->h;
            right = x + bw;
            bottom = y + bh;
            x0 = x;
            y0 = y;
            x1 = x0 + rw;
            y1 = y0 + rh;
            if ((f & 0x10) && mode == 2) {
                x0 = (x0 + 1) & ~1;
                x1 = x0 + rw;
                ok = (right - x0 < rw) ^ ok;
            }
            if ((f & 0x20) && mode == 2) {
                x0 = (x0 + 15) & ~15;
                x1 = x0 + rw;
                if (right - x0 < rw) {
                    ok = 0;
                }
            }
            if (f & 4) {
                if (w > 256) {
                    ok = 0;
                } else if (x1 - (x0 & ~63) > (256 >> (2 - mode))) {
                    f |= 1;
                }
            }
            if (f & 8) {
                if (h > 256) {
                    ok = 0;
                } else if (y1 - (y0 & ~255) > 256) {
                    f |= 2;
                }
            }
            if (f & 1) {
                x0 = (x0 + 63) & ~63;
                x1 = x0 + rw;
                if (right - x0 < rw) {
                    ok = 0;
                }
            }
            if (f & 2) {
                y0 = (y0 + 255) & ~255;
                y1 = y0 + rh;
                if (bottom - y0 < rh) {
                    ok = 0;
                }
            }
            if (!ok) {
                continue;
            }
            func_8008D258(pool, b);
            top_a = (y0 - y) * (x1 - x);
            top_b = (y0 - y) * rw;
            left_a = (x0 - x) * rh;
            left_b = (x0 - x) * (y1 - y);
            low_a = (bottom - y1) * bw;
            low_b = (bottom - y1) * (x1 - x);
            side_a = (right - x1) * (y1 - y);
            side_b = (right - x1) * bh;
            if ((top_b < top_a && left_b < top_a) || (top_b < left_a && left_b < left_a)) {
                if (top_a != 0) {
                    func_8008D2CC(pool, x, y, x1 - x, y0 - y);
                }
                if (left_a != 0) {
                    func_8008D2CC(pool, x, y0, x0 - x, rh);
                }
            } else {
                if (top_b != 0) {
                    func_8008D2CC(pool, x0, y, rw, y0 - y);
                }
                if (left_b != 0) {
                    func_8008D2CC(pool, x, y, x0 - x, y1 - y);
                }
            }
            if ((low_b < low_a && side_b < low_a) || (low_b < side_a && side_b < side_a)) {
                if (low_a != 0) {
                    func_8008D2CC(pool, x, y1, bw, bottom - y1);
                }
                if (side_a != 0) {
                    func_8008D2CC(pool, x1, y, right - x1, y1 - y);
                }
            } else {
                if (low_b != 0) {
                    func_8008D2CC(pool, x, y1, x1 - x, bottom - y1);
                }
                if (side_b != 0) {
                    func_8008D2CC(pool, x1, y, right - x1, bh);
                }
            }
            b->x = x0;
            b->y = y0;
            b->w = rw;
            b->h = rh;
            b->next = pool->used;
            pool->used = b;
            return b;
        }
    } while (++index < 32);
    return 0;
}
