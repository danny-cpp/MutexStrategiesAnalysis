#include "SharedPoolAccess.h"


void Ece420::SharedPoolAccess::ReadWriteLock::readLock() {

    // Mutex scope begins
    std::unique_lock<std::mutex> lock{single_rw_lock};

    // If there is at least one writer, we wait. The loop
    // here is to prevent spurious wake up
    while (write_count >= 1) {
        waitingToRead.wait(lock, [&] {
            return write_count == 0;
        });
    }

    read_count++;

    // Mutex scope automatically ends
}

void Ece420::SharedPoolAccess::ReadWriteLock::readUnlock() {

    // Mutex scope begins
    std::unique_lock<std::mutex> lock{single_rw_lock};

    read_count--;
    if (read_count == 0) {

        // We use notify one here is a defensive way to wake up writers.
        // If we notify all, all of them will wake up (but only one will stay
        // awake and the other should go back to sleep if implement correctly).
        // However, it will waste resources and this is the best way to do it.
        waitingToWrite.notify_one();
    }

    // Mutex scope ends
}

void Ece420::SharedPoolAccess::ReadWriteLock::writeLock() {

    // Mutex scope begins
    std::unique_lock<std::mutex> lock{single_rw_lock};

    while (write_count >= 1 || read_count >= 1) {
        waitingToWrite.wait(lock, [&] {

            // A writer is always more prone to starvation because it needs "stricter"
            // condition to be woken up. More advanced techniques could be used such as
            // timed or priority-based to alleviate the problem
            return write_count == 0 && read_count == 0;
        });
    }

    write_count++;

    // Mutex scope ends
}

void Ece420::SharedPoolAccess::ReadWriteLock::writeUnlock() {

    // Mutex scope begins
    std::unique_lock<std::mutex> lock{single_rw_lock};

    write_count--;

    // We will first attempt to wake ONE writer up and then attempt to wake ALL
    // readers up. Since we implement the locks above correctly, the threads should
    // go back to sleep EVEN IF it is woken up when their requirements are met BUT FAIL
    // TO SATISFIED when they are taking actions (this is called a spurious wake-up).
    //
    // We also prioritize to wake writer up before reader because we know that writer is
    // more prone to starvation.
    waitingToWrite.notify_one();
    waitingToRead.notify_all();

    // Mutex scope ends
}

Ece420::SharedPoolAccess::SharedPoolAccess(bool rw_flag_option, int number_of_locks) {

    // Indicates if this use regular mutex or rw-mutex
    this->rw_flag_option = rw_flag_option;

    if (rw_flag_option) {
        rw_lock_array = std::vector<SharedPoolAccess::ReadWriteLock>(number_of_locks);
    }
    else {
        normal_lock_array = std::vector<std::mutex>(number_of_locks);
    }
}

void Ece420::SharedPoolAccess::normalLock(int lock_position) {
    normal_lock_array[lock_position].lock();
}

void Ece420::SharedPoolAccess::normalLock() {
    normal_lock_array[0].lock();
}

void Ece420::SharedPoolAccess::normalUnlock(int lock_position) {
    normal_lock_array[lock_position].unlock();
}

void Ece420::SharedPoolAccess::normalUnlock() {
    normal_lock_array[0].unlock();
}

void Ece420::SharedPoolAccess::readLock(int lock_position) {
    rw_lock_array[lock_position].readLock();
}

void Ece420::SharedPoolAccess::readLock() {
    rw_lock_array[0].readLock();
}

void Ece420::SharedPoolAccess::writeLock(int lock_position) {
    rw_lock_array[lock_position].writeLock();
}

void Ece420::SharedPoolAccess::writeLock() {
    rw_lock_array[0].writeLock();
}

void Ece420::SharedPoolAccess::readUnlock(int lock_position) {
    rw_lock_array[lock_position].readUnlock();
}

void Ece420::SharedPoolAccess::readUnlock() {
    rw_lock_array[0].readUnlock();
}

void Ece420::SharedPoolAccess::writeUnlock(int lock_position) {
    rw_lock_array[lock_position].writeUnlock();
}

void Ece420::SharedPoolAccess::writeUnlock() {
    rw_lock_array[0].writeUnlock();
}
