#pragma once

#include <PCH.h>
#include <chrono>
#include <utility>


namespace Shell379 {
    namespace Utilities {
        /**
         * !!! IMPORTANT
         *
         * Scope timer object. Initiate at the beginning of the scope to measure time passed in that scope.
         */
        template <class Ratio>
        class totalTiming {
        public:

            /**
             * Initiate at the beginning of the scope to measure time of the scope. When it is initiate (via this
             * constructor), it will stamp the time point and stored as its attribute.
             *
             * @param return_time reference to be written for the total_time of the scope. Time unit in <Ratio>
             * i.e. if std::milli is used then this will record in millisecond.
             */
            explicit totalTiming<Ratio>(double* return_elapsed_time) {
                reference_duration = return_elapsed_time;
                start = std::chrono::high_resolution_clock::now();
            }

            /**
             * When a scope ends, the timer goes out of scope and ger destroyed. It will automatically calls
             * this destructor. This destructor will stamp this moment and compute the time elapsed; and store
             * it in the pointer.
             *
             */
            ~totalTiming() {
                end = std::chrono::high_resolution_clock::now();
                *reference_duration = std::chrono::duration<double, Ratio>(end - start).count();
            }

        private:
            std::chrono::time_point<std::chrono::system_clock> start, end;
            double* reference_duration;
        };

    }
}

