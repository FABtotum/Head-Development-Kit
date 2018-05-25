#ifndef _TESTER_H_
#define _TESTER_H_

#define ERR_UNRECOGNIZED_COMMAND "Unrecognized command"

typedef unsigned int lock_t;

extern lock_t serial_lock;

extern char * errmsg;

bool acquire (lock_t &lock);

inline void release (lock_t &lock) { lock--; }
inline void wait (lock_t &lock) { while (!acquire(lock)); }

#endif