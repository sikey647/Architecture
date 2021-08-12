#include <string>
#include <vector>

struct ServerAddr {
    std::string ip;
    uint32_t port;
};

class ConnPool {
   public:
    ConnPool();
    virtual ~ConnPool();

   private:
    std::vector<ServerAddr> m_addrs;
    uint32_t m_timeout;
};