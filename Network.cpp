#include "Network.hpp"

CNetwork::CNetwork (void) {
	AdressFromServer.sin_addr.s_addr = inet_addr ("192.168.100.72");
	AdressFromServer.sin_port = htons(7000);
	AdressFromServer.sin_family = AF_INET;
	
	m_nSizeOfServerSocket = sizeof(AdressFromServer);
	m_nOwnSocket = 0;
	m_nBytes = 0;
}

int CNetwork::NetworkInit (void) {

	WSADATA wsa;

	if (WSAStartup(MAKEWORD(1, 1), &wsa)) {
		std::cout << "Winsocket konnte nicht initalisiert werden!" << std::endl;
		return 1;
	}

	m_nOwnSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_nOwnSocket == -1) {
		std::cout << "Socket konnte nicht geoffnet weren!" << std::endl;
		return 1;
	}

	return 0;
}

int CNetwork::Connect () {
	u_long i = 224;

	if (connect (m_nOwnSocket, (struct sockaddr*) &AdressFromServer, sizeof(AdressFromServer)) == -1) {
		std::cout << "Verbinung Fehlgeschalgen!" << std::endl;
		return 1;
	}
	ioctlsocket (m_nOwnSocket, FIONBIO, &i); //socket = nonblocking
	//ioctlsocket (m_nOwnSocket, FIONREAD, &i); //socket = read 2 bytes 
	return 0;
}

int CNetwork::Recv (void) {
	for (int i=0; i<BUF_SIZE; i++) {
			m_chBuffer[i] = 0;
		}

	m_nRecvdBytes = recv (m_nOwnSocket, m_chBuffer, BUF_SIZE, 0);
	if (m_nRecvdBytes == SOCKET_ERROR) {
		return -1;
	}else{
		m_nBytes = 0;
		return 1;
	}
}

uint16_t CNetwork::GetData () {
	uint8_t i[2];
	uint16_t u = 0;
	i[0] = m_chBuffer[m_nBytes];
	m_nBytes ++;
	i[1] = m_chBuffer[m_nBytes];
	m_nBytes ++;
	u = ((i[1] << 8 ) | i[0])-1024;
	return u;
}

void CNetwork::Clear () { /////DEBUG
			for (int i=0; i<BUF_SIZE; i++) {
			m_chBuffer[i] = 0;
		}
}