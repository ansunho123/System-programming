# 🖥️ 시스템 프로그래밍 과제 2

## 📌 과제 내용
이번 과제에서는 `printf()` 함수를 **Library Interpositioning** 기법을 사용하여 직접 구현합니다.  
이를 통해 **Compile-time Interpositioning**과 **Link-time Interpositioning**의 개념을 학습합니다.

### 🛠️ 구현 요구사항
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

## 📂 파일 구성

| 파일명       | 설명 |
|-------------|-----------------------------------------------------|
| `main.c`    | `printf()` 함수의 interpositioning을 테스트하는 코드 |
| `printf.h`  | 사용자 정의 `printf()` 함수의 **헤더 파일** |
| `myprintf.c` | `printf()`의 일부 기능을 직접 구현한 소스 코드 |

---

## 🚀 실행 방법
### 1️⃣ Compile-time Interpositioning
```bash
gcc -o main main.c myprintf.c
./main
