// $Id$
//
//    File: JEventProcessor_DAQWaveformsMode1.h
// Created: Mon Nov 13 10:53:49 CET 2017
// Creator: celentan (on Linux apcx4 2.6.32-696.13.2.el6.x86_64 x86_64)
//

#ifndef _JEventProcessor_DAQWaveformsMode1_
#define _JEventProcessor_DAQWaveformsMode1_

#include <JANA/JEventProcessor.h>

class JEventProcessor_DAQWaveformsMode1:public jana::JEventProcessor{
	public:
		JEventProcessor_DAQWaveformsMode1();
		~JEventProcessor_DAQWaveformsMode1();
		const char* className(void){return "JEventProcessor_DAQWaveformsMode1";}

	private:
		jerror_t init(void);						///< Called once at program start.
		jerror_t brun(jana::JEventLoop *eventLoop, int32_t runnumber);	///< Called everytime a new run number is detected.
		jerror_t evnt(jana::JEventLoop *eventLoop, uint64_t eventnumber);	///< Called every event.
		jerror_t erun(void);						///< Called everytime run number changes, provided brun has been called.
		jerror_t fini(void);						///< Called after last event of last event source has been processed.
};

#endif // _JEventProcessor_DAQWaveformsMode1_

