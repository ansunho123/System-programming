long func4(int rdi)
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
