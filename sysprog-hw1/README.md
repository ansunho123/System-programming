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

## 2) func2 분석

### 어셈블리 코드
```assembly
000000000000124a <func2>:
    124a:       f3 0f 1e fa             endbr64
    124e:       48 85 f6                test   %rsi,%rsi
    1251:       7e 41                   jle    1294 <func2+0x4a>
    1253:       49 89 fa                mov    %rdi,%r10
    1256:       41 b9 00 00 00 00       mov    $0x0,%r9d
    125c:       41 b8 00 00 00 00       mov    $0x0,%r8d
    1262:       b9 00 00 00 00          mov    $0x0,%ecx
    1267:       48 89 d7                mov    %rdx,%rdi
    126a:       eb 0f                   jmp    127b <func2+0x31>
    126c:       4c 01 c9                add    %r9,%rcx
    126f:       41 83 c0 01             add    $0x1,%r8d
    1273:       4d 01 d1                add    %r10,%r9
    1276:       41 39 f0                cmp    %esi,%r8d
    1279:       74 1e                   je     1299 <func2+0x4f>
    127b:       ba 00 00 00 00          mov    $0x0,%edx
    1280:       b8 00 00 00 00          mov    $0x0,%eax
    1285:       48 01 d1                add    %rdx,%rcx
    1288:       83 c0 01                add    $0x1,%eax
    128b:       48 01 fa                add    %rdi,%rdx
    128e:       39 f0                   cmp    %esi,%eax
    1290:       75 f3                   jne    1285 <func2+0x3b>
    1292:       eb d8                   jmp    126c <func2+0x22>
    1294:       b9 00 00 00 00          mov    $0x0,%ecx
    1299:       48 89 c8                mov    %rcx,%rax
    129c:       c3                      retq
```

### 변환된 C 코드
```c
long func2(long x, long y, long z)
{
    long rcx = 0;
    long r10 = x;
    long r9 = 0;
    long r8 = 0;
    x = z;
    long result = 0;
    z = 0;
    if (y <= 0)
    {
        return rcx;
    }

    while (1)
    {
        rcx += z;
        result += 1;
        z += x;
        if (result != y)
        {
            continue;
        }

        rcx += r9;
        r8 += 1;
        r9 += r10;
        if (r8 == y)
        {
            return rcx;
        }
        z = 0;
        result = 0;
    }
}
```

### 어셈블리 코드 분석 및 해석

- `%rdi`, `%rsi`, `%rdx`는 각각 첫 번째(`x`), 두 번째(`y`), 세 번째(`z`) 인자
- `test %rsi, %rsi` 후 `jle` 실행 → `if (y <= 0)` 조건 확인 후 리턴
- 초기화 과정에서 `r10 = x`, `r9 = 0`, `r8 = 0`, `x = z`, `result = 0`, `z = 0` 설정
- 반복문 실행: `rcx`에 `z`를 더하고, `result` 증가, `z`에 `x`를 더함
- `if (result != y)`가 참이면 계속 진행
- `rcx`에 `r9`를 더하고, `r8` 증가, `r9`에 `r10` 더하기
- `if (r8 == y)`이면 `rcx` 반환
- `z = 0; result = 0;` 후 다시 반복



