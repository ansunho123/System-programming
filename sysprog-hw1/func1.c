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
