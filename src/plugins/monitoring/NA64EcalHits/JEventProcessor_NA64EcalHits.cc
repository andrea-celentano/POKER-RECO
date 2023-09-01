// $Id$
//
//    File: JEventProcessor_NA64EcalHits.cc
// Created: Thu Oct  3 17:27:30 CEST 2019
// Creator: celentan (on Linux apcx4 3.10.0-957.el7.x86_64 x86_64)
//

#include "../NA64EcalHits/JEventProcessor_NA64EcalHits.h"
using namespace jana;

// Routine used to create our JEventProcessor
#include <JANA/JApplication.h>
#include <JANA/JFactory.h>

#include "Calorimeter/CalorimeterHit.h"
#include "DAQ/eventData.h"

#include <system/JROOTOutput.h>
#include <system/BDXEventProcessor.h>

#include "TROOT.h"
// Routine used to create our JEventProcessor
#include <JANA/JApplication.h>
#include <JANA/JFactory.h>

#include "TH2D.h"
/*Here goes the histograms*/
static const int nECAL = 9;

//Energy
static TH1D *hNA64EcalHitsEnergy[nECAL] = { 0 };
static TH2D *hNA64EcalHitsEnergy2D = 0;
static TH2D *hNA64EcalHitsEnergy2D_n = 0;

static TH2D *hNA64EcalHitsEnergyFrac = 0;
static TH2D *hNA64EcalHitsEnergyFrac_n = 0;

static TH1D *hNA64EcalHits_TopMinusBottom = 0;
static TH1D *hNA64EcalHits_JuraMinusSaleve = 0;

static TH1D *hNA64EcalHitsEnergyTot = 0;
double EsumThr;

extern "C" {
void InitPlugin(JApplication *app) {
	InitJANAPlugin(app);
	app->AddProcessor(new JEventProcessor_NA64EcalHits());
}
} // "C"

//------------------
// JEventProcessor_NA64EcalHits (Constructor)
//------------------
JEventProcessor_NA64EcalHits::JEventProcessor_NA64EcalHits() :
		m_ROOTOutput(0), m_isMC(0) {
	m_isFirstCallToBrun = 1;

}

//------------------
// ~JEventProcessor_NA64EcalHits (Destructor)
//------------------
JEventProcessor_NA64EcalHits::~JEventProcessor_NA64EcalHits() {

}

//------------------
// init
//------------------
jerror_t JEventProcessor_NA64EcalHits::init(void) {
	// This is called once at program startup. If you are creating
	// and filling historgrams in this plugin, you should lock the
	// ROOT mutex like this:
	//
	// japp->RootWriteLock();
	//  ... fill historgrams or trees ...
	// japp->RootUnLock();
	//
	m_isFirstCallToBrun = 1;
	m_isMC = 0;
	gPARMS->GetParameter("MC", m_isMC);

	/*Hard-coded XY -> id geometry*/
	geometry[make_pair(0, 0)] = 1;
	geometry[make_pair(0, 1)] = 4;
	geometry[make_pair(0, 2)] = 6;
	geometry[make_pair(1, 0)] = 2;
	geometry[make_pair(1, 1)] = 0;
	geometry[make_pair(1, 2)] = 7;
	geometry[make_pair(2, 0)] = 3;
	geometry[make_pair(2, 1)] = 5;
	geometry[make_pair(2, 2)] = 8;

	japp->RootWriteLock();

	if (hNA64EcalHitsEnergy[0] != NULL) {
		japp->RootUnLock();
		return NOERROR;
	}

	gROOT->cd();
	TDirectory *main = gDirectory;
	gDirectory->mkdir("NA64EcalHits")->cd();

	/*Create all the histograms*/
	map<pair<int, int>, int>::iterator geometry_it;
	int iX, iY, id;

	double Emin, Emax;
	int NE;

	NE = 500;
	Emin = 100;
	Emax = 600; //600

	gPARMS->SetDefaultParameter("NA64EcalHits:Emin", Emin, "Emin for histo");
	gPARMS->SetDefaultParameter("NA64EcalHits:Emax", Emax, "Emax for histo");
	gPARMS->SetDefaultParameter("NA64EcalHits:NE", NE, "NE for histo");

	gPARMS->SetDefaultParameter("NA64EcalHits:EsumThr", EsumThr, "Min ene in GeV to enter the sum");

	for (geometry_it = geometry.begin(); geometry_it != geometry.end();
			geometry_it++) {
		//Do whatever you want. To access the first part of pair(pair is the key of the map here) you should write

		iX = (geometry_it->first).first;
		iY = (geometry_it->first).second;
		id = (geometry_it->second);

		hNA64EcalHitsEnergy[id] = new TH1D(Form("hE_x%i_y%i", iX, iY),
				Form("hE_x%i_y%i", iX, iY), NE, Emin, Emax);
		hNA64EcalHitsEnergy[id]->GetXaxis()->SetTitle("E");

	}

	hNA64EcalHitsEnergy2D = new TH2D("hE_2D", "hE_2D", 3, -0.5, 2.5, 3, -0.5,
			2.5);
	hNA64EcalHitsEnergy2D_n = new TH2D("hE_2Dn", "hE_2Dn", 3, -0.5, 2.5, 3, -0.5,
			2.5);

	hNA64EcalHitsEnergyFrac = new TH2D("hE_Frac", "hE_Frac", 3, -0.5, 2.5, 3, -0.5,
			2.5);

	hNA64EcalHitsEnergyFrac_n = new TH2D("hE_Fracn", "hE_Fracn", 3, -0.5, 2.5, 3, -0.5,
				2.5);


	hNA64EcalHits_TopMinusBottom = new TH1D("hNA64EcalHits_TopMinusBottom",
			"hNA64EcalHits_TopMinusBottom", 2 * NE, -1, 1);
	hNA64EcalHits_JuraMinusSaleve = new TH1D("hNA64EcalHits_JuraMinusSaleve",
			"hNA64EcalHits_JuraMinusSaleve", 2 * NE, -1, 1);

	hNA64EcalHitsEnergyTot = new TH1D("hNA64EcalHitsEnergyTot","hNA64EcalHitsEnergyTot", NE, Emin, Emax);

	// back to main dir
	main->cd();
	japp->RootUnLock();

	return NOERROR;

}

