//
//  ClientSocket.hpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/5/25.
//

#ifndef ClientSocket_hpp
#define ClientSocket_hpp

#pragma once
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>

class CClientSocket
{
public:
    CClientSocket(int port, const char * ServerIPAddress);
    void InitServerAddress(int port, const char * ServerIPAddress);
    bool CreateSocket();
    bool ConnectSocket();
    int GetSocketFD() const;
    void SetSocketFD(int SocketFD);
    const char * receiveMessage();
    bool sendMessage(const std::string & Buffer);
    static void ClientProc(CClientSocket * myself);
    char * GetBuffer();
    
    bool GetReceived();
    void SetReceived(bool received);
    void busyWaitting();
    
    ~CClientSocket();
private:
    //AF = Address Family
    static constexpr int IPV4 = AF_INET;
    static constexpr int TCP = SOCK_STREAM;
    sockaddr_in ServerAddress;
    int SocketFD;
    std::thread ClientThread;
    static constexpr int BufferSize = 8192;
    char ReceiveBuffer[BufferSize];
    static timeval timeout;//second, usecond
    bool received = 0;
};

#endif /* ClientSocket_hpp */
