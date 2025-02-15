# 시스템 프로그래밍 실습 2

## 실습 내용
- GCC를 활용한 소스 코드 컴파일 과정
- GDB를 사용한 디버깅 기법 및 Breakpoint 활용
- Object 파일을 Assembly로 변환하여 구조 분석

  
## 프로젝트 파일 구성
본 실습은 총 7개의 파일로 구성됩니다.

| 파일명       | 설명 |
|-------------|--------------------------------------------------|
| [main.c]  | func를 부르고 연산 하는 main 함수 |
| [func.c] | 0부터 a까지의 합을 리턴 해주는 func 함수|
| [func.h]| func 함수 해더 파일 |
| [ex1] | gcc 컴파일을 통해 만든 실행 파일 |
| [ex1_debug] | gcc 컴파일 통해 디버깅 정보도 포함 된 실행 파일 |
| [func.s] | func.c 함수를 assembly 파일 변환 |
| [ex1_assembly] | ex1 파일을 assembly 파일로 변환 | 




**********************
## 실습 과정

### C 파일 

### main 함수 
```c
#include "func.h"

int main() {
	int i = 10;
	int j = func(i);
	
	printf("func(%d) = %d\n" , i ,j);
	return 0;
}
```
### func.c 함수

```c
#include "func.h"

int func(int a) {
	int ret = 0;
	for (int i = 0; i < a; i++) {
		ret = ret + i ;
	}
	return ret;
}
```

### func.h
```c
#include <stdio.h>

int func(int);
```
*********************

## GCC 컴파일 

### GCC 주요 option
* -o <filename>: 출력 파일 지정
* O/-O0/-O1/-O2: 최적화(optimization) 레벨
* -S: compile만 수행 (assembly code로 출력, assemble과 link 과정 수행 안함)
* -c: compile 및 assemble만 수행 (link 과정 수행 안함)
* -g: debugging을 위한 정보를 포함한 컴파일
* 옵션이 포함된 사용법 ex) gcc -O1 -g -o exe_file main.c func.c



### Compile with optimization Level 1
```
$ gcc –O1 –o ex1 main.c func.c
$ ./ex1
func(10) = 45
```

### • Compile only (func.c를 assembly어로만)

```
$ gcc –O1 –S func.c
$ vim func.s
```
|[func.s](https://github.com/ansunho123/System-programming/blob/main/sysprog-labs2/func.s)|

*****************




