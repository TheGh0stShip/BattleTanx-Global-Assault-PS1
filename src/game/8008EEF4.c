extern int D_800EEC34[];

int func_8008EEF4(int value) {
    int result = 0;
    if (value == D_800EEC34[107]) {
        result = D_800EEC34[15] - D_800EEC34[106];
        if (result < 0) {
            result = 0;
        }
    }
    return result;
}
