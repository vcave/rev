//
// Created by alefel on 12/07/23.
//

#ifndef UPDOWN_MMESSAGE_H
#define UPDOWN_MMESSAGE_H

#include <iostream>
#include <iomanip>
#include <assert.h>
#include <memory>
#include "lanetypes.hh"

namespace basim {

    enum class MType{
        M1Type = 0,
        M2Type = 1,
        M3Type = 2,
        M3Type_M = 3,
        M4Type = 4,
        M4Type_M = 5
    };

    class MMessage {
    private:
        /// Destination event word/Destination event label
        /// The destination event word contains information about the event to be triggered into execution at the destination.
        eventword_t eventWord;

        /// Continuation word / continuation event label
        /// The continuation word to be triggered following the destination event's execution.
        eventword_t continuationWord;
        
        // when message can be popped
        uint64_t _when;

        // PayLoad len
        uint64_t len;

        // Payload data 
        std::shared_ptr<word_t []> payload;

        // Type of Message
        MType mtype;

        // Mode of messages
        uint8_t mode;

        // Destination Address
        Addr destaddr;

    public:
        MMessage() = delete;

        MMessage(MMessage const &) = delete;

        //MMessage &operator=(MMessage const &) = delete;

        MMessage(eventword_t xc, eventword_t xe, MType _mtype) {
            setXc(xc);
            setXe(xe);
            mtype = _mtype;
        }

        void setXe(eventword_t newXe) { eventWord = newXe; }
        
        void setXc(eventword_t newXc) { continuationWord = newXc; }

        eventword_t getXe() { return eventWord; };

        eventword_t getXc() { return continuationWord; };

        uint64_t when() { return _when;};
        
        void setWhen(uint64_t when) {_when = when;}

        MType getType(){return mtype;}

        void addpayload(std::shared_ptr<word_t[]> data){payload = std::move(data);}
        
        std::shared_ptr<word_t[]> getpayload(){return payload;}
        
        bool isStore(){return ((mode & 0x1) == 1);}
        
        bool setMode(int _mode){return ((mode & 0x1) == 1);}
        
        void setLen(uint64_t _len){len = _len;}
        
        uint64_t getLen(){return len;}
        
        Addr getdestaddr() { return destaddr; }
        
        void setdestaddr(Addr _destaddr) {destaddr = _destaddr; }
    };

typedef MMessage* MMessagePtr;


    // Need to rewrite this.
    //inline std::ostream &operator<<(std::ostream &str, M1Message &mMessage) {
    //    str << "m: 0x" << std::hex << mMessage.getM() << ", len: 0x" << mMessage.getLen() << ", xptr: 0x"
    //        << mMessage.getXptr() << "Xc: 0x" << mMessage.getXc() << ", Xe: 0x" << mMessage.getXe();
    //    str << "(0x0" << std::setw(8) << std::setfill('0')
    //        << (mMessage.getM() << 26 || mMessage.getLen() << 22 || mMessage.getXptr() << 17 ||
    //            mMessage.getXc() << 12 || mMessage.getXe());
    //    str << ") " << std::dec;
    //    return str;
    //}

    //inline std::ostream &operator<<(std::ostream &str, M2Message &mMessage) {
    //    str << "destaddr: 0x" << std::hex << mMessage.getdestaddr() << "m: 0x" << mMessage.getM() << ", len: 0x"
    //        << mMessage.getLen() << ", xptr: 0x"
    //        << mMessage.getXptr() << "Xc: 0x" << mMessage.getXc() << ", Xe: 0x" << mMessage.getXe();
    //    str << "(0x0" << std::setw(8) << std::setfill('0')
    //        << (mMessage.getdestaddr() << 27 || mMessage.getM() << 25 || mMessage.getLen() << 22 ||
    //            mMessage.getXptr() << 17 ||
    //            mMessage.getXc() << 12 || mMessage.getXe()
    //                    << 7);
    //    str << ") " << std::dec;
    //    return str;
    //}

    //inline std::ostream &operator<<(std::ostream &str, M3Message &mMessage) {
    //    str << "destaddr: 0x" << std::hex << mMessage.getdestaddr() << "m: 0x" << mMessage.getM() << ", x2: 0x"
    //        << mMessage.getX2() << ", x1: 0x"
    //        << mMessage.getX1() << "Xc: 0x" << mMessage.getXc() << ", Xe: 0x" << mMessage.getXe();
    //    str << "(0x0" << std::setw(8) << std::setfill('0')
    //        << (mMessage.getdestaddr() << 27 || mMessage.getM() << 26 || mMessage.getX2() << 22 ||
    //            mMessage.getX1() << 17 ||
    //            mMessage.getXc() << 12 || mMessage.getXe()
    //                    << 7);
    //    str << ") " << std::dec;
    //    return str;
    //}

    //inline std::ostream &operator<<(std::ostream &str, M4Message &mMessage) {
    //    str << std::hex << "destaddr: 0x" << mMessage.getdestaddr() << "m: 0x" << mMessage.getM() << ", numops: 0x"
    //        << mMessage.getNumops() << ", xop: 0x"
    //        << mMessage.getXop() << "Xc: 0x" << mMessage.getXc() << ", Xe: 0x" << mMessage.getXe();
    //    str << "(0x0" << std::setw(8) << std::setfill('0')
    //        << (mMessage.getdestaddr() << 27 || mMessage.getM() << 26 || mMessage.getNumops() << 22 ||
    //            mMessage.getXop() << 17 ||
    //            mMessage.getXc() << 12 || mMessage.getXe()
    //                    << 7);
    //    str << ") " << std::dec;
    //    return str;
    //}
}

#endif //UPDOWN_MMESSAGE_H
