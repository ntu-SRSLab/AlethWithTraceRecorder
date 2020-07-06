#pragma once 
#ifndef  ALETH_TRACE_RECORDER_H
#define ALETH_TRACE_RECORDER_H

#include <cstdint>
#include <iostream>
#include <vector>
#include  "httplib.h"
void logMsg (const char* file, int  line,  std::string msg);
void logInfo(const char* file, int  line, std::string txHash, std::string contractAddress, std::vector<std::string> instructions);
#define LOGTrace(txHash, contractAddress, instructions) logInfo( __FILE__, __LINE__, txHash, contractAddress, instructions)
#define LOGMSG(msg)    logMsg( __FILE__, __LINE__, msg)
#define TRACE_CREATE  0
#define  TRACE_GET 1
#define  TRACE_RESET 2

class TraceRecorder
{
private:
    /** 
    *  @txHash: transaction hash value
    *  @contractAddress: contract address related to the transaction
    *  @instructions: the instruction traces within the transaction processing 
    */
    std::string txHash;
    std::string contractAddress;
    std::vector<std::string> instructions;    
    bool isRepeated;
    httplib::Client* m_cli;
public:
    TraceRecorder(/* args */){
        isRepeated = false;
        m_cli = new httplib::Client("localhost", 3000);
    }
    ~TraceRecorder(){
        delete m_cli;
    }
     // reset recorder context
     void reset(){
         if(!isRepeated){
            // LOGMSG("reset recorder");
            this->sendTrace();
         }
     }
     // add related information to the recorder context;     
     void addInstruction(std::string instruction){
         if(!isRepeated){
            // LOGMSG("add instruction");
            this->instructions.emplace_back(instruction);
            // LOGMSG(instruction);
         }
     }
     void addTxHash(std::string  txHash){
         if(txHash==this->txHash){
             isRepeated = true;
         }else {
            this->txHash = "";
            this->contractAddress = "";
            this->instructions.clear();
            // LOGMSG("add transaction hash");
            this->txHash = txHash;
            // LOGMSG(txHash);
            isRepeated = false;
         }
     }
     void  addContractAddress(std::string contractAddress){
         if(!isRepeated){
                // LOGMSG("add contract address");
                this->contractAddress = contractAddress;
                // LOGMSG(contractAddress);
         }
     }
     // network function
     void sendTrace();
};

TraceRecorder* CreateOrGetOrResetRecorder(int);
#endif

