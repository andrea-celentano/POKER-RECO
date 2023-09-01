// $Id$
//
//    File: Cerenkov_factory.cc
// Created: Sat Jul 29 03:31:37 EDT 2023
// Creator: clasana (on Linux jdaq8 3.10.0-1160.88.1.el7.x86_64 x86_64)
//

#include <iostream>
#include <iomanip>
using namespace std;

#include "CerenkovHit_factory.h"
#include <DAQ/fa250Mode1CalibPedSubHit.h>
#include <DAQ/fa250WaveboardV1Hit.h>
#include <TT/TranslationTable.h>
using namespace jana;

//------------------
// init
//------------------
jerror_t CerenkovHit_factory::init(void) {

	m_thr_analog = 20;
	m_thr_digital = 20;
	m_pedestal = 15;
	m_scale = -1;
	gPARMS->SetDefaultParameter("CERENKOV:THR_ANALOG", m_thr_analog,
			"thr in mV for analogue");
	gPARMS->SetDefaultParameter("CERENKOV:THR_DIGITAL", m_thr_digital,
			"thr in mV for digital");
	gPARMS->SetDefaultParameter("CERENKOV:NPED", m_pedestal,
				"num samples pedestal");
	 gPARMS->SetDefaultParameter("CERENKOV:SCALE", m_scale, "Common scale factor");
	return NOERROR;
}

//------------------
// brun
//------------------
jerror_t CerenkovHit_factory::brun(jana::JEventLoop *eventLoop,
		int32_t runnumber) {

	jout << "CerenkovHit_factory::brun new run number: " << runnumber
			<< endl;
	m_tt = 0;
	eventLoop->GetSingle(m_tt);
	if (m_tt == 0) {
		jerr << " unable to get the TranslationTable from this run!" << endl;
		return OBJECT_NOT_AVAILABLE;
	}

	/*this->updateCalibrationHandler(m_wb_gain, eventLoop);

	if (VERBOSE > 3) {
		std::map<TranslationTable::CALO_Index_t, std::vector<double> > gainCalibMap;
		std::map<TranslationTable::CALO_Index_t, std::vector<double> >::iterator gainCalibMap_it;
		gainCalibMap = m_wb_gain->getCalibMap();
		jout << "Got following wb_gain for run number: " << runnumber << endl;
		jout << "Rows: " << gainCalibMap.size() << endl;
		for (gainCalibMap_it = gainCalibMap.begin();
				gainCalibMap_it != gainCalibMap.end(); gainCalibMap_it++) {
			jout << gainCalibMap_it->first.sector << " "
					<< gainCalibMap_it->first.x << " "
					<< gainCalibMap_it->first.y << " "
					<< gainCalibMap_it->first.readout << " "
					<< gainCalibMap_it->second.at(0) << endl;
		}
	}
*/
	jout << "CerenkovaHit_factory::brun done" << endl;

	return NOERROR;
}

//------------------
// evnt
//------------------
jerror_t CerenkovHit_factory::evnt(JEventLoop *loop, uint64_t eventnumber) {

	// Code to generate factory data goes here. Add it like:
	//
	// Cerenkov *myCerenkov = new Cerenkov;
	// myCerenkov->x = x;
	// myCerenkov->y = y;
	// ...
	// _data.push_back(myCerenkov);
	//
	// Note that the objects you create here will be deleted later
	// by the system and the _data vector will be cleared automatically.

	CerenkovHit *m_CerenkovHit = 0;
	TranslationTable::ChannelInfo m_channel;
	TranslationTable::csc_t m_csc;

	//1: Here, we get from the framework the objects we need to process
	//1a: create vectors
	vector<const fa250Mode1CalibPedSubHit*> m_fa250Mode1CalibPedSubHit;
	vector<const fa250Mode1CalibPedSubHit*>::const_iterator it_fa250Mode1CalibPedSubHit;

	//1b: retrieve objects
	loop->Get(m_fa250Mode1CalibPedSubHit);


	/*2: Now we have the daq objects, still indexed as "crate-slot-channel"
	*/


	 for (it_fa250Mode1CalibPedSubHit = m_fa250Mode1CalibPedSubHit.begin(); it_fa250Mode1CalibPedSubHit != m_fa250Mode1CalibPedSubHit.end();
	            it_fa250Mode1CalibPedSubHit++) {

	        const fa250Mode1CalibPedSubHit *hit = (*it_fa250Mode1CalibPedSubHit);
	        m_channel = m_tt->getChannelInfo(hit->m_channel);

	        if (m_channel.det_sys == TranslationTable::CERENKOV){

	        	 double ped = 0;
	        	 double A=-9999;
	        	 for (int jj = 0; jj < hit->samples.size(); jj++) {
	        		 if (jj < m_pedestal)
	        		    ped += hit->samples[jj]*m_scale;
	        		 if (hit->samples[jj]*m_scale > A) {
	        		    A = hit->samples[jj]*m_scale;
	        		 }
	        	 }
	        	 A = A - ped/(m_pedestal);

	        	 bool isGood=0;
	        	 //Analogue channel
	        	 if (m_channel.cerenkov->readout==0){
	        		 isGood = (A>m_thr_analog);
	        	 }
	        	 //Digital
	        	 if (m_channel.cerenkov->readout==1){
	        	 	 isGood = (A>m_thr_digital);
	        	 }

	        	 if (isGood){
	        		 m_CerenkovHit = new CerenkovHit();
	        		 m_CerenkovHit->m_channel = *(m_channel.cerenkov);
	        		 m_CerenkovHit->AddAssociatedObject(hit);
	        		 _data.push_back(m_CerenkovHit);
	        	 }
	        }

	 }


	return NOERROR;
}

//------------------
// erun
//------------------
jerror_t CerenkovHit_factory::erun(void) {
	return NOERROR;
}

//------------------
// fini
//------------------
jerror_t CerenkovHit_factory::fini(void) {
	return NOERROR;
}

