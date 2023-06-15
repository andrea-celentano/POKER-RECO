// $Id$
//
//    File: JEventProcessor_txtWriter.h
// Created: Thu Oct 20 10:07:53 UTC 2022
// Creator: clasrun (on Linux jdaq6 3.10.0-1160.31.1.el7.x86_64 x86_64)
//

#ifndef _JEventProcessor_txtWriter_
#define _JEventProcessor_txtWriter_

#include <JANA/JEventProcessor.h>
class JTxtOutput;

class JEventProcessor_txtWriter:public jana::JEventProcessor{
	public:
		JEventProcessor_txtWriter();
		~JEventProcessor_txtWriter();
		const char* className(void){return "JEventProcessor_txtWriter";}

	private:
		jerror_t init(void);						///< Called once at program start.
		jerror_t brun(jana::JEventLoop *eventLoop, int32_t runnumber);	///< Called everytime a new run number is detected.
		jerror_t evnt(jana::JEventLoop *eventLoop, uint64_t eventnumber);	///< Called every event.
		jerror_t erun(void);						///< Called everytime run number changes, provided brun has been called.
		jerror_t fini(void);						///< Called after last event of last event source has been processed.

		JTxtOutput *m_TxtOutput;
	    int m_isFirstCallToBrun;
};

#endif // _JEventProcessor_txtWriter_

