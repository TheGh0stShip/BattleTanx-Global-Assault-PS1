typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct PathNode {
    u8 type;
    u8 pad_01;
    u16 next;
    u8 pad_04[8];
    u16 left;
    u16 right;
    u8 pad_10[2];
    u8 mark;
} PathNode;

typedef struct PathList {
    PathNode *current;
    u8 pad_04[2];
    u16 field_06;
    u8 pad_08[2];
    u16 head;
    u8 pad_0C[8];
    u16 field_14;
    u16 field_16;
    u32 field_18;
} PathList;

typedef struct PathEntity {
    u8 pad_000[0xF8];
    PathList list;
    u8 pad_114[0x36];
    u16 field_14A;
    u8 pad_14C[0x34];
    u32 flags_180;
} PathEntity;

extern PathNode *func_8004A794(unsigned int id);
extern void func_8004A160(void *value, int mode);

void func_8004C17C(PathEntity *entity) {
    register PathEntity *entity_reg asm("$19") = entity;
    register PathList *list asm("$16");
    register unsigned int id asm("$17");
    register unsigned int previous asm("$18");
    PathNode *node;

    {
        register PathList *initial asm("$2") = &entity_reg->list;
        register PathNode *current asm("$4") = initial->current;

        if (current == 0) {
            id = initial->head;
        } else {
            id = current->next;
        }
    }

    node = func_8004A794(id);
    list = &entity_reg->list;
    if (node == 0) {
        return;
    }

loop:
    previous = id;
    id = node->next;
    node = func_8004A794(id);
    if (node == 0) {
        return;
    }

    {
        register u8 type asm("$5") = node->type;
        register unsigned int previous_id asm("$4") = (u16)previous;

        if (type != 2) {
            goto loop;
        }
        if (node->left == previous_id) {
            node->mark = 1;
            goto loop;
        }
        if (node->right == previous_id) {
            node->mark = type;
            goto loop;
        }
    }

cleanup:
    {
        register void *value asm("$4") = (u8 *)entity_reg + 0xFC;
        register int mode asm("$5") = 0;

        __asm__ volatile("" : "+r"(value), "+r"(mode));
        entity_reg->field_14A = 0;
        func_8004A160(value, mode);
    }
    list->field_06 = 0;
    entity_reg->list.current = 0;
    list->head = 0;
    list->field_14 = 0;
    list->field_16 = 0;
    list->field_18 = 0;
    entity_reg->flags_180 &= ~0x180;
}
