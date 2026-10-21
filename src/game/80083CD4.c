signed char func_80083CD4(signed char v, signed char center, signed char lo, signed char hi, signed char dead) {
    int d = v - center;
    int den;

    if (d < 0) {
        if (-d > dead) {
            den = (lo - center) + dead;
            d = -((d + dead) * 128) / den;
            if (d < -128) {
                d = -128;
            } else if (d > 0) {
                d = 0;
            }
        } else {
            d = 0;
        }
    } else if (d > 0) {
        if (d > dead) {
            den = (hi - center) - dead;
            d = ((d - dead) * 127) / den;
            if (d >= 128) {
                d = 127;
            } else if (d < 0) {
                d = 0;
            }
        } else {
            d = 0;
        }
    }
    return d;
}
