typedef struct {
    unsigned char size;
    unsigned char unk1;
    unsigned char count;
    unsigned char unk3[4];
    unsigned char code;
} Packet;

typedef struct {
    Packet *start;
    Packet *end;
} PacketList;

extern PacketList D_800AD9EC;

void func_800684C0(void) {
    Packet *packet;
    volatile unsigned char *child;
    int total;
    int i;
    int c;

    total = 0;
    for (packet = D_800AD9EC.start; packet != D_800AD9EC.end;
         packet = (Packet *)((int *)packet + packet->size)) {
        if (packet->count == 0) {
            if (packet->code == 16) {}
            c = packet->code & ~3;
            if (c == 56) {}
            switch (c) {
            case 64:
                total++;
                if (total >= 511) {
                    break;
                }
            case 16:
            case 32:
            case 36:
            case 40:
            case 44:
            case 48:
            case 52:
            case 56:
            case 60:
            case 80:
            case 164:
            case 180:
            case 224:
            case 232:
                total++;
                break;
            case 236:
            case 240:
            case 244:
            case 248:
            case 252:
                break;
            }
        } else {
            switch (packet->code & ~3) {
            case 64:
            case 80:
                i = packet->count;
                total++;
            count_loop:
                if (i > 0 && total < 512) {
                    total++;
                    i--;
                    goto count_loop;
                }
                continue;
            case 60:
                child = (unsigned char *)packet + 44;
                break;
            case 44:
                child = (unsigned char *)packet + 32;
                break;
            case 56:
                child = (unsigned char *)packet + 40;
                break;
            case 40:
                child = (unsigned char *)packet + 28;
                break;
            default:
                continue;
            }
            total++;
            for (i = packet->count; i > 0; i--) {
                if (total >= 512) {
                    break;
                }
                total++;
                child += *child * 4;
            }
        }
    }
}
