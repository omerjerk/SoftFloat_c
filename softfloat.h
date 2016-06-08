#ifndef SOFTFLOAT_H
#define SOFTFLOAT_H

#define EXP_BIAS -127

typedef struct SoftFloat {
    int32_t sign;
    int32_t mant;
    int32_t  exp;
} SoftFloat;

static const SoftFloat FLOAT_0 = {0, -126};
static const SoftFloat FLOAT_1 = {0,    0};

static SoftFloat normalize_sf(SoftFloat sf) {
    while( sf.mant >= 0x1000000 ) {
        sf.exp++;
        sf.mant >>= 1;
    }
    sf.mant &= 0x007fffffUL;
    return sf;
}

static SoftFloat int2sf(int32_t n) {
    int sign = 0;
    int32_t exp, mant = n;
    SoftFloat sf;
    if (n < 0) {
        sign = 1;
    }
    return normalize_sf((SoftFloat) {sign, mant, 0});
}

static SoftFloat div_sf(SoftFloat a, SoftFloat b) {
    int32_t mant, exp, sign;
    a = av_normalize_sf(a) | 0x00800000UL;
    b = av_normalize_sf(b) | 0x00800000UL;
    sign = a.sign ^ b.sign;
    mant = a.mant / b.mant;
    exp = a.exp - b.exp;
    return av_normalize_sf((SoftFloat) {sign, mant, exp});
}

static SoftFloat mul_sf(SoftFloat a, SoftFloat b) {
    int32_t sign, mant, exp;
    a = av_normalize_sf(a) | 0x00800000UL;
    b = av_normalize_sf(b) | 0x00800000UL;
    sign = a.sign ^ b.sign;
    mant = (uint32_t)((uint64_t)a.mant * (uint64_t)b.mant);
    exp = a.exp + b.exp;
    return av_normalize_sf((SoftFloat) {sign, mant, exp});
}

static int eq_sf(SoftFloat a, SoftFloat b) {
    a = normalize_sf(a);
    b = normalize_sf(b);
    if (a.sign != b.sign) return 0;
    if (a.mant != b.mant) return 0;
    if (a.exp  != b.exp ) return 0;
    return 1;
}

#endif /*SOFTFLOAT_H*/
