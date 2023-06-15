// $Id$
//
//    File: triggerData_factory.h
// Created: Fri May  3 11:44:17 CEST 2019
// Creator: celentan (on Linux apcx4 2.6.32-696.13.2.el6.x86_64 x86_64)
//

#ifndef _triggerData_factory_
#define _triggerData_factory_

#include <JANA/JFactory.h>
#include "triggerDataBDXmini.h"

class triggerDataBDXmini_factory:public jana::JFactory<triggerDataBDXmini>{
	public:
		triggerDataBDXmini_factory(){};
		~triggerDataBDXmini_factory(){};


	private:
		jerror_t init(void);						///< Called once at program start.
		jerror_t brun(jana::JEventLoop *eventLoop, int32_t runnumber);	///< Called everytime a new run number is detected.
		jerror_t evnt(jana::JEventLoop *eventLoop, uint64_t eventnumber);	///< Called every event.
		jerror_t erun(void);						///< Called everytime run number changes, provided brun has been called.
		jerror_t fini(void);						///< Called after last event of last event source has been processed.

		int m_isMC;
		int m_chanTimeMin; //25 ns units;
		int m_chanTimeMax; //25 ns units;

		static const int nTriggersMAX=32;
		static const int nChansMAX=64;
		static const unsigned int MAGIC_TRG_WORD = 0xabcdabcd;
};

#endif // _triggerData_factory_

