typedef struct { unsigned char pad[0x46]; unsigned char kind; unsigned char arg47; unsigned char pad2[0xE4 - 0x48]; unsigned char argE4; } Port;
void func_8009F508(Port *);
void func_8009F51C(Port *, int);
void func_8009F55C(Port *, int);

void func_8009EDA4(Port *p)
{
    switch (p->kind) {
    case 2:
        func_8009F508(p);
        break;
    case 3:
        func_8009F51C(p, p->argE4);
        break;
    case 4:
        func_8009F55C(p, p->arg47);
        break;
    }
}
