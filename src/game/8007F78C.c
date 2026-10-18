extern int D_800EC334[];

void func_8007F78C(void) {
    int offset = D_800EC334[3] * D_800EC334[4];

    D_800EC334[3]++;
    D_800EC334[0] = D_800EC334[2] + offset;
    D_800EC334[1] = D_800EC334[0] + D_800EC334[4];
    if (D_800EC334[3] == D_800EC334[5]) {
        D_800EC334[3] = 0;
    }
}
