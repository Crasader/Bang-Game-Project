//
//  ClientSocket.cpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/5/25.
//

#include "ClientSocket.hpp"
#include <nlohmann/json.hpp>
#include "NetworkCom.hpp"

#include <string.h>

CClientSocket* CClientSocket::myself = nullptr;

CClientSocket* CClientSocket::getInstance(){
    if(CClientSocket::myself == nullptr){
        CClientSocket::myself = new CClientSocket(28716, "104.199.215.104");
    }
    return CClientSocket::myself;
}

timeval CClientSocket::timeout;
CClientSocket::CClientSocket(int port, const char * ServerIPAddress)
{
    InitServerAddress(port, ServerIPAddress);
    CreateSocket();
    ConnectSocket();
    ClientThread = std::thread(ClientProc, this);
}
void CClientSocket::InitServerAddress(int port, const char * ServerIPAddress)
{
    memset(&ServerAddress, 0, sizeof(ServerAddress));
    
    //PF = Protocol Family
    ServerAddress.sin_family = PF_INET;
    //Kernel decided address
    ServerAddress.sin_addr.s_addr = inet_addr(ServerIPAddress);
    //Unified endian
    ServerAddress.sin_port = htons(port);
}
bool CClientSocket::CreateSocket()
{
    SocketFD = socket(IPV4, TCP, 0);
    if(SocketFD == -1)
    {
        return false;
    }
    return true;
}
bool CClientSocket::ConnectSocket()
{
    //bind socket address and port
    //true if success, otherwise failed
    setsockopt(SocketFD, SOL_SOCKET, SO_REUSEADDR, &ServerAddress, sizeof(ServerAddress));
    return connect(SocketFD, (sockaddr *)&ServerAddress, sizeof(ServerAddress)) != -1;
}
int CClientSocket::GetSocketFD() const
{
    return SocketFD;
}
void CClientSocket::SetSocketFD(int SocketFD)
{
    this->SocketFD = SocketFD;
}
const char * CClientSocket::receiveMessage()
{
    // true if there is some data need to be receive, otherwise the other side's socket has closed
    int ReceiveLength;
    if((ReceiveLength = recv(this->SocketFD, ReceiveBuffer, BufferSize-1, 0)) <= 0)
    {
        ReceiveBuffer[0] = '\0';
    }
    /*somehow it receive byte string without '\0'*/
    ReceiveBuffer[ReceiveLength] = '\0';
    return ReceiveBuffer;
}
bool CClientSocket::sendMessage(const std::string & Buffer)
{
    // true if successfully send data, otherwise failed
    return send(this->SocketFD, Buffer.c_str(), Buffer.size()+1, 0) != -1;
}
void CClientSocket::ClientProc(CClientSocket * myself)
{
    fd_set ReadFDSet;
    timeout = {0, 0};
    while(1)
    {
        FD_ZERO(&ReadFDSet);
        FD_SET(myself->SocketFD, &ReadFDSet);
        if(select(myself->SocketFD + 1, &ReadFDSet, NULL, NULL, &timeout) < 0)
        {
            //select() fail
            break;
        }
        if(FD_ISSET(myself->SocketFD, &ReadFDSet))
        {
            const char * ReceivedData = myself->receiveMessage();
            if(ReceivedData[0] != '\0')
            {

                std::thread ParseThread = std::thread(Client::HandleAction, ReceivedData);
                ParseThread.detach();
                printf("Received: %s\n", ReceivedData);
            }
            else
            {
                //如果與伺服器斷線就直接跳(退出thread) 看你在斷線時要什麼機制
                break;
            }
        }
    }
}
char * CClientSocket::GetBuffer()
{
    return ReceiveBuffer;
}
int CClientSocket::GetHandledAction()
{
    return HandledAction;
}
void CClientSocket::SetHandledAction(int HandledAction)
{
    this->HandledAction = HandledAction;
}
CClientSocket::~CClientSocket()
{
    shutdown(SocketFD, SHUT_RDWR);
    ClientThread.detach();
}
void CClientSocket::busyWaitting(int Action){
    while (this->GetHandledAction() != Action) {};
}
