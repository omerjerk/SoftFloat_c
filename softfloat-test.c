#include <stdio.h>

#include "softfloat.h"

int main() {
	int32_t a, b, c;
	a = -10;

	SoftFloat a_sf = int2sf(a, 0);
	printf("Normal fields check for %d:\n", a);
	printf("sign = %d\n", a_sf.sign);
	printf("exp = %d\n", a_sf.exp);
	printf("mant = %lu\n", a_sf.mant);
	printf("========================\n\n");

	b = 15;
	c = -10;
	SoftFloat b_sf = int2sf(b, 0);
	SoftFloat c_sf = int2sf(c, 0);
	a_sf = mul_sf(b_sf, c_sf);
	printf("Multiplication check for %d and %d:\n", b, c);
	printf("sign = %d\n", a_sf.sign);
	printf("exp = %d\n", a_sf.exp);
	printf("mant = %lu\n", a_sf.mant);
	printf("========================\n\n");

	a_sf = div_sf(b_sf, c_sf);
	printf("Division check for %d by %d:\n", b, c);
	printf("sign = %d\n", a_sf.sign);
	printf("exp = %d\n", a_sf.exp);
	printf("mant = %lu\n", a_sf.mant);
	printf("========================\n\n");
}
