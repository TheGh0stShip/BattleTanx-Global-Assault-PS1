typedef struct { char pad[13]; unsigned char r, g, b; } FogInfo;
typedef struct { char pad[436]; FogInfo fog; } Level;
extern Level *D_800D2FE4;
extern short D_800D5B88;
void func_8003BCBC(int, int, int);
void func_8008B968(int, int);

void func_8003E9A8(int dist, short ratio) {
    FogInfo *fog = &D_800D2FE4->fog;

    if (dist > 28000) {
        dist = 28000;
    }
    func_8003BCBC(dist - dist * ratio / 4096, dist, (fog->b << 16) + (fog->g << 8) | fog->r);
    func_8008B968(200, dist);
    D_800D5B88 = dist;
}
