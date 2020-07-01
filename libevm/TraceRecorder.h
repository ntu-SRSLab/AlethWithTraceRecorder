#include <cstdint>
#include <iostream>
#include <vector>
#include  "cpp-httplib/httplib.h"

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
public:
    TraceRecorder(/* args */);
    ~TraceRecorder();
     // reset recorder context
     void reset();
     // add related information to the recorder context;     
     void addInstruction(std::string instruction);
     void addTxHash(std::string  txHash);
     void  addContractAddress(std::string contractAddress);

     // network function
     void sendTrace();

};

TraceRecorder::TraceRecorder(/* args */)
{
}

TraceRecorder::~TraceRecorder()
{
}

