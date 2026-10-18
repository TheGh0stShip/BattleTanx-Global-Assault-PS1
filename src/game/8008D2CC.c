typedef unsigned char u8;
typedef short s16;

typedef struct Packet {
    struct Packet *next;
    u8 pad_04[4];
    s16 first;
    s16 second;
    s16 third;
    s16 fourth;
} Packet;

typedef struct Queue {
    Packet *head;
} Queue;

extern void func_8008D1B8(Queue *queue, Packet *packet);

Packet *func_8008D2CC(
    Queue *queue,
    int first,
    int second,
    int third,
    int fourth
) {
    Packet *packet = queue->head;
    queue->head = packet->next;
    packet->first = first;
    packet->second = second;
    packet->third = third;
    packet->fourth = fourth;
    func_8008D1B8(queue, packet);
    return packet;
}
