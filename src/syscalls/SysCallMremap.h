//
// SysCallMmap.h
//
// Copyright (C) 2017-2021 Tactical Computing Laboratories, LLC
// All Rights Reserved
// contact@tactcomplabs.com
//
// See LICENSE in the top level directory for licensing details
//
#pragma once
#ifndef __SYSTEMCALLMREMAP_H__
#define __SYSTEMCALLMREMAP_H__

#include "SystemCallInterface.h"
#include <type_traits>

namespace SST { namespace RevCPU {

template<typename RiscvArchType=Riscv32>
using MremapInterfaceType = SystemCallInterface<RiscvArchType, 216>;

template<typename RiscvArchType=Riscv32>
class MremapParameters : public virtual SystemCallParameterInterface<RiscvArchType> {
    
    private:

    void * oldaddr;
    void * newaddr;
    size_t oldsize;
    size_t newsize;
    int flags;

    public:

    using SystemCallParameterInterfaceType = MremapParametersInterfaceType<RiscvArchType>;
    using SystemCallCodeType = typename SystemCallParameterInterfaceType::SystemCallCodeType;

    MremapParameters(void * addrp, size_t oldsz, size_t newsz, int flagsp)
        : SystemCallParameterInterfaceType(), addr(addrp), len(lenp), prot(protp), flags(flagsp), newaddr(std::nullptr) {}

    MremapParameters(void * oaddr, size_t oldsz, size_t newsz, int flagsp, void * naddr)
        : SystemCallParameterInterfaceType(), oldaddr(oaddr), oldsize(oldsz), newsize(newsz), flags(flagsp), newaddr(naddr) {}

    size_t count() override { return (newaddr == std::nullptr) ? 5UL : 6UL; }

    template<typename ParameterType>
    bool get(const size_t parameter_index, ParameterType & param);

    template<>
    bool get(const size_t parameter_index, void_ptr & param) {
        if(parameter_index == 0) {
            param = oldaddr;
            return true;
        }
        else if(parameter_index == 4 && (newaddr == std::nullptr) ) {
            param = newaddr;
            return true;
        }

        return false;
    }

    template<>
    bool get(const size_t parameter_index, int & param) {
        if(parameter_index == 3) {
            param = flags;
            return true;
        }

        return false;
    }

    template<>
    bool get(const size_t parameter_index, size_t & param) {
        if(parameter_index == 1) {
            param = oldsize;
            return true;
        }
        else if(parameter_index == 2) {
            param = newsize;
            return true;
        }

        return false;
    }
};

template<typename RiscvArchType=Riscv32>
class Mremap : public virtual SystemCallInterface<RiscvArchType> {
  
    public:

    using SystemCallInterfaceType = MremapInterfaceType<RiscvArchType>;

    using RiscvModeIntegerType = typename SystemCallInterfaceType::RiscvModeIntegerType;
    using SystemCallCodeType = typename SystemCallInterfaceType::SystemCallCodeType;
    
    using SystemCallParameterInterfaceType = SystemCallParameterInterface<RiscvArchType>;

    public:

    Mremap() : SystemCallInterfaceType() {}

    // always returns false
    //
    template<typename ReturnType>
    void invoke(SystemCallParameterInterfaceType & parameters, ReturnType & value);

    // returns true
    //
    template<>
    void invoke(SystemCallParameterInterfaceType & parameters, void_t & value);
};

} /* end namespace RevCPU */ } // end namespace SST

#endif

// EOF