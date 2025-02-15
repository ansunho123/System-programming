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



