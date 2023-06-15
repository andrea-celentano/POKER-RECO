// $Id$
//
//    File: fa250Mode1CalibPedSubHitFFT_factory.h
// Created: Mon May 27 15:32:26 CEST 2019
// Creator: celentan (on Linux apcx4 3.10.0-957.el7.x86_64 x86_64)
//

#ifndef _fa250Mode1CalibPedSubHitFFT_factory_
#define _fa250Mode1CalibPedSubHitFFT_factory_

#include <JANA/JFactory.h>
#include "fa250Mode1CalibPedSubHitFFT.h"

class fa250Mode1CalibPedSubHitFFT_factory:public jana::JFactory<fa250Mode1CalibPedSubHitFFT>{
	public:
		fa250Mode1CalibPedSubHitFFT_factory(){};
		~fa250Mode1CalibPedSubHitFFT_factory(){};


	private:
		jerror_t init(void);						///< Called once at program start.
		jerror_t brun(jana::JEventLoop *eventLoop, int32_t runnumber);	///< Called everytime a new run number is detected.
		jerror_t evnt(jana::JEventLoop *eventLoop, uint64_t eventnumber);	///< Called every event.
		jerror_t erun(void);						///< Called everytime run number changes, provided brun has been called.
		jerror_t fini(void);						///< Called after last event of last event source has been processed.
};

#endif // _fa250Mode1CalibPedSubHitFFT_factory_

