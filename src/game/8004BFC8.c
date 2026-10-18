typedef unsigned char u8;
typedef unsigned short u16;
typedef signed int s32;

typedef struct PathNode {
    u8 type;
    u8 pad_01;
    u16 link;
    s32 x;
    s32 z;
} PathNode;

typedef struct PathEntity {
    u8 pad_000[0x11C];
    struct {
        s32 x;
        s32 pad;
        s32 z;
    } start;
    struct {
        s32 x;
        s32 pad;
        s32 z;
    } goal;
} PathEntity;

typedef struct RouteItem {
    u8 pad_00[4];
    s32 key;
    s32 distance;
} RouteItem;

extern PathNode *func_8004A794(u16 link);
extern s32 func_8004BA6C(PathEntity *entity, PathNode *node);
extern s32 func_800495D8(s32 *left, s32 *right);

void func_8004BFC8(PathEntity *entity, RouteItem *item) {
    register PathEntity *entity_reg asm("$18") = entity;
    register RouteItem *item_reg asm("$17") = item;
    register s32 *position asm("$16");
    register int position_type asm("$19");
    PathNode *node;

    item_reg->key = func_8004BA6C(entity_reg, (PathNode *)item_reg);
    node = (PathNode *)item_reg;
    position = &entity_reg->start.x;
    position_type = 3;
    __asm__ volatile("" : "+r"(position_type));

loop:
    if (node == 0) {
        goto done;
    }
    if (node->type == position_type) {
        goto found;
    }
    node = func_8004A794(node->link);
    goto loop;

found:
    position = &node->x;

done:
    item_reg->distance = func_800495D8(position, &entity_reg->goal.x);
}
