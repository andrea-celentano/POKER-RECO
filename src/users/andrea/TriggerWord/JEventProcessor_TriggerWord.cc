// $Id$
//
//    File: JEventProcessor_TriggerWord.cc
// Created: Fri Feb  2 11:31:41 CET 2018
// Creator: celentan (on Linux apcx4 2.6.32-696.13.2.el6.x86_64 x86_64)
//

#include "JEventProcessor_TriggerWord.h"
#include <DAQ/fa250Mode1Hit.h>
#include <DAQ/fa250Mode1CalibPedSubHit.h>
#include <DAQ/eventData.h>
#include "TApplication.h"
using namespace jana;

TApplication gui("GUI",0,NULL);


// Routine used to create our JEventProcessor
#include <JANA/JApplication.h>
#include <JANA/JFactory.h>
extern "C" {
void InitPlugin(JApplication *app) {
	InitJANAPlugin(app);
	app->AddProcessor(new JEventProcessor_TriggerWord());
}
} // "C"

//------------------
// JEventProcessor_TriggerWord (Constructor)
//------------------
JEventProcessor_TriggerWord::JEventProcessor_TriggerWord() {

}

//------------------
// ~JEventProcessor_TriggerWord (Destructor)
//------------------
JEventProcessor_TriggerWord::~JEventProcessor_TriggerWord() {

}

//------------------
// init
//------------------
jerror_t JEventProcessor_TriggerWord::init(void) {
	// This is called once at program startup. If you are creating
	// and filling historgrams in this plugin, you should lock the
	// ROOT mutex like this:
	//
	// japp->RootWriteLock();
	//  ... fill historgrams or trees ...
	// japp->RootUnLock();
	//

	c=new TCanvas("c","c");
	return NOERROR;
}

//------------------
// brun
//------------------
jerror_t JEventProcessor_TriggerWord::brun(JEventLoop *eventLoop, uint32_t runnumber) {
	// This is called whenever the run number changes
	return NOERROR;
}

//------------------
// evnt
//------------------
jerror_t JEventProcessor_TriggerWord::evnt(JEventLoop *loop, uint64_t eventnumber) {
	// This is called for every event. Use of common resources like writing
	// to a file or filling a histogram should be mutex protected. Using
	// loop->Get(...) to get reconstructed objects (and thereby activating the
	// reconstruction algorithm) should be done outside of any mutex lock
	// since multiple threads may call this method at the same time.
	// Here's an example:
	//
	// vector<const MyDataClass*> mydataclasses;
	// loop->Get(mydataclasses);
	//
	// japp->RootWriteLock();
	//  ... fill historgrams or trees ...
	// japp->RootUnLock();

	vector<const fa250Mode1CalibPedSubHit*> data;
	vector<const fa250Mode1CalibPedSubHit*>::const_iterator data_it;
	const eventData *m_eventData;
	vector<TH1D *> waves;
	int nTriggerSingles[nTriggersMAX]={0};
	vector<int> trgTimes[nTriggersMAX];

	double max=-9999;

	bool triggers[32] = { false };
	int nTriggers = 0;
	int word1, word2;

	loop->Get(data);
	try {
		loop->GetSingle(m_eventData);
	} catch (unsigned long e) {
		jout << "no eventData this event: " << eventnumber << endl;
		return NOERROR;
	}

	for (int ii=0;ii<data.size();ii++){
		waves.push_back(new TH1D(Form("h%i",ii),Form("h%i",ii),data[ii]->samples.size(),-0.5,data[ii]->samples.size()-0.5));
		data[ii]->toHisto(waves[ii]);
		if (waves[ii]->GetMaximum()>max) max=waves[ii]->GetMaximum();
	}

	for (int ii = 0; ii < m_eventData->triggerWords.size() / 2; ii++) {
		word1 = m_eventData->triggerWords[ii * 2];
		word2 = m_eventData->triggerWords[ii * 2 + 1];
		for (int jj = 0; jj < nTriggersMAX; jj++) {
			if ((word1 >> jj) & 0x1) {
				triggers[jj] = true;
				nTriggers++;
				nTriggerSingles[jj]++;
				trgTimes[jj].push_back(word2);
			}
		}
	}

	jout <<"EVT "<< m_eventData->eventN << " : " << m_eventData->triggerWords.size() / 2 << std::endl;
	jout << "TRGS: " << nTriggers << std::endl;
	for (int jj = 0; jj < nTriggersMAX; jj++) {
		jout << jj << " : " << (triggers[jj] == true ? "1" : "0") << " --> ";
		for (int kk=0;kk<nTriggerSingles[jj];kk++){
			jout<<trgTimes[jj][kk]<<" ";
		}
		jout<<std::endl;
	}

	//bit0
	waves[11]->GetYaxis()->SetRangeUser(-100,1.1*max);
	waves[11]->Draw();
	waves[12]->Draw("SAME");
	//bit1
	waves[0]->SetLineColor(2);
	waves[1]->SetLineColor(2);
	waves[0]->Draw("SAME");
	waves[1]->Draw("SAME");
	//bit2
	waves[14]->SetLineColor(3);
	waves[14]->Draw("SAME");
	//bit3
	waves[2]->SetLineColor(4);
	waves[5]->SetLineColor(4);
	waves[6]->SetLineColor(4);
	waves[2]->Draw("SAME");
	waves[5]->Draw("SAME");
	waves[6]->Draw("SAME");

	c->Draw();
	c->Modified();
	c->Update();
	c->Draw();
	cin.get();
	return NOERROR;
}

//------------------
// erun
//------------------
jerror_t JEventProcessor_TriggerWord::erun(void) {
	// This is called whenever the run number changes, before it is
	// changed to give you a chance to clean up before processing
	// events from the next run number.
	return NOERROR;
}

//------------------
// fini
//------------------
jerror_t JEventProcessor_TriggerWord::fini(void) {
	// Called before program exit after event processing is finished.
	return NOERROR;
}

