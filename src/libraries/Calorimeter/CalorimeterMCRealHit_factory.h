// $Id$
//
//    File: CalorimeterMCRealHit_factory.h
// Created: Wed Feb 22 15:46:35 CET 2017
// Creator: celentan (on Linux apcx4 2.6.32-504.30.3.el6.x86_64 x86_64)
//

#ifndef _CalorimeterMCRealHit_factory_
#define _CalorimeterMCRealHit_factory_

#include <JANA/JFactory.h>
#include "CalorimeterMCRealHit.h"

class CalorimeterMCRealHit_factory: public jana::JFactory<CalorimeterMCRealHit> {
public:
	CalorimeterMCRealHit_factory() {
	}
	;
	~CalorimeterMCRealHit_factory() {
	}
	;

private:
	jerror_t init(void);						///< Called once at program start.
	jerror_t brun(jana::JEventLoop *eventLoop, int32_t runnumber);	///< Called everytime a new run number is detected.
	jerror_t evnt(jana::JEventLoop *eventLoop, uint64_t eventnumber);	///< Called every event.
	jerror_t erun(void);						///< Called everytime run number changes, provided brun has been called.
	jerror_t fini(void);						///< Called after last event of last event source has been processed.

	int isMC;

	std::map<TranslationTable::CALO_Index_t, CalorimeterMCRealHit*> m_map;
	std::map<TranslationTable::CALO_Index_t, CalorimeterMCRealHit*>::iterator m_map_it;
};

#endif // _CalorimeterMCRealHit_factory_

