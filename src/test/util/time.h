// Copyright (c) The Sixbit Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://opensource.org/license/mit/.

#ifndef SIXBIT_TEST_UTIL_TIME_H
#define SIXBIT_TEST_UTIL_TIME_H

#include <util/time.h>

struct ElapseSteady {
    MockableSteadyClock::mock_time_point::duration t{MockableSteadyClock::INITIAL_MOCK_TIME};
    ElapseSteady()
    {
        (*this)(0s); // init
    }
    void operator()(std::chrono::milliseconds d)
    {
        t += d;
        MockableSteadyClock::SetMockTime(t);
    }
};

#endif // SIXBIT_TEST_UTIL_TIME_H
