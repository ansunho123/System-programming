# 시스템 프로그래밍 과제 1

## 과제 내용
이번 과제에서는 총 4개의 dump 파일(어셈블리 코드)을 C 코드로 번역하는 것이 목표입니다.

| 어셈블리 파일 | 변환된 C 코드 파일 |
|--------------|----------------|
| func1.dump  | func1.c        |
| func2.dump  | func2.c        |
| func3.dump  | func3.c        |
| func4.dump  | func4.c        |

---

## 1) func1 분석

### 어셈블리 코드
```assembly
0000000000001236 <func1>:
    1236:       f3 0f 1e fa             endbr64
    123a:       48 8d 04 37             lea    (%rdi,%rsi,1),%rax
    123e:       48 29 d0                sub    %rdx,%rax
    1241:       78 01                   js     1244 <func1+0xe>
    1243:       c3                      retq
    1244:       48 0f af c0             imul   %rax,%rax
    1248:       eb f9                   jmp    1243 <func1+0xd>
```

### 변환된 C 코드
```c
long func1(long x, long y, long z)
{
    long result = x + y;
    result = result - z;

    if (result < 0)
    {
        return result * result;
    }
    else
    {
        return result;
    }
}
```

---

## 어셈블리 코드 분석 및 해석

- `123a: lea (%rdi, %rsi,1), %rax`
  - `rdi`는 첫 번째 인자(`x`), `rsi`는 두 번째 인자(`y`)
  - `lea (%rdi, %rsi,1), %rax`는 주소 변환 연산으로 `rdi + rsi * 1`을 `rax`에 저장
  - 따라서 `long result = x + y;`로 변환

- `123e: sub %rdx, %rax`
  - `rax`에서 `rdx`(세 번째 인자, `z`)를 빼는 연산
  - 즉, `result = result - z;`에 해당

- `1241: js 1244`
  - 최근 연산 결과가 negative이면(음수이면) `1244`로 점프
  - 따라서 `if (result < 0)` 조건을 의미

- `1244: imul %rax, %rax`
  - `rax = rax * rax`, 즉 `result = result * result;`

- `1248: jmp 1243`
  - `1243` 주소는 `retq`를 실행하는 부분으로 바로 리턴됨
  - 즉, `return result * result;`

- `1243: retq`
  - `if (result < 0)`이 아니라면 바로 `return result;`

따라서 최종적으로 변환된 C 코드는 위와 같이 작성될 수 있습니다.

