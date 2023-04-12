#include "../RevSysCalls.h"
#include "../RevSysCallInterface.h"
#include <filesystem>

#include <unistd.h>

struct RevFork {
  // ecall (a7 = 2) -> fork
  static const int value = 220; 
  
  template<typename RiscvArchType>
  static int ECall(RevRegFile& regFile, RevMem& mem, RevInst& inst) {

    std::cout << "INSIDE FORK" << std::endl;
    if constexpr (std::is_same<RiscvArchType, Riscv32>::value){

    }
    
    else if (std::is_same<RiscvArchType, Riscv64>::value){
      mem
    
    // pid_t rc = fork();
    return rc;
  }
};
