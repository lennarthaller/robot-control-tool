#include "SyncNetwork.hpp"

int SyncNetwork::InitNetwork () {
	return (Network.NetworkInit());
}

int SyncNetwork::Connect () {
	return (Network.Connect());
}