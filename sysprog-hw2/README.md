# 🖥️ 시스템 프로그래밍 과제 2

## 📌 과제 내용
이번 과제에서는 `printf()` 함수를 **Library Interpositioning** 기법을 사용하여 직접 구현합니다.  
이를 통해 **Compile-time Interpositioning**과 **Link-time Interpositioning**의 개념을 학습합니다.

---

## 🔍 구현 요구사항
- `stdio.h`에 있는 `printf()` 함수를 사용하지 않고, **사용자 정의 `printf()` 함수**를 구현합니다.
- `printf()`의 일부 **Format 기능**을 지원해야 합니다:
  - `%d` : `int` 값을 출력
  - `%c` : `char` 값을 출력
  - `%s` : `string` 값을 출력
  - `%x` : `int` 값을 **16진수** 형태로 출력
  - **Multiple arguments 지원**: 여러 개의 인자를 처리할 수 있도록 구현
- 기본 `printf()`와 구분을 위해, **출력 시 "[Interpositioning]"이라는 문구를 추가**합니다.
- **Compile-time, Link-time Interpositioning** 두 가지 방법을 모두 실습합니다.

---

## ⚠️ 제약 조건
✅ **금지된 함수**  
- `printf()`, `fprintf()`, `dprintf()` 사용 불가  
- `sprintf()` 등 **format 인식 기능이 있는 함수** 사용 불가  

✅ **사용 가능한 함수**  
- `putchar()`, `fputs()`와 같은 **format을 인식하지 않는 출력 함수** 사용 가능  

✅ **가변 인자 처리 필수**  
- `printf()`의 원형은 아래와 같음:
  ```c
  int printf(const char* format, ...);
  ```
- 가변 인자(`...`)를 사용하여 **입력 개수를 알 수 없는 경우에도 처리할 수 있도록 구현**  
- **`stdarg.h` 헤더 파일을 포함하여 가변 인자 처리**  
- `va_list`, `va_start`, `va_arg`, `va_end` 매크로 사용 필수  

---

## 📂 파일 구성

| 파일명       | 설명 |
|-------------|-----------------------------------------------------|
| `main.c`    | `printf()` 함수의 interpositioning을 테스트하는 코드 |
| `printf.h`  | 사용자 정의 `printf()` 함수의 **헤더 파일** |
| `myprintf.c` | `printf()`의 일부 기능을 직접 구현한 소스 코드 |

---


## 구현 방법
✅ `%d`, `%x` → **4 Byte 크기의 `int` 타입 인자**  
✅ `%c` → **1 Byte 크기의 `char` 타입 인자**  
✅ `%s` → **8 Byte 크기의 `char *` 타입 인자**  

### 가변 인자 처리 예제 (`stdarg.h` 활용)
```c
#include <stdarg.h>
#include <stdio.h>

void example(int a, ...) {
    va_list ap;      
    va_start(ap, a);  // 가변 인자 리스트 초기화
    
    while (/* 모든 인수를 읽을 때\ua까지 */) {
        int arg = va_arg(ap, int);  // 가변 인자 읽기
        /* 처리 로직 */
    }
    
    va_end(ap);  // 가변 인자 리스트 해제
}

```

*******


## 과제 설명




### `main.c`
- `printf()` 함수가 올바르게 동작하는지 확인하기 위한 테스트 코드
- 다양한 형식의 인자를 사용하여 `printf()` 호출

```c
#include<stdio.h>
#include<printf.h>

int main(){
    int i = 1000;
    char c = 'a';
    char *s = "test";
    int x1 = 7293;
    int x2 = -412;

    printf("Inter i = %d\n\n", i);
    printf("Character c = %c\n\n", c);
    printf("String s = %s\n\n" , s);
    printf("hex x1 = %x, x2 = %x\n\n", x1, x2);
    printf("Multiple arguments : i = %d, c = %c, s = %s, x1 = %x, x2 = %x\n", i ,c, s, x1, x2);

    return 0;
}
```

### `printf.h`
- Compile-time interpositioning을 위해 `printf`를 `myprintf`로 매핑
```c
#define printf myprintf

int myprintf(const char* format, ...);
```

### `myprintf.c`
- `COMPILETIME`과 `LINKTIME`을 구분하여 `myprintf()` 함수 구현
- 가변 인자(`stdarg.h`)를 이용하여 `printf()`와 동일한 기능을 구현
- `printf()`의 format을 해석하여 직접 숫자, 문자, 문자열을 출력

