//
// SysCalls.h
//
// Copyright (C) 2017-2021 Tactical Computing Laboratories, LLC
// All Rights Reserved
// contact@tactcomplabs.com
//
// See LICENSE in the top level directory for licensing details
//
#pragma once      /// THIS WILL ALMOST NEVER WORK


#ifndef _SST_REVCPU_SYSCALLS_H_
#define _SST_REVCPU_SYSCALLS_H_

#include <unordered_map>
#include <type_traits>
#include <cstddef>
#include <cstdint>
#include <sys/types.h>
#include <utility>
#include <unistd.h>
#include <filesystem>
#include <variant>

#include "RevInstTable.h"
#include "RevSysCallInterface.h"
#include "RevMem.h"

#include "syscalls/RevChdir.h"
#include "syscalls/RevWrite.h"
#include "syscalls/RevFork.h"
#include "syscalls/RevRTSigProcMask.h"
#include "syscalls/RevExit.h"
#include "syscalls/Rev99.h"
// #include "../include/syscalls/RevGetPID.h"
// #include "../include/syscalls/RevMkdirat.h"
// #include "../include/syscalls/RevPwrite.h"
// #include "../include/syscalls/RevClone.h"

using namespace SST::RevCPU;

namespace SST { namespace RevCPU {

// using return_t = std::variant<
//   std::monostate, // -- null case
//   int,
//   ssize_t,
//   pid_t,
//   timeval
// >;

class SystemCalls {
    public:
    SystemCalls() = default;

    // static std::unordered_map< int, std::pair<systemcall_t, return_t>> jump_table32; //-- 32-bit SysCalls
    // static std::unordered_map< int, std::pair<systemcall_t, return_t>> jump_table64; //-- 64-bit SysCalls

    static std::unordered_map<int, systemcall_t> jump_table32; //-- 32-bit SysCalls
    static std::unordered_map<int, systemcall_t> jump_table64; //-- 64-bit SysCalls
};

} /* end namespace RevCPU */ } // end namespace SST

#endif  // end _SST_REVCPU_SYSCALLS_H_
// EOF
