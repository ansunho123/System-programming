
# 시스템 프로그래밍 실습 3

## 실습 내용
- Linking 전 symbol 테이블, relocation 내용 확인
- Static linking
- Library interpositioning

## 프로젝트 파일 구성
```
example1/
  ├── main.c
  ├── sum.c
example2/
  ├── main2.c
  ├── addvec.c
  ├── multvec.c
  ├── libvector.a
example3/
  ├── main3.c
  ├── malloc.h
  ├── mymalloc.c
```

---

## 실습 과정

### Example 1

#### main.c
```c
int sum(int *a, int n);

int array[2] = {1, 2};

int main()
{
    int val = sum(array, 2);
    return val;
}
```

#### sum.c
```c
int sum(int *a, int n)
{
    int i, s = 0;
    for (i = 0; i < n; i++)
    {
        s += a[i];
    }
    return s;
}
```

### Linking 제외하고 Compile하기
```sh
gcc -O -c main.c sum.c
```

### objdump를 사용하여 main.o 파일 확인
```sh
objdump -D -t -r main.o > objdump_main
vim objdump_main
```
- **옵션 설명**
  - `-D` : 모든 section의 assembler 내용 출력 (disassembling)
  - `-t` : symbol table 내용 출력
  - `-r` : relocation 내용 출력

> **주의:**
> - 사용자의 환경이 macOS이므로, ELF 포맷이 아닌 Mach-O 형식으로 objdump 결과가 다를 수 있음.
> - objdump_main의 내용을 사진으로 첨부하여 분석.

#### 사진 첨부 및 설명
![Linking 전 symbol 테이블 및 relocation 내용](https://github.com/ansunho123/System-programming/blob/main/sysprog-labs3/images/linking%20%E1%84%83%E1%85%AC%E1%84%80%E1%85%B5%E1%84%8C%E1%85%A5%E1%86%AB.jpeg)

### Linking 및 실행 파일 확인
```sh
gcc -o ex4_1 main.o sum.o
objdump -D ex4_1 > objdump_ex4_1
vim objdump_ex4_1
```

#### 사진 첨부 및 설명
(사진 첨부 후, 해당 내용을 설명)

---

## Example 2

#### main2.c
```c
#include <stdio.h>
#include "vector.h"

int x[2] = {1, 2};
int y[2] = {3, 4};
int z[2];

int main()
{
    addvec(x, y, z, 2);
    printf("z = [% d % d]\n", z[0], z[1]);
    return 0;
}
```

#### vector.h
```c
void addvec(int *x, int *y, int *z, int n);
void multvec(int *x, int *y, int *z, int n);
```

#### addvec.c
```c
void addvec(int *x, int *y, int *z, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        z[i] = x[i] + y[i];
    }
}
```

#### multvec.c
```c
void multvec(int *x, int *y, int *z, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        z[i] = x[i] * y[i];
    }
}
```

### 사진 첨부
(사진을 추가하고 설명 작성)

### 각각의 object file 만들기
```sh
gcc -c main2.c addvec.c multvec.c
```

### addvec.o와 multvec.o를 libvector.a 아카이브로 만들기
```sh
ar rcs libvector.a addvec.o multvec.o
```
- `r` : object 추가
- `c` : 아카이브 생성
- `s` : 인덱스 생성

### Static linking
```sh
gcc -static -o ex4_2 main2.o ./libvector.a
```
또는
```sh
gcc -static -o ex4_2 main2.o -L. -lvector
```