```c
#ifdef COMPILETIME
#include <stdio.h>
#include <stdarg.h>

int myprintf(const char* format,...){
    va_list args;
    va_start(args, format);
    
    fputs("[Interpositioning]", stdout);
    
    while (*format != '\0'){
        if(*format == '%') {
            format++;
            if(*format == 'd'){
                int num = va_arg(args,int);
                char a[100];
                if(num < 0){
                    putchar('-');
                    num = -num;  
                }
                int i = 0;
                if(num == 0) {
                    a[i] = '0';
                    i++;
                }
                else {
                    while(num!=0) {
                        a[i] = num % 10 + '0';
                        i++;
                        num /= 10; 
                    }
                }
                for(int j = i-1; j>=0; j--){
                    putchar(a[j]);
                }
            }
            else if(*format == 'c'){
                char c = va_arg(args,int);
                putchar(c);
            }
            else if(*format == 's'){
                char *str = va_arg(args,char*);
                fputs(str, stdout);
            }
            else if(*format == 'x'){
                unsigned int num = va_arg(args,int);
                char hex[100];
                int i = 0;
                if (num == 0){
                    hex[i] = '0';
                    i++;
                }
                else {
                    while(num!=0){
                        int temp = num % 16;    
                        if(temp < 10) {
                            hex[i] = temp + '0';
                        }
                        else{
                            hex[i] = (temp -10) + 'a';
                        }
                        i++;
                        num /= 16;
                    }
                }
                for(int j = i-1; j>=0; j--){
                    putchar(hex[j]);
                }
            }
        }
        else {
            putchar(*format);
        }
        format++;
    }
    va_end(args);
    return 0;    
}
#endif

#ifdef LINKTIME

#include <stdio.h>
#include <stdarg.h>

int __real_printf(const char* format,...);

int __wrap_printf(const char* format,...){

/* 위와 코드는 동일 하기 때문에 생략.
myprint.c 참고 */
 
```

---
## Compile Time 결과

![Compile Time Interpositioning](https://github.com/ansunho123/System-programming/raw/main/sysprog-hw2/images/compiltetime%20interpositioning.png)

---

## Link-time 결과 
![LInkint time Interpositioning](https://github.com/ansunho123/System-programming/blob/main/sysprog-hw2/images/linkingtime%20interpositioning.png)




*** 

## myprint.c 코드 설명

이 코드에서는 **Compile Time**과 **Link Time**에서의 Library Interpositioning을 구현하는 방법을 구분하여 설명하고 있습니다. 또한, 가변 인자를 처리하는 방식도 포함하고 있습니다.



### 1. Compile Time vs Link Time Interpositioning

코드에서는 `#ifdef COMPILETIME ~ #endif`와 `#ifdef LINKTIME ~ #endif`을 사용하여 **Compile Time**과 **Link Time**에서의 library interpositioning을 구분하였습니다.




#### ✅ Compile Time Interpositioning
- `printf.h`라는 별도의 헤더 파일을 만들어서 로컬에서 `printf.h`가 존재해야 합니다.
- `#define printf myprintf`를 선언하여 기존의 `printf`를 `myprintf`로 변경합니다.
- `int myprintf(const char* format, ...);`을 선언하여, 컴파일 시 `printf`가 아닌 `myprintf`가 참조되도록 합니다.




### 2. 가변 인자 처리 (`stdarg.h` 사용)
가변 인자를 다루기 위해 `<stdarg.h>` 헤더를 포함하여 `va_list`, `va_start`, `va_arg`, `va_end`를 활용했습니다.



### 3. myprintf 함수 구현
`myprintf` 함수는 출력 시 항상 `[Interpositioning]`을 먼저 출력하며, 포맷 문자열을 해석하여 적절한 출력 형식으로 변환합니다.



### 문자열 처리 과정
1. 포맷 문자열의 끝(`'\0'`)까지 반복하며 `while (*format != '\0')`로 검사합니다.
2. `if (*format == '%')`를 이용해 `%` 기호가 등장하면 특정 처리 루틴으로 분기합니다.
3. `%d, %c, %s, %x` 등의 포맷을 구별하여 처리합니다.



####  `%d` (정수 출력)
- `va_arg(args, int)`로 정수를 가져옵니다.
- 양수인지 음수인지 구분 후 부호부터 출력합니다.
- 10진수로 변환하여 문자열 배열에 저장한 후, 이를 거꾸로 출력합니다.


#### `%c` (문자 출력)
- `va_arg(args, int)`를 이용하여 문자 값을 가져온 후, `putchar()`로 출력합니다.
- (Va_arg(args,char)로 하면 오류가 떠서 int로 해주었다.)



####  `%s` (문자열 출력)
- `va_arg(args, char*)`를 사용하여 문자열을 가져오고, `fputs()`로 출력합니다.
  

####  `%x` (16진수 출력)
- `va_arg(args, int)`를 이용해 정수를 가져오고, 16진수로 변환하여 출력합니다.
- 양수 음수 상관 없이 그 비트의 형식대로 출력해주기 때문에 unsigned int num로 받았습니다.
- 16진수 변환 과정에서 `0~9`는 그대로 출력하고, `10~15`는 `a~f`로 변환하여 처리합니다.


### 4. 다양한 인자 처리
- `va_list args`를 활용하여 여러 개의 인자를 처리할 수 있도록 하였습니다.
- `format++;`을 통해 포맷 문자열을 계속 탐색하면서 `%`를 만나면 해당 형식에 맞게 변환합니다.



