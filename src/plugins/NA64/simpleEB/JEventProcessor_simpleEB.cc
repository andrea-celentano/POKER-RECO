// $Id$
//
//    File: JEventProcessor_simpleEB.cc
// Created: Thu Apr 28 15:13:02 UTC 2022
// Creator: clasrun (on Linux jdaq6 3.10.0-1160.31.1.el7.x86_64 x86_64)
//

#include "JEventProcessor_simpleEB.h"

#include <system/JROOTOutput.h>
#include <system/BDXEventProcessor.h>

#include "Calorimeter/CalorimeterHit.h"
#include "Cerenkov/CerenkovHit.h"
#include "DAQ/fa250WaveboardV1Hit.h"
#include "DAQ/fa250Mode1CalibPedSubHit.h"
#include <DAQ/eventData.h>

#include "TTree.h"

using namespace jana;

// Routine used to create our JEventProcessor
#include <JANA/JApplication.h>
extern "C" {
void InitPlugin(JApplication *app) {
	InitJANAPlugin(app);
	app->AddProcessor(new JEventProcessor_simpleEB());
}
} // "C"

//------------------
// JEventProcessor_simpleEB (Constructor)
//------------------
JEventProcessor_simpleEB::JEventProcessor_simpleEB() {
	m_tout = 0;
}

//------------------
// ~JEventProcessor_simpleEB (Destructor)
//------------------
JEventProcessor_simpleEB::~JEventProcessor_simpleEB() {

}

//------------------
// init
//------------------
jerror_t JEventProcessor_simpleEB::init(void) {

	m_isFirstCallToBrun = 1;
	m_isMC = 0;
	gPARMS->GetParameter("MC", m_isMC);

	japp->RootWriteLock();

	if (m_tout != NULL) {
		japp->RootUnLock();
		return NOERROR;
	}
	vector<double> d;
	for (int ii = 0; ii < 9; ii++) {
		m_samples.push_back(d);
	}

	m_tout = new TTree("tout_NA64", "NA64 simple EB");
	//m_tout->Branch("samples", &m_samples);
	m_tout->Branch("A", &m_A, "A[3][3]/D");
  m_tout->Branch("Araw", &m_Araw, "Araw[3][3]/D");
	m_tout->Branch("Q", &m_Q, "Q[3][3]/D");
	m_tout->Branch("E", &m_E, "E[3][3]/D");
	m_tout->Branch("T", &m_T, "T[3][3]/D");
	m_tout->Branch("Etot", &m_Etot);

	m_tout->Branch("eventN", &m_evnN);
	m_tout->Branch("spillN", &m_spillN);
	m_tout->Branch("runN", &m_runN);
	m_tout->Branch("eventT", &m_evnTime, "eventT/l");

	m_tout->Branch("A1", &A1);
	m_tout->Branch("A2", &A2);
	m_tout->Branch("Abig", &Abig);

	m_tout->Branch("cerenkov", &cerenkov);

	japp->RootUnLock();

	// This is called once at program startup
	return NOERROR;
}

//------------------
// brun
//------------------
jerror_t JEventProcessor_simpleEB::brun(JEventLoop *eventLoop,
		int32_t runnumber) {
	// This is called whenever the run number changes
	jout << m_isFirstCallToBrun << endl;

	if (m_isFirstCallToBrun) {

		jout << "JEventProcessor_BDXMiniClusters::brun searching m_RootOutput"
				<< endl;
		string class_name, this_class_name;
		string joutput_name;
		BDXEventProcessor *m_BDXEventProcessor;
		vector<JEventProcessor*> m_processors = app->GetProcessors();
		vector<JEventProcessor*>::iterator m_processors_it;

		m_isFirstCallToBrun = 0;
		class_name = "BDXEventProcessor";
		joutput_name = "JROOTOutput";
		//Now I need to determine which processor is the one holding the output. Discussing with David, he suggested just to check the class name, since
		//a dynamic cast may not work with plugins
		for (m_processors_it = m_processors.begin();
				m_processors_it != m_processors.end(); m_processors_it++) {
			if ((*m_processors_it) != 0) {
				this_class_name = string((*m_processors_it)->className());
				if (this_class_name == class_name) {
					m_BDXEventProcessor =
							(BDXEventProcessor*) (*m_processors_it);
					if (m_BDXEventProcessor->getOutput() == 0) {
						jerr << "BDXEventProcessor JOutput is null!" << endl;
						break;
					}
					if (string(m_BDXEventProcessor->getOutput()->className())
							== joutput_name) {
						m_ROOTOutput =
								(JROOTOutput*) (m_BDXEventProcessor->getOutput());
						jout << "Got JROOTOutput!" << endl;
					} else {
						jerr
								<< "BDXEventProcessor JOutput is not null BUT class is: "
								<< m_BDXEventProcessor->getOutput()->className()
								<< endl;
					}
				}
			}
		}
	}

	return NOERROR;
}

