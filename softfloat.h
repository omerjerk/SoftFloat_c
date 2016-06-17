#ifndef SOFTFLOAT_H
#define SOFTFLOAT_H

#include <stdint.h>

#define EXP_BIAS -127
#define MANT_BITS 23

typedef struct SoftFloat {
    int32_t sign;
    uint32_t mant;
    int32_t  exp;
} SoftFloat;

static const SoftFloat FLOAT_0 = {0, 0, -126};
static const SoftFloat FLOAT_1 = {0, 0,    0};

static SoftFloat normalize_sf(SoftFloat sf) {
    while( sf.mant >= 0x1000000UL ) {
        sf.exp++;
        sf.mant >>= 1;
    }
    sf.mant &= 0x007fffffUL;
    return sf;
}

static SoftFloat int2sf(int32_t n, int e) {
    int sign = 0;
    int32_t exp;
    uint32_t mant;
    SoftFloat sf;

    if (n < 0) {
        sign = 1;
        n *= -1;
    }
    mant = n << 23; //Keep mant in a 64-bit integer may be ?
    return normalize_sf((SoftFloat) {sign, mant, 0 + e});
}

static int sf2int(SoftFloat a) {
    if(a.exp >= 0) return a.mant <<  a.exp ;
    else           return a.mant >>(-a.exp);
}

static SoftFloat div_sf(SoftFloat a, SoftFloat b) {
    //Or should we rather convert it into a normal float and perform the division ?
    int32_t mant, exp, sign;
    a = normalize_sf(a);
    b = normalize_sf(b);
    sign = a.sign ^ b.sign;
    mant = ((((uint64_t) (a.mant | 0x00800000UL)) << MANT_BITS) / (b.mant| 0x00800000UL));
    exp = a.exp - b.exp;
    return normalize_sf((SoftFloat) {sign, mant, exp});
}

static SoftFloat mul_sf(SoftFloat a, SoftFloat b) {
    int32_t sign, mant, exp;
    a = normalize_sf(a);
    b = normalize_sf(b);
    sign = a.sign ^ b.sign;
    mant = (uint32_t) (((uint64_t)(a.mant|0x00800000UL) * (uint64_t)(b.mant|0x00800000UL))>>MANT_BITS);
    exp = a.exp + b.exp;
    return normalize_sf((SoftFloat) {sign, mant, exp});
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
