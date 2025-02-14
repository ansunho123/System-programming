#include <stdio.h>
#include "header.h"

/* binary로 출력 */

void print_binary_char(unsigned char a) {
	int i;
	unsigned char p;
	p = 0x80; 
	printf("[");
	 for (i = 0; i < 8; i++) {
	  if (a & p) printf("1");
	  else printf("0");
	  p = p >> 1;
     }
        printf("]");
        /* char의 경우 1 byte (8 bits)이므로 0x80 (10000000) 부터 */
 }


void print_binary_short(unsigned short a) {
	int i;
	unsigned short p;
	p = 0x8000; 
	printf("[");
	 for (i = 0; i < 16; i++) {
	  if (a & p) printf("1");
	  else printf("0");
	  p = p >> 1;
        }
	printf("]");
	/* short의 경우 2 byte (16 bits)이므로 0x8000 (10000000_00000000) 부터 */
}



/*binary로 floating frac 출력 IEEE 32bit 기준*/

void print_binary_frac(unsigned int a) {
	int i;
	unsigned int p; /*floating도 4byte라 상관 x */
	p = 0x400000; /*frac 출력 23bit이므로 0x400000 */
	printf("[");
	 for (i = 0; i < 23; i++) {
	  if (a & p) printf("1");
	  else printf("0");
	  p = p >> 1;
	}
	printf("]");
}





/* practice 1  같은 변수를 signed와 unsigned로 출력하여 결과 비교*/

void example_1() {
   /* unsigned vs. signed */
   printf ("[Example 1] Unsigned vs. Signed\n");
   
   unsigned char zero = 0;
   
   for (unsigned char i = 1; i != zero; i++) {
    printf ("bit-level i = ");
    print_binary_char(i);
    printf (", unsigned i = %u, signed i = %d\n", i, (char)i);
   }
}



/* practice 2 unsigned addition에서 overflow 영향 확인 */

void example_2() { 
   /* unsigned addition */
   printf ("[Example 2] Unsigned addition\n");
   unsigned char uc = 140;
   unsigned char ud = 220;
   unsigned char ue = uc + ud; /* overflow result */
   unsigned short ushe = (unsigned short) uc + ud; /* true result */

   printf ("unsigned char uc = %u ", uc);
   print_binary_char(uc);
   printf (", unsigned char ud = %u ", ud);
   print_binary_char(ud);
   printf ("\n");
   printf ("unsigned char ue = uc + ud = %u ", ue);
   print_binary_char(ue);
   printf (", real result = %u ", ushe);
   print_binary_short(ushe);
   printf ("\n");
}



/* practice 3  intel 기준 Little endian 1byte씩 확인 */

void show_bytes(pointer start, size_t len) {
   size_t i;
   for (i = 0; i < len; i++){
    printf("%p \t 0x%.2x\n", start+i, start[i]);
   }
}

void example_3() { /* data representation */
   printf ("[Example 3] Data representation\n");
   int i = 15213;
   printf("int i = %d [%x]\n", i, i);
   show_bytes((pointer) &i, sizeof(int));
}




/* pratice 4  floating point data representation 확인 */

void analyze_float(pointer start) {
    unsigned int exp;
    unsigned int frac;
    unsigned int sign;
    sign = start[3] >> 7;
    exp = ((start[3] & 0x7f) << 1) + (start[2] >> 7);
    frac = ((unsigned int)(start[2] & 0x7f) << 16) + ((unsigned int) start[1] << 8) + start[0];
    printf("sign = %u, exp = %u, frac = ", sign, exp);
    print_binary_frac(frac);
    printf("\n");
}


void example_4() { /* data representation */
   printf ("[Example 4] Floating point\n");
   float f = 14;
   printf("float f = %f\n", f);
   show_bytes((pointer) &f, sizeof(float));
   analyze_float((pointer) &f);

}
