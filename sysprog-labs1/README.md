# 시스템 프로그래밍 실습 1

## 실습 내용
이번 실습에서는 총 4개의 함수를 통해 데이터 표현(data representation)에 대해 실습합니다.

### 실습할 함수
- `example_1()`: unsigned vs. signed
- `example_2()`: unsigned addition
- `example_3()`: data representation (little endian)
- `example_4()`: data representation (floating point)

## 프로젝트 파일 구성
본 프로젝트는 총 3개의 파일로 구성됩니다.

| 파일명       | 설명 |
|-------------|--------------------------------------------------|
| [main.c](https://github.com/ansunho123/System-programming/blob/main/sysprog-labs1/main.c)    | 각 example 함수를 호출하는 main 함수 |
| [header.h](https://github.com/ansunho123/System-programming/blob/main/sysprog-labs1/header.h)  | 4개의 example 함수 및 관련 함수(print_binary) 선언 |
| [func.c](https://github.com/ansunho123/System-programming/blob/main/sysprog-labs1/func.c) | 4개의 example 함수 및 관련 함수(print_binary) 정의 |



# 실습 결과
실행 결과는 [`sysprog-practice_1.out`](https://github.com/your-repo/sysprog-practice_1.out)에 저장됩니다.


**********************
### Example 1 코드 및 결과
```c
/* practice 1  - unsigned vs. signed 출력 비교 */
void example_1() {
   /* unsigned vs. signed */
   printf("[Example 1] Unsigned vs. Signed\n");
   
   unsigned char zero = 0;
   for (unsigned char i = 1; i != zero; i++) {
       printf("bit-level i = ");
       print_binary_char(i);
       printf(", unsigned i = %u, signed i = %d\n", i, (char)i);
   }
}
```

#### Example 1 실행 결과 (일부)
```
[Example 1] Unsigned vs. Signed
bit-level i = [00000001], unsigned i = 1, signed i = 1
bit-level i = [00000010], unsigned i = 2, signed i = 2
bit-level i = [00000011], unsigned i = 3, signed i = 3
bit-level i = [00000100], unsigned i = 4, signed i = 4
bit-level i = [00000101], unsigned i = 5, signed i = 5
bit-level i = [00000110], unsigned i = 6, signed i = 6
bit-level i = [00000111], unsigned i = 7, signed i = 7
bit-level i = [00001000], unsigned i = 8, signed i = 8
bit-level i = [00001001], unsigned i = 9, signed i = 9
bit-level i = [00001010], unsigned i = 10, signed i = 10
bit-level i = [00001011], unsigned i = 11, signed i = 11
bit-level i = [00001100], unsigned i = 12, signed i = 12
...
```
------------------------
### Example 2 코드 및 결과
```c
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
```

#### Example 2 실행 결과
```
[Example 2] Unsigned addition
unsigned char uc = 140 [10001100], unsigned char ud = 220 [11011100]
unsigned char ue = uc + ud = 104 [01101000], real result = 360 [0000000101101000]
```
--------------

### Example 3 코드 및 결과

```c
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
```
#### Example 3 실행 결과
```
[Example 3] Data representation
int i = 15213 [3b6d]
0x16d2e746c 	 0x6d
0x16d2e746d 	 0x3b
0x16d2e746e 	 0x00
0x16d2e746f 	 0x00
```


### Example 3 구현 이슈

* len = 4로 반환 (sizeof(int))
* size_t 사용 이유
> 항상 0 이상
>>시스템 마다 크기가 달라서 좋음
>>>int i로 하면 매번 casting unsigned vs signed 비교 성능 저하
* pointer -> unsigned char* : 1bytes
* start + 1 : start + 1byte
  
---------------
### Example 4 코드 및 결과

```c
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
```

#### Example 4 실행 결과
```
[Example 4] Floating point
float f = 14.000000
0x16d2e746c 	 0x00
0x16d2e746d 	 0x00
0x16d2e746e 	 0x60
0x16d2e746f 	 0x41
sign = 0, exp = 130, frac = [11000000000000000000000]
```

### Example 4 구현 이슈
* pointer를 array처럼 사용. start[0] : 최하위 1byte 의미
* exp 8bit >> start[3] 하위 7비트 + start[2] 상위 1
* frac  23bit >> start[2] 하위 7비트 + start[1] + start[0] 