//------------------
// brun
//------------------
jerror_t JEventProcessor_NA64EcalHits::brun(JEventLoop *eventLoop,
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
jerror_t JEventProcessor_NA64EcalHits::evnt(JEventLoop *loop,
		uint64_t eventnumber) {
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

	vector<const CalorimeterHit*> hits;
	vector<const CalorimeterHit*>::iterator hits_it;
	const CalorimeterHit *m_hit;
	const eventData *tData;
	if (!m_isMC) {
		try {
			loop->GetSingle(tData);
		} catch (unsigned long e) {
			jout
					<< "JEventProcessor_NA64EcalHits::evnt no eventData bank this event"
					<< std::endl;
			return OBJECT_NOT_AVAILABLE;
		}
	}

	loop->Get(hits);
	int sector, X, Y, id;

	//Jura and Saleve
	double E_2_1 = -1000;
	double E_0_1 = -1000;

	//Top and Bottom
	double E_1_2 = -1000;
	double E_1_0 = -1000;

	double Esum=0;
	for (hits_it = hits.begin(); hits_it != hits.end(); hits_it++) {
		m_hit = *hits_it;

		sector = m_hit->m_channel.sector;
		X = m_hit->m_channel.x;
		Y = m_hit->m_channel.y;

		if ((X < 0) || (X > 2) || (Y < 0) || (Y > 2) || (sector != 0))
			continue;
		id = geometry[make_pair(X, Y)];

		japp->RootWriteLock();
		hNA64EcalHitsEnergy[id]->Fill(m_hit->E); //E

		hNA64EcalHitsEnergy2D->Fill(2 - X, Y, m_hit->E); //2-X is to have X axis reflected
		hNA64EcalHitsEnergy2D_n->Fill(2 - X, Y);

		//Fill total
		if (m_hit->E >EsumThr){
			Esum+=m_hit->E;
		}


		if ((X == 0) && (Y == 1)) {
			E_0_1 = m_hit->E;
		}

		if ((X == 2) && (Y == 1)) {
			E_2_1 = m_hit->E;
		}

		if ((X == 1) && (Y == 0)) {
			E_1_0 = m_hit->E;
		}

		if ((X == 1) && (Y == 2)) {
			E_1_2 = m_hit->E;
		}
		japp->RootUnLock();
	}

	for (hits_it = hits.begin(); hits_it != hits.end(); hits_it++) {
		m_hit = *hits_it;
		sector = m_hit->m_channel.sector;
		X = m_hit->m_channel.x;
		Y = m_hit->m_channel.y;

		if ((X < 0) || (X > 2) || (Y < 0) || (Y > 2) || (sector != 0))
			continue;
		if (Esum>0){
			hNA64EcalHitsEnergyFrac_n->Fill(2 - X, Y);
			hNA64EcalHitsEnergyFrac->Fill(2 - X, Y, m_hit->E/Esum); //2-X is to have X axis reflected
		}
	}

	japp->RootWriteLock();
	hNA64EcalHitsEnergyTot->Fill(Esum);
	//top minus bottom
	if ((E_1_0>-10)&&(E_1_2>-10)){
	  hNA64EcalHits_TopMinusBottom->Fill((E_1_2-E_1_0)/(E_1_2+E_1_0));
	}

	if ((E_2_1>-10)&&(E_0_1>-10)){
	  hNA64EcalHits_JuraMinusSaleve->Fill((E_2_1-E_0_1)/(E_2_1+E_0_1));
	}

	japp->RootUnLock();
	return NOERROR;
}

//------------------
// erun
//------------------
jerror_t JEventProcessor_NA64EcalHits::erun(void) {
	// This is called whenever the run number changes, before it is
	// changed to give you a chance to clean up before processing
	// events from the next run number.

	if (m_ROOTOutput != 0) {
		jout
				<< "JEventProcessor_BDXMiniCalorimeterEnergyCalibartion adding histos to m_ROOTOutput"
				<< endl;
		for (int ii = 0; ii < nECAL; ii++) {
			m_ROOTOutput->AddObject(hNA64EcalHitsEnergy[ii]);
		}
		m_ROOTOutput->AddObject(hNA64EcalHitsEnergy2D);
		m_ROOTOutput->AddObject(hNA64EcalHits_TopMinusBottom);
		m_ROOTOutput->AddObject(hNA64EcalHits_JuraMinusSaleve);
		m_ROOTOutput->AddObject(hNA64EcalHitsEnergyTot);
		m_ROOTOutput->AddObject(hNA64EcalHitsEnergyFrac);
		m_ROOTOutput->AddObject(hNA64EcalHitsEnergyFrac_n);
	}
	return NOERROR;
}

//------------------
// fini
//------------------
jerror_t JEventProcessor_NA64EcalHits::fini(void) {
	// Called before program exit after event processing is finished.
	return NOERROR;
}

