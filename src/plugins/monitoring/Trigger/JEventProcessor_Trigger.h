// $Id$
//
//    File: JEventProcessor_Trigger.h
// Created: Thu Feb  8 18:39:24 CET 2018
// Creator: celentan (on Linux apcx4 2.6.32-696.13.2.el6.x86_64 x86_64)
//

#ifndef _JEventProcessor_Trigger_
#define _JEventProcessor_Trigger_

#include <JANA/JEventProcessor.h>

class TH1D;
class TH2D;


class JEventProcessor_Trigger:public jana::JEventProcessor{
	public:
		JEventProcessor_Trigger();
		~JEventProcessor_Trigger();
		const char* className(void){return "JEventProcessor_Trigger";}

	private:
		jerror_t init(void);						///< Called once at program start.
		jerror_t brun(jana::JEventLoop *eventLoop, uint32_t runnumber);	///< Called everytime a new run number is detected.
		jerror_t evnt(jana::JEventLoop *eventLoop, uint64_t eventnumber);	///< Called every event.
		jerror_t erun(void);						///< Called everytime run number changes, provided brun has been called.
		jerror_t fini(void);						///< Called after last event of last event source has been processed.

		static const int nTriggersMAX=32;
		static const int nChansMax=64;
		static const int MAGIC_TRG_WORD = 0xabcdabcd;
		static const int MAGIC_TRG_WORD2 = 0xfafafbfb;

		int chanTimeMin,chanTimeMax;

};

#endif // _JEventProcessor_Trigger_

