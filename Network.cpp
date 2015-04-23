#include "Network.hpp"

CNetwork::CNetwork (void) {
	AdressFromServer.sin_addr.s_addr = inet_addr ("192.168.173.120");
	AdressFromServer.sin_port = htons(7000);
	AdressFromServer.sin_family = AF_INET;
	
	m_nSizeOfServerSocket = sizeof(AdressFromServer);
	m_nOwnSocket = 0;
}

int CNetwork::NetworkInit (void) {

	using namespace std;

	WSADATA wsa;

	if (WSAStartup(MAKEWORD(1, 1), &wsa)) {
		cout << "Winsocket konnte nicht initalisiert werden!" << endl;
		return 1;
	}

	m_nOwnSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (m_nOwnSocket == -1) {
		cout << "Socket konnte nicht geoffnet weren!" << endl;
		return 1;
	}

	return 0;
}

int CNetwork::Connect () {
	if (connect (m_nOwnSocket, (struct sockaddr*) &AdressFromServer, sizeof(AdressFromServer)) == -1) {
		std::cout << "Verbinung Fehlgeschalgen!" << std::endl;
		return 1;
	}

	return 0;
}

int CNetwork::Recv (void) {
	m_nRecvdBytes = recv (m_nOwnSocket, m_chBuffer, sizeof(m_chBuffer) -1, 0);
	if (m_nRecvdBytes == -1) {
		return 1;
	}else{
		return 0;
	}
}
