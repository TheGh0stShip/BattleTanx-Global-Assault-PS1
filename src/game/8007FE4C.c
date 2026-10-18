typedef struct DisplayInterface {
    void *unknown_00[5];
    void (*submit)(void *data, unsigned int option);
    void *unknown_18[9];
    void (*apply)(void *value);
} DisplayInterface;

typedef struct DisplayPacket {
    unsigned char header[4];
    unsigned char data[1];
} DisplayPacket;

extern DisplayInterface *D_800B0C58_apply;
extern DisplayInterface *D_800B0C58_submit;

void func_8007FE4C(DisplayPacket *packet)
{
    unsigned int option = packet->header[3];

    D_800B0C58_apply->apply(0);
    D_800B0C58_submit->submit(packet->data, option);
}
