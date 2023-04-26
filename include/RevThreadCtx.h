//
// _RevThreadCtx_h_
//
// Copyright (C) 2017-2023 Tactical Computing Laboratories, LLC
// All Rights Reserved
// contact@tactcomplabs.com
//
// See LICENSE in the top level directory for licensing details
//
//

/***
RevThreadCtx 

Memory Actions:
- RelinquishMem
- ShareMem
***/

#include <cstdint>
#include <vector>
#include "../include/RevMem.h"
#include "RevInstTable.h"

enum class ThreadState {
  Running,
  Waiting,
  Sleeping,
  Dead,
};

class RevThreadCtx {

private: 
  // FIXME: Maybe make this private? 
  uint32_t PID;
  uint32_t ParentPID;

  ThreadState State = ThreadState::Waiting;
  RevRegFile RegFile; 

  uint64_t MemStartAddr;
  uint64_t MemSize;

  std::vector<uint32_t> ChildrenPIDs = {};

public:
  // Constructor that takes a RevRegFile object and a uint32_t ParentPID
  RevThreadCtx(const uint32_t inputPID, const RevRegFile& inputRevRegFile, uint32_t inputParentPID,
               uint64_t inputMemStartAddr, uint64_t inputMemSize )
      : PID(inputPID), ParentPID(inputParentPID), RegFile(inputRevRegFile), 
        MemStartAddr(inputMemStartAddr), MemSize(inputMemSize)
  {
  }

  RevRegFile& GetRegFile() { return RegFile; }

  uint32_t GetPID() { return PID; }
  void SetPID(uint32_t NewPID) { PID = NewPID; }

  uint32_t GetParentPID() const { return ParentPID; }
  void SetParentPID(uint32_t parent_pid) { ParentPID = parent_pid; }

  ThreadState GetState() const { return State; }
  void SetState(ThreadState newState) { State = newState; }

  uint64_t GetMemSize() { return MemSize; }
  uint64_t GetMemStartAddr() { return MemStartAddr; }

  bool AddChildPID(uint32_t pid);
  bool RemoveChildPID(uint32_t pid);

  bool isRunning(){ return ( State == ThreadState::Running ); }
  // bool isReady(){ return (State == ThreadState::Ready); }
  bool isWaiting(){ return (State == ThreadState::Waiting); }
  // bool isTerminated(){ return (State == ThreadState::Terminated); }
  bool isDead(){ return (State == ThreadState::Dead); }

};


