typedef struct PadPort PadPort;
struct PadPort {
    char pad00[12];
    PadPort *children;
    PadPort *volatile parent;
    char pad14[28];
    unsigned char *out;
    char pad34[2];
    unsigned char locked;
    volatile unsigned char busy;
    char pad38[4];
    unsigned char *in;
    char pad40[4];
    unsigned char mode;
    char pad45[1];
    unsigned char state;
    char pad47[2];
    unsigned char failed;
    unsigned char retry;
    char pad4B[1];
    int frames;
    char pad50[152];
    unsigned char kind;
    char padE9[7];
};

extern void (*D_800B8C78)(PadPort *);

void func_800A3698(PadPort *self, int arg)
{
    PadPort *port = self;
    int kind;
    int i;
    PadPort *child;

    kind = port->in[0] >> 4;
    if (port->kind != 8) {
        if (kind == 8) {
            port->kind = kind;
            port->out[0] = 0xFF;
            port->out[1] = 0x80;
            port->mode = 2;
        }
    }
    if (port->kind == 8) {
        child = port->children;
        for (i = 0; i < 4; i++) {
            func_800A3698(child++, -1);
        }
    }
    child = port->parent->children;
    if (port->children == 0) {
        goto idle;
    }
    if (port->locked == 0) {
        if (child->busy != 0) {
            goto busy;
        }
        child++;
        if (child->busy != 0) {
            goto busy;
        }
        child++;
        if (child->busy != 0) {
            goto busy;
        }
        child++;
        if (child->busy != 0) {
            goto busy;
        }
    }
    child = port->parent->children;
    if (((volatile PadPort *)port)->children == 0) {
    idle:
        if (port->busy != 0) {
            goto ready;
        }
        if (port->parent->locked != 0) {
            goto busy;
        }
        if (child->busy != 0) {
            goto busy;
        }
        child++;
        if (child->busy != 0) {
            goto busy;
        }
        child++;
        if (child->busy != 0) {
            goto busy;
        }
        child++;
        if (child->busy != 0) {
        busy:
            if (port->retry == 0) {
                port->retry = 1;
            }
            return;
        }
    }
ready:
    port->frames++;
    if (port->state != 0) {
        if (port->state == 1) {
            if (port->retry < 2) {
                if (port->parent->kind != 8) {
                    port->retry++;
                    return;
                }
            }
            port->failed = 2;
            port->state = 0xFF;
            return;
        }
        if (port->retry < 4) {
            port->retry++;
            return;
        }
    }
    if (port->failed != 0) {
        port->out[0] = 0xFF;
        port->out[1] = 0;
        port->kind = 0;
        port->mode = 0;
        D_800B8C78(port);
    }
    if (kind == 0) {
        port->kind = 0;
        port->out[1] = 0;
    }
    if (kind == 8 && port->children != 0) {
        port->kind = kind;
        port->out[1] = 0x80;
    }
}
