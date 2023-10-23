// $Id$
//
//    File: CalorimeterDigiHit_factory.cc
// Created: Wed Jan 27 16:39:57 CET 2016
// Creator: celentan (on Linux apcx4 2.6.32-504.30.3.el6.x86_64 x86_64)
//

#include <iostream>
#include <iomanip>
using namespace std;

//objects we need from the framework
#include <TT/TranslationTable.h>
#include "CalorimeterRawDataHit.h"
//objects we put in the framework
#include <Calorimeter/CalorimeterDigiHit.h>

#include "CalorimeterDigiHit_factory.h"
using namespace jana;

//------------------
// init
//------------------
jerror_t CalorimeterDigiHit_factory::init(void) {
	return NOERROR;
}

//------------------
// brun
//------------------
jerror_t CalorimeterDigiHit_factory::brun(jana::JEventLoop *eventLoop,
		int32_t runnumber) {

	return NOERROR;
}

//------------------
// evnt
//------------------
jerror_t CalorimeterDigiHit_factory::evnt(JEventLoop *loop,
		uint64_t eventnumber) {

	TranslationTable::CALO_Index_t m_channel;
	CalorimeterDigiHit *m_CalorimeterDigiHit = 0;

	//1: Here, we get from the framework the objects we need to process
	//1a: create vectors
	vector<const CalorimeterRawDataHit*> m_CalorimeterSiPMHits;
	vector<const CalorimeterRawDataHit*>::const_iterator it;
	const CalorimeterRawDataHit* m_CalorimeterRawDataHit;
	//1b: retrieve CalorimeterSiPMHit objects
	loop->Get(m_CalorimeterSiPMHits);

	for (it = m_CalorimeterSiPMHits.begin(); it != m_CalorimeterSiPMHits.end();
			it++) {
		m_CalorimeterRawDataHit = (*it);
		m_CalorimeterDigiHit = new CalorimeterDigiHit();
		m_CalorimeterDigiHit->m_channel =
				*(m_CalorimeterRawDataHit->m_channel.calorimeter);
		m_CalorimeterDigiHit->Q = m_CalorimeterRawDataHit->Q;
		m_CalorimeterDigiHit->T = m_CalorimeterRawDataHit->T;
		m_CalorimeterDigiHit->A = m_CalorimeterRawDataHit->A;
		m_CalorimeterDigiHit->pedMean = m_CalorimeterRawDataHit->pedMean;
		m_CalorimeterDigiHit->pedRMS = m_CalorimeterRawDataHit->pedRMS;
		m_CalorimeterDigiHit->RMSflag = m_CalorimeterRawDataHit->RMSflag;
		m_CalorimeterDigiHit->AddAssociatedObject(m_CalorimeterRawDataHit);
		_data.push_back(m_CalorimeterDigiHit);
	}

	return NOERROR;
}

//------------------
// erun
//------------------
jerror_t CalorimeterDigiHit_factory::erun(void) {
	return NOERROR;
}

//------------------
// fini
//------------------
jerror_t CalorimeterDigiHit_factory::fini(void) {
	return NOERROR;
}

