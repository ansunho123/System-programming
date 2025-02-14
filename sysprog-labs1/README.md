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
| [header.h](https://github.com/ansunho123/System-programming/blob/main/sysprog-labs1/header.h)  | 4개의 example 함수 및 관련 함수 선언 |
| [func.c](https://github.com/ansunho123/System-programming/blob/main/sysprog-labs1/func.c) | 4개의 example 함수 및 관련 함수 정의 |


## 실습 결과
실행 결과는 [`sysprog-practice_1.out`](https://github.com/your-repo/sysprog-practice_1.out)에 저장됩니다.


-------------------------
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
