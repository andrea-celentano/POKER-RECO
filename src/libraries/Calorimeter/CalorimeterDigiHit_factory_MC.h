// $Id$
//
//    File: CalorimeterDigiHit_factory_MC.h
// Created: Tue Mar  1 17:38:32 CET 2016
// Creator: celentan (on Linux localhost.localdomain 2.6.32-573.12.1.el6.x86_64 x86_64)
//

#ifndef _CalorimeterDigiHit_factory_MC_
#define _CalorimeterDigiHit_factory_MC_

#include <JANA/JFactory.h>
#include "CalorimeterDigiHit.h"

class CalorimeterMCHit;

class CalorimeterDigiHit_factory_MC:public jana::JFactory<CalorimeterDigiHit>{
public:
	CalorimeterDigiHit_factory_MC(){};
	~CalorimeterDigiHit_factory_MC(){};
	const char* Tag(void){return "MC";}

	static void SetIndex(TranslationTable::CALO_Index_t &index,const CalorimeterMCHit *mchit,int MC);



private:
	jerror_t init(void);						///< Called once at program start.
	jerror_t brun(jana::JEventLoop *eventLoop, int32_t runnumber);	///< Called everytime a new run number is detected.
	jerror_t evnt(jana::JEventLoop *eventLoop, uint64_t eventnumber);	///< Called every event.
	jerror_t erun(void);						///< Called everytime run number changes, provided brun has been called.
	jerror_t fini(void);						///< Called after last event of last event source has been processed.

	/*This code is here because MC could generate more than 1 hit per sector!*/
	/*The key is the way MC is organized: sector - channel (where sector and channel have a different meaning than in the real data!!!)*/
	std::map<TranslationTable::CALO_Index_t,CalorimeterDigiHit*> m_map;
	std::map<TranslationTable::CALO_Index_t,CalorimeterDigiHit*>::iterator m_map_it;

	int m_isMC;
};

#endif // _CalorimeterDigiHit_factory_MC_

