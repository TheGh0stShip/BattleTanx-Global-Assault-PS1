extern int D_800EDF08[];

int func_80083B18(int value) {
    int previous = D_800EDF08[27];
    D_800EDF08[27] = value;
    return previous;
}
