extern int D_800EAC1C;
extern int D_800DE30C;
extern int func_80070900(unsigned int *obj);

void func_80070CC0(unsigned int *obj, int *done) {
    int result;

    switch (obj[2]) {
    case 10:
    case 11:
        result = func_80070900(obj);
        if (result) {
            D_800EAC1C = 0;
        }
        break;
    default:
        result = 1;
        break;
    }
    obj[6] += D_800DE30C;
    if (result) {
        *done = 1;
    } else {
        *done = 0;
    }
}
