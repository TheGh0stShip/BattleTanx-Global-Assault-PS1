typedef union Rect {
    struct {
        short x;
        short y;
        short width;
        short height;
    } area;
    unsigned int words[2];
} Rect;

typedef struct DisplayInterface {
    void *fields00[2];
    int (*dispatch)(void *, void *, int, int);
    void *fields0C[3];
    void *context;
} DisplayInterface;

typedef char Rect_size[(sizeof(Rect) == 8) ? 1 : -1];
typedef char DisplayInterface_size[(sizeof(DisplayInterface) == 0x1C) ? 1 : -1];

extern DisplayInterface *D_800B0C58;
extern unsigned int D_800B0D00[];
extern char D_800C4C30[];
extern void func_8007FADC(char *, Rect *);

int func_8007FCE8(Rect *rect, int low, int high) {
    register unsigned int *packet asm("$3");
    register unsigned int packed asm("$2");
    register unsigned int xy asm("$5");
    register DisplayInterface *interface asm("$7");
    register int size asm("$6");

    func_8007FADC(D_800C4C30, rect);
    if (rect->area.width == 0 || rect->area.height == 0)
        return -1;
    packed = (unsigned int)high << 16;
    packet = D_800B0D00;
    asm("" : "+r"(packet));
    packed |= low & 0xFFFF;
    xy = rect->words[0];
    asm("lui %0,%%hi(D_800B0C58)\n\t"
        "lw %0,%%lo(D_800B0C58)(%0)"
        : "=r"(interface) : "r"(xy) : "memory");
    size = 20;
    asm("" : "+r"(size) : : "memory");
    packet[1] = packed;
    packet[0] = xy;
    asm volatile("" : : : "memory");
    packet[2] = rect->words[1];
    return interface->dispatch(interface->context,
                               (unsigned char *)packet - 8, size, 0);
}
