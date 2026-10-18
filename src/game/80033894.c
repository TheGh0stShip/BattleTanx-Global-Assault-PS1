struct EffectNode {
    unsigned char pad_00[0x1C];
    struct EffectNode *next;
};

struct EffectList {
    unsigned char pad_00[0xA4];
    struct EffectNode *head;
};

void func_800324C8(struct EffectNode *effect, int value);

void func_80033894(struct EffectList *list, int value) {
    while (list->head != 0) {
        struct EffectNode *effect = list->head;

        list->head = effect->next;
        func_800324C8(effect, value);
    }
}
