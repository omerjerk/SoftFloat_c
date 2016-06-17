#include <stdio.h>

#include "softfloat.h"

int main() {
	int32_t a = 10;
	
	SoftFloat a_sf = int2sf(a);
	printf("sign = %d\n", a_sf.sign);
	printf("exp = %d\n", a_sf.exp);
	printf("mant = %d\n", a_sf.mant);
}
