typedef unsigned char u8;
typedef unsigned short u16;

typedef struct PoolNode PoolNode;

struct PoolNode {
    u8 state;
    u8 pad_01;
    u16 value;
    PoolNode *next;
    u16 index;
    u8 pad_0A[0x12];
};

typedef struct ObjectPool {
    PoolNode nodes[0x800];
    PoolNode *head;
    u16 field_E004;
    u16 field_E006;
    u16 field_E008;
    u16 field_E00A;
} ObjectPool;

typedef char PoolNode_size[(sizeof(PoolNode) == 0x1C) ? 1 : -1];
typedef char ObjectPool_nodes_size
    [(sizeof(((ObjectPool *)0)->nodes) == 0xE000) ? 1 : -1];

void func_80049F84(ObjectPool *pool) {
    u16 index;
    u8 available;

    index = 1;
    available = index;
    pool->nodes[0].state = 0;
    pool->nodes[0].value = 0;
    pool->head = &pool->nodes[1];
    for (; index < 0x7FF; index++) {
        pool->nodes[index].index = index;
        pool->nodes[index].next = &pool->nodes[index + 1];
        pool->nodes[index].state = available;
        pool->nodes[index].value = 0;
    }
    pool->nodes[index].next = 0;
    pool->nodes[index].index = index;
    pool->nodes[index].state = 1;
    pool->nodes[index].value = 0;
    pool->field_E006 = 0x6E;
    pool->field_E008 = 0x6E;
    pool->field_E004 = 0;
    pool->field_E00A = 0x10;
}
