// $Id$
//
//    File: Cerenkov_factory.h
// Created: Sat Jul 29 03:31:37 EDT 2023
// Creator: clasana (on Linux jdaq8 3.10.0-1160.88.1.el7.x86_64 x86_64)
//

#ifndef _Cerenkov_factory_
#define _Cerenkov_factory_

#include <JANA/JFactory.h>
#include "CerenkovHit.h"

class TranslationTable;
class CerenkovHit_factory:public jana::JFactory<CerenkovHit>{
	public:
		CerenkovHit_factory(){};
		~CerenkovHit_factory(){};


	private:
		jerror_t init(void);						///< Called once at program start.
		jerror_t brun(jana::JEventLoop *eventLoop, int32_t runnumber);	///< Called everytime a new run number is detected.
		jerror_t evnt(jana::JEventLoop *eventLoop, uint64_t eventnumber);	///< Called every event.
		jerror_t erun(void);						///< Called everytime run number changes, provided brun has been called.
		jerror_t fini(void);						///< Called after last event of last event source has been processed.
		const TranslationTable *m_tt;
		double m_thr_analog;    //thr in mV on waveform for analogue signal
		double m_thr_digital;   //thr in mV on waveform for digital signal
		double m_pedestal;      //n samples ped sub
		double m_scale;

};

#endif // _Cerenkov_factory_

