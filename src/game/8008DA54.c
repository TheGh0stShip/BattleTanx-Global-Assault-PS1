int func_8008DA54(
    int first,
    int second,
    int third,
    int fourth
) {
    return ((first & 3) << 7) |
        ((second & 3) << 5) |
        ((fourth & 0x100) >> 4) |
        ((third & 0x3FF) >> 6) |
        ((fourth & 0x200) << 2);
}
