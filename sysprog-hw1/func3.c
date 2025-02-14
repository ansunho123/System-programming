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
