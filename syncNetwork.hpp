#ifndef SYNCNetwork_HPP
#define SYNCNetwork_HPP

#include "network.hpp"

class SyncNetwork 
{
public:
	int InitNetwork ();
	int Connect ();
	void UpdateData ();
private:
	CNetwork Network;
};

#endif