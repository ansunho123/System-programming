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
| [func.h]| func 함수 헤더 파일 |
| [ex1] | gcc 컴파일을 통해 만든 실행 파일 |
| [ex1_debug] | gcc 컴파일 통해 디버깅 정보도 포함 된 실행 파일 |
| [func.s] | func.c 함수를 assembly 파일 변환 |
| [ex1_assembly] | ex1 파일을 assembly 파일로 변환 |

**********************

## 실습 과정

### C 파일

#### main 함수
```c
#include "func.h"

int main() {
	int i = 10;
	int j = func(i);
	
	printf("func(%d) = %d\n" , i ,j);
	return 0;
}
```

#### func.c 함수

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

#### func.h
```c
#include <stdio.h>

int func(int);
```

*********************

## GCC 컴파일

### GCC 주요 옵션
* -o <filename>: 출력 파일 지정
* -O0/-O1/-O2: 최적화(optimization) 레벨
* -S: compile만 수행 (assembly code로 출력, assemble과 link 과정 수행 안함)
* -c: compile 및 assemble만 수행 (link 과정 수행 안함)
* -g: debugging을 위한 정보를 포함한 컴파일
* 옵션이 포함된 사용법 ex) `gcc -O1 -g -o exe_file main.c func.c`

### 최적화 레벨 1로 컴파일
```
$ gcc -O1 -o ex1 main.c func.c
$ ./ex1
func(10) = 45
```

### func.c를 어셈블리 코드로 변환
```
$ gcc -O1 -S func.c
$ vim func.s
```

### func.s 결과
[func.s](https://github.com/ansunho123/System-programming/blob/main/sysprog-labs2/func.s)

*****************

## GDB 사용법

### 디버깅 정보 포함하여 컴파일
```
$ gcc -g -o ex1_debug main.c func.c
```

### GDB 실행
```
$ gdb <filename>
```

#### GDB 기본 명령어
* `help`: 도움말 확인
* `quit`: GDB 종료
* `r` 또는 `run`: 프로그램 실행
* `run`과 함께 인자 입력 가능 (예: `run arg1 arg2`)

### GDB GUI 모드 실행
* `-tui` 옵션을 사용하여 GUI 모드 실행 가능
* 방향키를 사용하여 Source Code 이동 가능
* `list` 명령어로 코드 확인 가능 (예: `list main.c:4`)

*****************

## Breakpoint 설정 및 활용

### Breakpoint 설정
```
(gdb) break main
(gdb) break 5
(gdb) break func.c:5
```
- `break main`: main 함수 시작에서 중단
- `break 5`: 현재 파일의 5번째 줄에서 중단
- `break func.c:5`: func.c 파일의 5번째 줄에서 중단

### Breakpoint 목록 확인
```
(gdb) info breakpoints
```

### Breakpoint 삭제 및 관리
```
(gdb) clear func
(gdb) delete
(gdb) disable 1
(gdb) enable 1
```

*****************

## Stepping (단계별 실행)

### 단계별 실행 명령어
```
(gdb) next
(gdb) next 10
(gdb) continue
(gdb) CTRL-C
```
- `next`: 현재 함수의 다음 명령어 실행
- `next 10`: 10개의 명령어 실행 후 정지
- `continue`: 프로그램 계속 실행
- `CTRL-C`: 프로그램 실행 중단

*****************

## 변수 확인 및 조작

### 변수 값 출력
```
(gdb) print i
(gdb) printf "%08x\n", i
```

### 변수 값 변경
```
(gdb) set variable i = 20
(gdb) print i
```

### 변수 지속적 감시
```
(gdb) display i
(gdb) undisplay 1
```

*****************

## 추가적인 Stepping 방법

### 현재 함수 종료 후 호출한 함수로 복귀
```
(gdb) finish
```

### 어셈블리 단위로 디버깅
```
(gdb) stepi
(gdb) nexti
```
- `stepi`: 다음 어셈블리 명령 실행 (함수 호출 포함)
- `nexti`: 다음 어셈블리 명령 실행 (함수 호출 제외)

*****************

## 실행 중 변수 값 변경

```
(gdb) print i
$1 = 10
(gdb) set variable i = 20
(gdb) print i
$2 = 20
```



