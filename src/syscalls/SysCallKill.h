//
// KillSystemCall.h
//
// Copyright (C) 2017-2021 Tactical Computing Laboratories, LLC
// All Rights Reserved
// contact@tactcomplabs.com
//
// See LICENSE in the top level directory for licensing details
//
#pragma once
#ifndef __SYSTEMCALLEXITGROUP_H__
#define __SYSTEMCALLEXITGROUP_H__

#include "SystemCallInterface.h"
#include <type_traits>

namespace SST { namespace RevCPU {

class KillSystemCallParameters : public virtual SystemCallParameterInterface {
    
    pid_t pid;
    int sig;

    public:

    KillSystemCallParameters(const pid_t pid_i, const int sig_i) : SystemCallParameterInterface(), pid(pid_i), sig(sig_i) {}

    size_t count() override;

    template<typename ParameterType>
    bool get(const size_t parameter_index, ParameterType & param);
};

template<bool IsRiscv32>
class KillSystemCall : public virtual SystemCallInterface<IsRiscv32> {

    using RiscvModeIntegerType = typename std::conditional<IsRiscv32, std::uint32_t, std::uint64_t>::type;

    public:

    KillSystemCall() {}

    RiscvModeIntegerType code() override;
    
    // always returns false
    //
    template<typename ReturnType>
    bool invoke(SystemCallParameterInterface & parameters, ReturnType & value);

    // returns true
    //
    template<>
    bool invoke(SystemCallParameterInterface & parameters, void_t & value);
};

} /* end namespace RevCPU */ } // end namespace SST

#endif

// EOF