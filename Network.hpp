#include <iostream>
#include <stdint.h>
#include <WS2tcpip.h>

#define BUF_SIZE 4096

class CNetwork
{
public:
	char m_chBuffer [BUF_SIZE];

	CNetwork (void);
	int NetworkInit (void); 
	int Connect (void);
	int Recv (void);

private:
	int m_nOwnSocket;
	struct m_sSockaddr_in;
	socklen_t m_nSizeOfServerSocket;
	struct sockaddr_in AdressFromServer;
	int m_nRecvdBytes;
};

	