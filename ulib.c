#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "x86.h"

char*
strcpy(char *s, const char *t)
{
  char *os;

  os = s;
  while((*s++ = *t++) != 0)
    ;
  return os;
}

int
strcmp(const char *p, const char *q)
{
  while(*p && *p == *q)
    p++, q++;
  return (uchar)*p - (uchar)*q;
}

uint
strlen(const char *s)
{
  int n;

  for(n = 0; s[n]; n++)
    ;
  return n;
}

void*
memset(void *dst, int c, uint n)
{
  stosb(dst, c, n);
  return dst;
}

char*
strchr(const char *s, char c)
{
  for(; *s; s++)
    if(*s == c)
      return (char*)s;
  return 0;
}

char*
gets(char *buf, int max)
{
  int i, cc;
  char c;

  for(i=0; i+1 < max; ){
    cc = read(0, &c, 1);
    if(cc < 1)
      break;
    buf[i++] = c;
    if(c == '\n' || c == '\r')
      break;
  }
  buf[i] = '\0';
  return buf;
}

int
stat(const char *n, struct stat *st)
{
  int fd;
  int r;

  fd = open(n, O_RDONLY);
  if(fd < 0)
    return -1;
  r = fstat(fd, st);
  close(fd);
  return r;
}

int
atoi(const char *s)
{
  int n;

  n = 0;
  while('0' <= *s && *s <= '9')
    n = n*10 + *s++ - '0';
  return n;
}

void*
memmove(void *vdst, const void *vsrc, int n)
{
  char *dst;
  const char *src;

  dst = vdst;
  src = vsrc;
  while(n-- > 0)
    *dst++ = *src++;
  return vdst;
}

// creates a new kernel thread that starts executing
// the given function with the given arguments.
int thread_create(void (*fn)(void*, void*), void* arg1, void* arg2)
{
    void* stack = malloc(4096);
    return clone(fn, arg1, arg2, stack);
}

// Joins the first child thread
// returns the pid of the thread joined
// or -1 if there are no child threads
int thread_join()
{
    void* stack;
    int ret = join(&stack);
    if (ret > -1) {
        free(stack);
    }

    return ret;
}

static inline atomic_fetch_add(int* addr, int amount)
{
  __asm__ volatile(
      "lock; xaddl %0, %1"
      : "+r" (amount), "+m" (*addr) // input+output
      : // No input-only
      : "memory"
  );
  return amount;
}

void ticket_lock_init(struct ticket_lock* lock) 
{
  lock->turn = 0;
  lock->tickets = 0;
}

void ticket_lock_acquire(struct ticket_lock* lock)
{
  int turn = atomic_fetch_add(&lock->tickets, 1);
  while (turn != lock->turn)
    ; // spin
    
}

void ticket_lock_release(struct ticket_lock* lock)
{
  lock->turn = lock->turn++;
}