//------------------
// evnt
//------------------
jerror_t JEventProcessor_simpleEB::evnt(JEventLoop *loop,
		uint64_t eventnumber) {
	// This is called for every event. Use of common resources like writing
	// to a file or filling a histogram should be mutex protected. Using
	// loop->Get(...) to get reconstructed objects (and thereby activating the
	// reconstruction algorithm) should be done outside of any mutex lock
	// since multiple threads may call this method at the same time.

	vector<const fa250Mode1CalibPedSubHit*> m_waveforms;
	vector<const fa250Mode1CalibPedSubHit*>::const_iterator m_waveforms_it;

	vector<const CalorimeterHit*> m_hits;
	vector<const CalorimeterHit*>::const_iterator m_hits_it;
	const CalorimeterHit *m_hit;

	vector<const CerenkovHit*> m_chits;
	vector<const CerenkovHit*>::const_iterator m_chits_it;
	const CerenkovHit *m_chit;

	// loop->Get(m_waveforms);
	loop->Get(m_hits);
	loop->Get(m_chits);

	const eventData *tData;

	try {
		loop->GetSingle(tData);
	} catch (unsigned long e) {
		jout << "JEventProcessor_Trigger::evnt no eventData bank this event"
				<< std::endl;
		return OBJECT_NOT_AVAILABLE;
	}
	/*If this is an EPICS event, do nothing.*/
	if (tData->eventType == eventSource::EPICS) {
		return NOERROR;
	}

	// Lock ROOT
	japp->RootWriteLock();
	for (int ix = 0; ix < 3; ix++) {
		for (int iy = 0; iy < 3; iy++) {
			m_Q[ix][iy] = -1;
			m_A[ix][iy] = -1;
		  m_Araw[ix][iy] = -1;
			m_E[ix][iy] = -1;
			m_T[ix][iy] = -1;
		}
	}
	A1=-100;
	A2=-100;
	m_Etot=0;
	cerenkov = 0;

	m_evnN = tData->eventN;
	m_runN = tData->runN;
	m_evnTime = tData->time;
	m_spillN = (int)(tData->spillN);

	for (m_chits_it = m_chits.begin(); m_chits_it != m_chits.end(); m_chits_it++) {
		m_chit = *m_chits_it;
		int index = m_chit->m_channel.index;
		cerenkov = cerenkov | (1<<index);
	}

	for (m_hits_it = m_hits.begin(); m_hits_it != m_hits.end(); m_hits_it++) {

		m_hit = *m_hits_it;

		int sector = m_hit->m_channel.sector;
		int X = m_hit->m_channel.x;
		int Y = m_hit->m_channel.y;

		if (sector == 0) {
			if ((X < 0) || (X > 2) || (Y < 0) || (Y > 2))
				continue;

			m_E[X][Y] = m_hit->E;
			m_Q[X][Y] = m_hit->Eraw;
			m_A[X][Y] = m_hit->A;
	    m_Araw[X][Y] = m_hit->Araw;
			m_T[X][Y] = m_hit->T;

			if (m_hit->E>.1)
				m_Etot+=m_hit->E;

		}
		if (sector == 1) {
			if (X == 0)
				A1 = m_hit->A;
			if (X == 1)
				A2 = m_hit->A;
			if (X == 2)
				Abig = m_hit->A;
		}
	}

	m_tout->Fill();
	japp->RootUnLock();
	return NOERROR;
}

//------------------
// erun
//------------------
jerror_t JEventProcessor_simpleEB::erun(void) {
	// This is called whenever the run number changes, before it is
	// changed to give you a chance to clean up before processing
	// events from the next run number.

	if (m_ROOTOutput != 0) {
		jout
				<< "JEventProcessor_BDXMiniCalorimeterEnergyCalibartion adding histos to m_ROOTOutput"
				<< endl;

		m_ROOTOutput->AddObject(m_tout);

	}

	return NOERROR;
}

//------------------
// fini
//------------------
jerror_t JEventProcessor_simpleEB::fini(void) {
	// Called before program exit after event processing is finished.
	return NOERROR;
}

