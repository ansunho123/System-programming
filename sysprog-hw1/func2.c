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
