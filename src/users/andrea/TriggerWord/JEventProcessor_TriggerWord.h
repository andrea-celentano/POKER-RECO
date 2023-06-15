// $Id$
//
//    File: JEventProcessor_TriggerWord.h
// Created: Fri Feb  2 11:31:41 CET 2018
// Creator: celentan (on Linux apcx4 2.6.32-696.13.2.el6.x86_64 x86_64)
//

#ifndef _JEventProcessor_TriggerWord_
#define _JEventProcessor_TriggerWord_

#include <JANA/JEventProcessor.h>
#include "TCanvas.h"
#include "TH1D.h"
#include "TH1D.h"
#include "TCanvas.h"

class JEventProcessor_TriggerWord:public jana::JEventProcessor{
	public:
		JEventProcessor_TriggerWord();
		~JEventProcessor_TriggerWord();
		const char* className(void){return "JEventProcessor_TriggerWord";}

	private:
		jerror_t init(void);						///< Called once at program start.
		jerror_t brun(jana::JEventLoop *eventLoop, uint32_t runnumber);	///< Called everytime a new run number is detected.
		jerror_t evnt(jana::JEventLoop *eventLoop, uint64_t eventnumber);	///< Called every event.
		jerror_t erun(void);						///< Called everytime run number changes, provided brun has been called.
		jerror_t fini(void);						///< Called after last event of last event source has been processed.


		static const int nTriggersMAX=4;
		TCanvas *c;
};

#endif // _JEventProcessor_TriggerWord_

