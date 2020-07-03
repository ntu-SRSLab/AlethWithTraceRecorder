
#include "TraceRecorder.h"

TraceRecorder* CreateOrGetOrResetRecorder(int cmd){
    static TraceRecorder recoder;
    switch (cmd)
    {
    case TRACE_CREATE:
        /* code */
        break;
    case TRACE_GET:
        break;
    case  TRACE_RESET:
        recoder.reset();
        break;
    default:
        break;
    }
    return &recoder;
}

void logInfo(const char* file, int  line, std::string txHash, std::string contractAddress, std::vector<std::string> instructions)
{
     std::cout << "[" << file <<":"<< line<<   "]" << txHash << std::endl;
     std::cout<< "[" << file <<":"<< line<<   "]"<< contractAddress << std::endl;
     for(auto& instruction: instructions ){
         std::cout<< "[" << file <<":"<< line<< "]"<< instruction << std::endl;
     }
}
void logMsg(const char* file, int  line,  std::string msg)
{
     std::cout << "[" << file <<":"<< line<<   "]" <<msg << std::endl;
}
void join(const std::vector<std::string>& v, const char&c, std::string& s) {

   s.clear();

   for (auto p = v.begin(); p != v.end(); ++p) {
      s += *p;
      if (p != v.end() - 1)
        s += c;
   }
}
void TraceRecorder::sendTrace(){
         LOGMSG("send trace");
         LOGTrace(this->txHash, this->contractAddress, this->instructions);
         httplib::Client cli("localhost", 3000);
         std::string instructions;
         join(this->instructions, ',' , instructions);
         instructions = "[" + instructions +"]";
         httplib::Params params{
            { "hash", this->txHash },
            { "address", this->contractAddress },
             {"trace", instructions}
        };
        auto res = cli.Post("/fuzz", params);
}