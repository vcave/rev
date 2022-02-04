//
// SysCallKill.h
//
// Copyright (C) 2017-2021 Tactical Computing Laboratories, LLC
// All Rights Reserved
// contact@tactcomplabs.com
//
// See LICENSE in the top level directory for licensing details
//
#pragma once
#ifndef __SYSTEMCALLKILL_H__
#define __SYSTEMCALLKILL_H__

#include "SystemCallInterface.h"
#include <type_traits>
#include <sys/types.h>

namespace SST { namespace RevCPU {

template<typename RiscvArchType=Riscv32>
using KillInterfaceType = SystemCallInterface<RiscvArchType, 129>;

template<typename RiscvArchType=Riscv32>
class KillParameters : public virtual SystemCallParameterInterface<RiscvArchType> {
    
    private:

    pid_t pid;
    int sig;

    public:

    using SystemCallParameterInterfaceType = KillParametersInterfaceType<RiscvArchType>;
    using SystemCallCodeType = typename SystemCallParameterInterfaceType::SystemCallCodeType;

    KillParameters(const pid_t pid_i, const int sig_i) : SystemCallParameterInterfaceType(), pid(pid_i), sig(sig_i) {}

    size_t count() override { return 2UL; }

    template<typename ParameterType>
    bool get(const size_t parameter_index, ParameterType & param);

    template<>
    bool get(const size_t parameter_index, int& param) {
        if(parameter_index == 0) {
            param = pid;
            return true;
        }
        else if(parameter_index == 1) {
            param = sig;
            return true;
        }
        
        return false;
    }
};

template<typename RiscvArchType=Riscv32>
class Kill : public virtual SystemCallInterface<RiscvArchType> {
  
    public:

    using SystemCallInterfaceType = KillInterfaceType<RiscvArchType>;

    using RiscvModeIntegerType = typename SystemCallInterfaceType::RiscvModeIntegerType;
    using SystemCallCodeType = typename SystemCallInterfaceType::SystemCallCodeType;
    
    using SystemCallParameterInterfaceType = SystemCallParameterInterface<RiscvArchType>;

    Kill() : SystemCallInterfaceType() {}

    // always returns false
    //
    template<typename ReturnType>
    void invoke(SystemCallParameterInterfaceType & parameters, ReturnType & value);

    // returns true
    //
    template<>
    void invoke(SystemCallParameterInterfaceType & parameters, int & value);
};

} /* end namespace RevCPU */ } // end namespace SST

#endif

// EOF