#pragma once

#include <PCH.h>
#include <mutex>
#include <atomic>


namespace Ece420 {

    /**
     * !!! WARNING POSSIBLE DEADLOCK !!!
     *
     * This class provides a suite of mutex, mutex array, read-write mutex, and read-write mutex array.
     * Locks here do not automatically unlock when go out of scope and must me unlocked automatically.
     * Possible deadlock if misuse.
     *
     */
    class SharedPoolAccess {
    public:

        /**
         * Create the lock manager. Indicate if the lock are normal or read-write mutex.
         * Indicate mutex array saize
         *
         * @param rw_flag_option
         * @param number_of_locks
         */
        SharedPoolAccess(bool rw_flag_option, int number_of_locks);


        /**
         * Normal mutex lock
         * @param lock_position
         */
        void normalLock(int lock_position);
        void normalLock();


        /**
         * Normal mutex unlock
         * @param lock_position
         */
        void normalUnlock(int lock_position);
        void normalUnlock();


        /**
         * Lock mutex as reader
         *
         * @param lock_position
         */
        void readLock(int lock_position);
        void readLock();


        /**
         * Lock mutex as writer
         *
         * @param lock_position
         */
        void writeLock(int lock_position);
        void writeLock();


        /**
         * Unlock mutex as reader
         *
         * @param lock_position
         */
        void readUnlock(int lock_position);
        void readUnlock();


        /**
         * Unlock mutex as writer
         *
         * @param lock_position
         */
        void writeUnlock(int lock_position);
        void writeUnlock();


        /**
         * Inner class use for read and write mutex
         */
        class ReadWriteLock {
        public:

            ReadWriteLock() = default;

            /**
             * Equivalent to shared mutex
             */
            void readLock();


            /**
             * Unlock shared mutex.
             */
            void readUnlock();


            /**
             * Lock mutex uniquely
             */
            void writeLock();


            /**
             * Unlock unique mutex
             */
            void writeUnlock();

        private:
            std::mutex single_rw_lock;
            std::atomic<int> read_count{0};
            std::atomic<int> write_count{0};
            std::condition_variable waitingToRead;
            std::condition_variable waitingToWrite;
        };
        

    private:
        std::vector<std::mutex> normal_lock_array;
        std::vector<SharedPoolAccess::ReadWriteLock> rw_lock_array;
        bool rw_flag_option;
    };
}
