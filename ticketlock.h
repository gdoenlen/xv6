#ifndef TICKETLOCK_H
#define TICKETLOCK_H

struct ticket_lock {
  int turn;
  int tickets;
};

void ticket_lock_acquire(struct ticket_lock*);
void ticket_lock_release(struct ticket_lock*);
void ticket_lock_init(struct ticket_lock*);

#endif
