#ifndef SYNCNetwork_HPP
#define SYNCNetwork_HPP

#include "network.hpp"

class SyncNetwork 
{
public:
	int InitNetwork ();
	int Connect ();
private:
	CNetwork Network;
};

#endif