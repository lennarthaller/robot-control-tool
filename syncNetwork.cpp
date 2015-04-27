#include "SyncNetwork.hpp"

int SyncNetwork::InitNetwork () {
	for (int i=0; i<100; i++) {
		m_nScannerData[i] = 0;
	}
	for (int i=0; i<4; i++) {
		m_nOdometryticks[i] = 0;
	}
	for (int i=0; i<4; i++) {
		m_nMotorPower[i] = 0;
	}
	m_fCalculatedDrivingDirection = 0.0;
	m_fTargetDrivingDirection = 0.0;
	m_fVoltage = 0.0;
	m_nLoopTicks = 0;

	return (Network.NetworkInit());
}

int SyncNetwork::Connect () {
	return (Network.Connect());
}

void SyncNetwork::UpdateData () {
	for (int i=0; i<100; i++) {
		m_nScannerData[i] = Network.Recv ();
	}
	for (int i=0; i<4; i++) {
		m_nOdometryticks[i] = Network.Recv ();
	}
	for (int i=0; i<4; i++) {
		m_nMotorPower[i] = Network.Recv ();
	}
	m_fCalculatedDrivingDirection = (static_cast<float> (Network.Recv ()/10));
	m_fTargetDrivingDirection = (static_cast<float> (Network.Recv ()/10));
	m_fVoltage = (static_cast<float> (Network.Recv ()/10));
	m_nLoopTicks = Network.Recv ();
}