#include "SyncNetwork.hpp"

int SyncNetwork::InitNetwork () {
	for (int i=0; i<271; i++) {
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

	m_bWasUpdated = false;

	return (Network.NetworkInit());
}

int SyncNetwork::Connect () {
	return (Network.Connect());
}

void SyncNetwork::UpdateData () {
	 if (Network.Recv () != -1) {
		
		 for (int i=0; i<4; i++) {
			m_nOdometryticks[i] = Network.GetData ();
		}
		for (int i=0; i<271; i++) {
			m_nScannerData[i] = static_cast <int> (Network.GetData () / 10.0);
		}
		for (int i=0; i<4; i++) {
			m_nMotorPower[i] = Network.GetData ();
		}
		m_fCalculatedDrivingDirection = static_cast<float> (Network.GetData ());
		m_fCalculatedDrivingDirection /= 100;
		m_fCalculatedDrivingDirection -= 90;
		m_fTargetDrivingDirection = static_cast<float> (Network.GetData ());
		m_fTargetDrivingDirection /= 100;
		m_fTargetDrivingDirection -= 90;
		m_fVoltage = (static_cast<float> (Network.GetData ()));
		m_fVoltage /= 100;
		m_nLoopTicks = (Network.GetData ()*10000);
		OdometryPositionData.nX = Network.GetData ()-15000;
		OdometryPositionData.nY = Network.GetData ()-15000;
		OdometryPositionData.fTheta = static_cast<float> (Network.GetData ());
		OdometryPositionData.fTheta = (OdometryPositionData.fTheta/1000)-10;

		m_bWasUpdated = true;
	 }

	 //Network.Clear();
}