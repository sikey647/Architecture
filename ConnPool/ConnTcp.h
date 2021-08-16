#include <string>

class ConnTcp {
   public:
    // 创建 tcp 连接
    ConnTcp(const std::string &ip, uint32_t port, uint32_t timeout);
    virtual ~ConnTcp();

    int connect();
    int read(const void *readBuf, const int size);
    int write(const void *readBuf, const int size);

    int setBlock();
    int setNonBlock();
    int setTimeout();

   private:
    int m_sockfd;
    std::string m_ip;
    uint32_t m_port;
};