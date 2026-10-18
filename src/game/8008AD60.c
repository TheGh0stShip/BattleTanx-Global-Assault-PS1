extern int func_8008AD9C(unsigned int angle);

int func_8008AD60(int angle)
{
    int result;

    if (angle >= 0) {
        result = func_8008AD9C(angle & 0xFFF);
    } else {
        result = -func_8008AD9C((-angle) & 0xFFF);
    }
    return result;
}
