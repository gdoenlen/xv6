#include "ticketlock.h"

static inline atomic_fetch_and_add(int* addr, int amount)
{
    __asm__ volatile("lock; xaddl %0, %1"
        : "+r" (amount), "+m" (*addr) // input+output
        : // No input-only
        : "memory"
    );
    return amount;
}
