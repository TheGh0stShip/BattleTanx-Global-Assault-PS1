typedef struct BodyConfig {
    unsigned short kind;
    int mass;
    int drag;
    int friction;
    int max_speed;
    int accel;
    int turn;
} BodyConfig;
typedef struct Body {
    int vx;
    int vy;
    int vz;
    int mass;
    int drag;
    int friction;
    unsigned short kind;
    short heading;
    int speed;
    int max_speed;
    int accel;
    int turn;
    int unk2C;
    int scale;
    short unk34;
    short unk36;
    char pad38[4];
    int forces[4];
    int torques[4];
    unsigned char grounded;
    char pad5D[3];
    int unk60;
} Body;

void func_8001EEE4(Body *body, BodyConfig *config) {
    unsigned short i;

    body->vx = 0;
    body->vy = 0;
    body->vz = 0;
    body->speed = 0;
    body->heading = 0;
    body->unk34 = 0;
    body->unk36 = 0;
    body->unk60 = 0;
    body->scale = 4096;
    for (i = 0; i < 4; i++) {
        body->forces[i] = 0;
        body->torques[i] = 0;
    }
    body->kind = config->kind;
    body->mass = config->mass;
    body->drag = config->drag;
    body->friction = config->friction;
    body->max_speed = config->max_speed;
    body->accel = config->accel;
    body->turn = config->turn;
    body->grounded = 0;
    body->unk2C = 0;
}
