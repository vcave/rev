//
// SysCallChdir.cc
//
// Copyright (C) 2017-2021 Tactical Computing Laboratories, LLC
// All Rights Reserved
// contact@tactcomplabs.com
//
// See LICENSE in the top level directory for licensing details
//
#include "SysCallChdir.h"

#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>

namespace SST { namespace RevCPU {

template<>
int Chdir<Riscv32>::invoke(RevRegFile const& regFile, RevMem const& mem, RevInst const& inst) {
   std::size_t strlen = 0;
   memory.FindStringTerminal(dt_u32(td_u32(regFile.RV32[inst.rs1],32)), strlen);

   char addr[strlen];
   memory.ReadMem(dt_u32(td_u32(regFile.RV32[inst.rs1],32), sizeof(char)*strlen, &addr);

   const int rc = chdir(&addr);
   regFile.RV32[inst.rd] = rc;
   regFile.RV32_PC += inst.instSize;
   return rc; 
}

template<>
int Chdir<Riscv64>::invoke(RevRegFile const& memregfile, RevMem const& revmemory, RevInst const& inst) {
   std::size_t strlen = 0;
   memory.FindStringTerminal(dt_u64(td_u64(regFile.RV64[inst.rs1],64)), strlen);

   char addr[strlen];
   memory.ReadMem(dt_u64(td_u64(regFile.RV64[inst.rs1],64), sizeof(char)*strlen, &addr);

   const int rc = chdir(&addr);
   regFile.RV64[inst.rd] = rc;
   regFile.RV64_PC += inst.instSize;
   return rc; 
}

template<>
int Chdir<Riscv128>::invoke(RevRegFile const& memregfile, RevMem const& revmemory, RevInst const& inst) {
}

} /* end namespace RevCPU */ } // end namespace SST
