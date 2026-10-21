typedef struct {
    volatile unsigned char ready;
    volatile unsigned char opened;
    volatile unsigned char busy;
    char pad3[0x3B];
    unsigned short sectorsPerFrame;
    char pad40[8];
    unsigned short width;
    unsigned short height;
} MovieStream;

typedef struct {
    int pad0[2];
    int width;
    int height;
    int depth;
    int rate;
    int active;
    int lastFrame;
    int frameCount;
    int imageSize;
    int imageSizeFixed;
    int ringBase;
    int bufferBase;
    int pad34[6];
    int ringSize;
    int frameBytes;
    int pad54[2];
    int startSector;
    int endSector;
    int position;
    char *fileName;
} MovieInfo;

typedef struct {
    unsigned char minute, second, sector, track;
} MovieCdLoc;

extern MovieStream D_800EEF0C;
extern void func_8008AA48(void *dst, int value, int size);
extern void func_800919D8(void);
extern void func_80091984(void);
extern int func_800982B0(char *name, unsigned int *pos, unsigned int *size);
extern void func_800916F4(void);
extern void func_8009759C(int sector, MovieCdLoc *loc);
extern int func_800973AC(int command, void *param, void *result);
extern int func_8009702C(void);
extern void *func_8009162C(void *callback);
extern void *func_80091618(void *callback);
extern void func_8009166C(void);
extern int func_8009278C(MovieInfo *info, int fixedWidth);
extern void func_800927E4(void);
extern void func_800927C8(void);

int func_80092830(MovieInfo *info, char *name, int depth) {
    int ok = 0;
    unsigned int start = 0;
    unsigned int end;
    unsigned int pos, size;
    MovieCdLoc loc;
    int mode;
    int failed;
    void *oldSync, *oldReady;
    MovieStream *s;

    func_8008AA48(info, 0, sizeof(MovieInfo));
    func_800919D8();
    func_80091984();
    D_800EEF0C.ready = 0;
    D_800EEF0C.opened = 0;
    end = 0;
    if (D_800EEF0C.busy == 0 && func_800982B0(name, &pos, &size)) {
        start = pos >> 11;
        end = start + ((size + 2047) >> 11);
        func_800916F4();
        *(int *)0x800C60BC = 1;
        func_8009759C(start, &loc);
        if (func_800973AC(2, &loc, 0)) {
            failed = func_800973AC(21, 0, 0) == 0;
            if (!failed) {
                int status = func_8009702C();

                mode = status & 0x80;
                if (mode != status) {
                    failed = func_800973AC(14, &mode, 0) == 0;
                }
                if (!failed) {
                    oldSync = func_8009162C(func_800927E4);
                    oldReady = func_80091618(func_800927C8);
                    failed = func_800973AC(6, &loc, 0) == 0;
                    if (!failed) {
                        while (D_800EEF0C.ready == 0) {
                        }
                    }
                    func_80091618(oldReady);
                    func_8009162C(oldSync);
                    if (!failed) {
                        func_8009166C();
                    }
                }
            }
        }
    }
    s = &D_800EEF0C;
    if (s->opened != 0) {
        unsigned int frames = s->sectorsPerFrame;
        unsigned int count;

        if (frames == 0) {
            frames = 1;
        }
        count = (end - start + frames - 1) / frames;
        info->width = s->width;
        info->height = s->height;
        info->depth = depth;
        info->rate = 60;
        info->active = 1;
        info->frameCount = count + 1;
        info->lastFrame = count - 2;
        info->ringBase = 0x11000;
        info->frameBytes = frames << 11;
        info->ringSize = (frames << 12) + (frames << 11);
        info->startSector = start;
        info->endSector = end;
        info->position = 0;
        info->fileName = name;
        info->imageSize = func_8009278C(info, 0);
        info->imageSizeFixed = func_8009278C(info, 1);
        info->bufferBase = ((info->imageSize + info->imageSizeFixed) << 1) + 0x11000;
        ok = 1;
    }
    D_800EEF0C.ready = 0;
    D_800EEF0C.opened = 0;
    return ok;
}
