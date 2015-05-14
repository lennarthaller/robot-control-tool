#ifndef SYNCNetwork_HPP
#define SYNCNetwork_HPP

#include "network.hpp"

class SyncNetwork 
{
public:
	int InitNetwork ();
	int Connect ();
	void UpdateData ();

	int* GetScannerData () {return m_nScannerData;}
	int* GetOdometryTicks () {return m_nOdometryticks;}
	int* GetMotorPower () {return m_nMotorPower;}
	float GetCalculatedDrivingDirection () {return m_fCalculatedDrivingDirection;}
	float GetTargetDrivingDirection () {return m_fTargetDrivingDirection;}
	float GetVoltage () {return m_fVoltage;}
	int	 GetLoopTicks () {return m_nLoopTicks;}
	bool GetWasUpdated () {return m_bWasUpdated;}
	void SetWasUpdated (bool bUpdated) {m_bWasUpdated = bUpdated;}

private:
	CNetwork Network;

	int m_nScannerData[100];
	int m_nOdometryticks[4];
	int m_nMotorPower[4];
	float m_fCalculatedDrivingDirection;
	float m_fTargetDrivingDirection;
	float m_fVoltage;
	int m_nLoopTicks;

	bool m_bWasUpdated;
};

#endif