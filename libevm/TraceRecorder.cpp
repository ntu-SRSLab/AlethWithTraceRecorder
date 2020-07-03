
#include "TraceRecorder.h"
#include  <libethereum/StandardTrace.h>

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
      s +="\"" +*p+"\"";
      if (p != v.end() - 1)
        s += c;
   }
}
void TraceRecorder::sendTrace(){
    
         LOGMSG("send trace");
         LOGTrace(this->txHash, this->contractAddress, this->instructions);
      
         std::string instructions;
         join(this->instructions, ',' , instructions);
         instructions = "[" + instructions +"]";

        //  Json::Value post;
        //  post["hash"] = "0x"+this->txHash;
        //  post["address"] = "0x"+this->contractAddress;
        //  post["trace"] = instructions;
        // LOGMSG(post.asString());

        std::string json = "{\"hash\": \"0x"+this->txHash+"\"," +"\"address\":\""+"0x"+this->contractAddress+"\","+      \
                                            "\"trace\":"+instructions+"}";
        LOGMSG(json);
        LOGMSG("will send trace to vultron server");
        httplib::Client cli("localhost", 3000);
        auto res = cli.Get("/");
        if (res && res->status == 200) {
              LOGMSG("connected to vultron server");
               res = cli.Post("/fuzz", json, "application/json");
               if (res && res->status == 200) {
                   std::cout  << "[" << __FILE__ <<":"<< __LINE__<<   "]" << res->body << std::endl;
                }else{
                   std::cerr<< "[" << __FILE__ <<":"<< __LINE__<<   "]" <<"cannot transfer trace info to vultron server" << std::endl;
              }
         }else{
                  std::cerr<< "[" << __FILE__ <<":"<< __LINE__<<   "]" << "cannot connect to vultron server" << std::endl;
        }

}