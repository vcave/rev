#include "../RevSysCalls.h"
#include "../RevSysCallInterface.h"
#include <filesystem>

#include <sched.h>

struct RevClone {
  // ecall (a7 = 120) -> clone
  static const int value = 120; 
  
  template<typename RiscvArchType>
  static int ECall(RevRegFile& regFile, RevMem& mem, RevInst& inst) {
    if constexpr (std::is_same<RiscvArchType, Riscv32>::value){
      int (*fnptr)(void*) = nullptr;
      mem.ReadMem(regFile.RV32[10] , sizeof(fnptr), &fnptr);
      void * stack = nullptr;
      mem.ReadMem(regFile.RV32[11] , sizeof(void*), &stack);
      int flags = regFile.RV32[12];
      void * arg = nullptr;
      mem.ReadMem(regFile.RV32[12] , sizeof(void*), &arg);

      // inst.jumpTarget
    
      // const int rc = clone(fnptr, stack, flags, arg);
      return rc; 
    }
    else if (std::is_same<RiscvArchType, Riscv64>::value){
      int (*fnptr)(void*) = nullptr;
      mem.ReadMem(regFile.RV64[10] , sizeof(fnptr), &fnptr);
      void * stack = nullptr;
      mem.ReadMem(regFile.RV64[11] , sizeof(void*), &stack);
      int flags = regFile.RV64[12];
      void * arg = nullptr;
      mem.ReadMem(regFile.RV64[12] , sizeof(void*), &arg);
    
      //
      /***
      1. Check for CLONE_VM (clone virtual memory) flag
          - If set: New process/thread will share same virtual memory
                     as calling process
          - If not: New process/thread has a separate memory space
      2. Copy/Share resources (ie. File descriptors, signal handlers, memory mappings etc.) 
          - This is all based on FLAGS (usually handled by kernel)
      3. Set up new stack
          - Setup stack
            - Because we don't have multithreading we will save a pointer 
              to the calling processes stack pointer, execute the childs stack
              return to parent 
            - MAYBE? Setup stack frame
            - Begin execution at address in thread_entry_point (ie. a2 register)
      4. [N/A] Update Process Table (Kernel usually does this... not sure what we will do)
      5. [N/A] Schedule new process/thread (Kernel's scheduler will schedule)
      ***/


      /***
      OUR RESTRICTIONS: 
      - Child must exit before Parent resumes its execution

      FUTURE TODO:
      - Deal with interprocess communication
      ***/
    }
    return -1;
  }
};
