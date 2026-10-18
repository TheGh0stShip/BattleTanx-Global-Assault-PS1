int func_8004D970(int type, int distance) {
    switch (type) {
    case 1:
        return 2;
    case 2:
        return 3;
    case 3:
        return 4;
    case 10:
        return 9;
    case 14:
        return distance <= 0x3E8000 ? 12 : 0;
    case 16:
        return distance <= 0x7D0000 ? 14 : 0;
    default:
        return 0;
    }
}
