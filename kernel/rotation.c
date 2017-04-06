#include <linux/unistd.h>
#include <linux/kernel.h>
#include <linux/rotation.h>
#include <linux/list.h>
#include <asm-generic/errno-base.h>

int dev_degree = -1;

struct rot_lock {
    int degree;
    int range;
    struct pid_t pid; // caller user process's pid.
    int is_read; // 1 for read lock, 0 for write lock.
}
// list of rotation locks that acquired lock.
struct rot_lock_acq {
    struct rot_lock lock;
    struct list_head acq_locks;
}
// list of rotation locks pending.
struct rot_lock_pend {
    struct rot_lock lock;
    struct list_head pend_locks;
}

int is_valid_input(int degree, int range) {
	// TODO : If input is valid, return 1. Otherwise, return 0.
	return 0;
}

struct list_head *find_by_range(int degree, int range) {
	// TODO : If there is matching process with current pid and given degree range, return corresponding list_head
	// Otherwise (no matching node), return NULL
	return NULL;
}

void exit_rotlock(void) {
	// TODO : 1. Acquire guard lock, 2. Remove elements in acquired list and pending list which has its pid, 
    // 3. If removed an element from acquired list, give lock for pending locks, 4. Release guard lock.
	return;
}

int range_overlap(struct rot_lock *r1, struct rot_lock *r2) {
	// TODO : Return 1 if two locks overlap, otherwise return 0.
	return 0;
}

// dev: device degree
int dev_deg_in_range(struct rot_lock *r) {
    // TODO : Return 1 if rot_lock's range contains device's degree, else 0;
	return 0;
}

int lock_lockables(int caller_is_readlock) {
    // TODO : lock pending locks that are available. If caller is a readlock, lock the first write lock.
    // else (caller is a writelock or set_rotation), FIFO.
    return 0;
}

asmlinkage int sys_set_rotation(int degree){
    // TODO : Set the current rotation as the input degree and let the pending locks
    // acquire their lock by calling lock_lockables(0).

	/* 0 <= degree < 360 */
	if (degree < 0 || degree >= 360)
		return -EINVAL;

	dev_degree = degree;
	printk("[set_rotation syscall] device degree : %d\n", dev_degree);
	return 0;
}

/* For 4 system calls below, 
   0 <= degree < 360, 0 < range < 180
   degree - range <= LOCK RANGE <= degree + range */

asmlinkage int sys_rotlock_read(int degree, int range){	
    // TODO : First, make a rot_lock struct. Then, put into the rot_lock_acq if available.
    // Else, put into the rot_lock_pend.
    
	if (!is_valid_input(degree, range))
		return -EINVAL;

	return 0;
}

asmlinkage int sys_rotlock_write(int degree, int range){
    // TODO : First, make a rot_lock struct. Then, put into the rot_lock_acq if available.
    // Else, put into the rot_lock_pend.
    
	if (!is_valid_input(degree, range)) 
		return -EINVAL;

	return 0;
}

asmlinkage int sys_rotunlock_read(int degree, int range){
    // TODO : First, find the rot_lock_acq struct by calling find_by_range function.
    // Then, remove this from the acqired locks list and let the locks in the pending
    // list to acquire their locks by calling lock_lockables(1).
	
    struct list_head *to_unlock;

	if (!is_valid_input(degree, range)) 
		return -EINVAL;
	
	to_unlock = find_with_range(degree, range);
	if (to_unlock == NULL)
		return -EINVAL;

	return 0;
}

asmlinkage int sys_rotunlock_write(int degree, int range){
    // TODO : First, find the rot_lock_acq struct by calling find_by_range function.
    // Then, remove this from the acqired locks list and let the locks in the pending
    // list to acquire their locks by calling lock_lockables(0).
	
    struct list_head *to_unlock;

	if (!is_valid_input(degree, range)) 
		return -EINVAL;

	to_unlock = find_with_range(degree, range);
	if (to_unlock == NULL)
		return -EINVAL;

	return 0;
}
