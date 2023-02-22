//
// SysCallChdir.h
//
// Copyright (C) 2017-2021 Tactical Computing Laboratories, LLC
// All Rights Reserved
// contact@tactcomplabs.com
//
// See LICENSE in the top level directory for licensing details
//
#pragma once
#ifndef __SYSTEMCALLCHDIR_H__
#define __SYSTEMCALLCHDIR_H__

#include "SystemCallInterface.h"
#include <type_traits>
#include <string>
#include <sys/types.h>

namespace SST { namespace RevCPU {

template<typename RiscvArchType=Riscv32>
using RevChdirCode = SystemCallInterfaceCode<RiscvArchType, 49>;

template<typename RiscvArchType=Riscv32>
int RevChdir(RevRegFile const& regFile, RevMem const& mem, RevInst const& inst);

} /* end namespace RevCPU */ } // end namespace SST

#endif

// EOF
