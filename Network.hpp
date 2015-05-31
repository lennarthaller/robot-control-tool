#include <iostream>
#include <stdint.h>
#include <WS2tcpip.h>
#include <WinSock2.h>

#define BUF_SIZE 4096 //224 benötigt(?)

class CNetwork
{
public:
	CNetwork (void);
	int NetworkInit (void); 
	int Connect (void);
	int Recv (void);
	uint16_t GetData (void);
	void Clear (void);

private:
	char m_chBuffer[BUF_SIZE];
	int m_nOwnSocket;
	struct m_sSockaddr_in;
	socklen_t m_nSizeOfServerSocket;
	struct sockaddr_in AdressFromServer;
	int m_nRecvdBytes;
	int m_nBytes;
};

	