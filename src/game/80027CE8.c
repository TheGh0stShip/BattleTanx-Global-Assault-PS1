typedef struct {
    char pad0[8];
    int x;
    int y;
    int z;
    char pad14[2];
    signed char health;
    unsigned char slot;
} Crate;

typedef struct {
    int busy;
    int pad4[2];
    int damage;
} Data;

typedef struct {
    unsigned char valid;
    char pad1[3];
    int x;
    int z;
} Out;

extern void func_800276D8(Crate *, int, Data *, Out *);
extern void func_80027858(Crate *, int, Data *, Out *);

void func_80027CE8(Crate *self, int arg, unsigned int cmd, Data *data, Out *out) {
    switch (cmd) {
    case 0:
        func_800276D8(self, arg, data, out);
        break;
    case 5:
        if (data->busy == 0) {
            int slot = self->slot;

            if (slot < 6) {
                if (slot >= 0) {
                    out->valid = 1;
                    out->x = self->x;
                    out->z = self->z;
                }
            }
        }
        break;
    case 6:
        func_80027858(self, arg, data, out);
        break;
    case 3:
        if (self->health < data->damage) {
            self->health = 0;
        } else {
            self->health -= data->damage;
        }
        break;
    }
}
