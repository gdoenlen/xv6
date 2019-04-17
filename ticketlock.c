/**
 * A simple implementation of a spin ticket lock. 
 */
#include "ticketlock.h"

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
