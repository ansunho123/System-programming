#define malloc mymalloc
#define free myfree
void *mymalloc(size_t size);
void myfree(void *ptr);