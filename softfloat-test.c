#include <stdio.h>

#include "softfloat.h"

int main() {
	int32_t a, b, c;
	a = 10;
	
	SoftFloat a_sf = int2sf(a);
	printf("Normal fields check for %d\n", a);
	printf("sign = %d\n", a_sf.sign);
	printf("exp = %d\n", a_sf.exp);
	printf("mant = %d\n", a_sf.mant);
	printf("========================\n\n");

	b = 15;
	c = -10;
	SoftFloat b_sf = int2sf(b);
	SoftFloat c_sf = int2sf(c);
	SoftFloat prod = mul_sf(b_sf, c_sf);
	printf("Multiplication check for %d and %d\n", b, c);
	printf("sign = %d\n", prod.sign);
	printf("exp = %d\n", prod.exp);
	printf("mant = %d\n", prod.mant);
	printf("========================\n\n");
}