# 🖥️ 시스템 프로그래밍 과제 1

## 📌 과제 내용
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

---

## 2) func3 분석

### 어셈블리 코드
```assembly
000000000000129d <func3>:
    129d:       f3 0f 1e fa             endbr64
    12a1:       49 0f af f8             imul   %r8,%rdi
    12a5:       49 0f af f1             imul   %r9,%rsi
    12a9:       48 29 f7                sub    %rsi,%rdi
    12ac:       48 0f af 54 24 08       imul   0x8(%rsp),%rdx
    12b2:       48 8d 04 3a             lea    (%rdx,%rdi,1),%rax
    12b6:       48 0f af 4c 24 10       imul   0x10(%rsp),%rcx
    12bc:       48 29 c8                sub    %rcx,%rax
    12bf:       c3                      retq

```

### 변환된 C 코드
```c

long func3(long rdi, long rsi, long rdx, long rcx, long r8, long r9, long x, long y)
{
    rdi *= r8;
    rsi *= r9;
    rdi -= rsi;
    rdx *= x;
    long result = (rdx + rdi);
    rcx *= y;
    result -= rcx;
    return result;
}
```

### 어셈블리 코드 분석 및 해석

- imul %r8, %rdi → rdi *= r8;
- imul %r9, %rsi → rsi *= r9;
- sub %rsi, %rdi → rdi -= rsi;
- imul 0x8(%rsp), %rdx → rdx *= x;
- lea (%rdx, %rdi,1), %rax → result = rdx + rdi;
- imul 0x10(%rsp), %rcx → rcx *= y;
- sub %rcx, %rax → result -= rcx;
- retq → return result;

---------
## 2) func4 분석

### 어셈블리 코드
```assembly
00000000000012c0 <func4>:
    12c0:       f3 0f 1e fa             endbr64
    12c4:       b8 02 00 00 00          mov    $0x2,%eax
    12c9:       48 83 ff 01             cmp    $0x1,%rdi
    12cd:       7e 14                   jle    12e3 <func4+0x23>
    12cf:       53                      push   %rbx
    12d0:       48 89 fb                mov    %rdi,%rbx
    12d3:       48 8d 7f ff             lea    -0x1(%rdi),%rdi
    12d7:       e8 e4 ff ff ff          callq  12c0 <func4>
    12dc:       48 8d 44 58 ff          lea    -0x1(%rax,%rbx,2),%rax
    12e1:       5b                      pop    %rbx
    12e2:       c3                      retq
    12e3:       c3                      retq
    12e4:       66 2e 0f 1f 84 00 00    nopw   %cs:0x0(%rax,%rax,1)
    12eb:       00 00 00
    12ee:       66 90                   xchg   %ax,%ax

```

### 변환된 C 코드
```c

llong func4(int rdi)
{
    long result = 2;

    if (rdi <= 1)
    {
        return result;
    }
    // push %rbx는 x를 다시 쓰기 때문에 다시 넣어놓는 임시 변수지만 전에 써있을수도 있으니 넣는거!
    long rbx = rdi;
    rdi--;

    long v1 = func4(rdi);
    result = v1 + (rbx * 2 - 1);
    return result;
    // pop rbx 예전의 rdi값 rbx에 받아오는거!
}
```

### 어셈블리 코드 분석 및 해석

#### 변수 할당

- %rdi → rdi (첫 번째 인자)
- %rax → result, v1
- %rbx → rbx

#### 어셈블리 변환

- mov $0x2, %eax → long result = 2;
- cmp $0x1, %rdi → if (rdi <= 1)
- jne 12e3 → 조건 만족 시 return result;
- push %rbx → rbx를 스택에 저장 (Callee 레지스터 보호)
- mov %rdi, %rbx → long rbx = rdi;
- lea -0x1(%rdi), %rdi → rdi--;
- callq 12c0 <func4> → 재귀 호출 → long v1 = func4(rdi);
- lea -0x1(%rax,%rbx,2), %rax → result = v1 + (rbx * 2 - 1);
- retq → return result;
