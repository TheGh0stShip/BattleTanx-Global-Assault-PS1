typedef struct VoiceAttr {
    unsigned int voice_mask;
} VoiceAttr;

extern void func_80090E10(VoiceAttr *attributes);
extern void func_800907C4(int on, unsigned int voice_mask);

void func_80090794(VoiceAttr *attributes) {
    func_80090E10(attributes);
    func_800907C4(1, attributes->voice_mask);
}
