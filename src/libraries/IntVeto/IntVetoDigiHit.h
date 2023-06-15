// $Id$
//
//    File: IntVetoDigiHit.h
// Created: Wed Jan 20 16:42:38 CET 2016
// Creator: celentan (on Linux apcx4 2.6.32-504.30.3.el6.x86_64 x86_64)
//

#ifndef _IntVetoDigiHit_
#define _IntVetoDigiHit_

#include <JANA/JObject.h>
#include <JANA/JFactory.h>
#include <system/BDXObject.h>
#include <TT/TranslationTable.h>
#include "TObject.h"
/*
 * A.C.
 * This object represents a not-yet calibrated it in the inner veto.
 * The goal of this object is dual:
 * - Do the matching of the different IntVetoSiPMhit hits corresponding to the SAME active volume (sector / layer / component)
 * - Be as similar as possible to what is obtained from GEMC, while we wait GEMC producing composite, fadc-like, banks.
 */

class TCanvas;
class TH1D;

class IntVetoDigiHit:public BDXObject{
public:

	JOBJECT_PUBLIC(IntVetoDigiHit);

	// Add data members here. For example:
	// int id;
	// double E;

	// This method is used primarily for pretty printing
	// the second argument to AddString is printf style format
	void toStrings(vector<pair<string,string> > &items)const{
		AddString(items, "sector", "%4d", m_channel.sector);
		AddString(items, "layer", "%4d", m_channel.layer);
		AddString(items, "component", "%4d", m_channel.component);
		AddString(items, "readout", "%4d", m_channel.readout);
		AddString(items, "Qphe","%4f",Qphe);
		AddString(items, "Qraw","%4f",Qraw);
		AddString(items, "T","%4f",T);
		AddString(items, "Araw","%4f",Araw);
		AddString(items, "Aphe","%4f",Aphe);
		AddString(items, "pedMean","%4f",pedMean);
		AddString(items, "pedRMS","%4f",pedRMS);
		AddString(items, "RMSflag","%4d",1*RMSflag);

	}
	//A.C. do not touch these
	TranslationTable::INT_VETO_Index_t m_channel;      //Detector-specific ID. Since this is a detector-based object, the readout field will be ==0

	virtual TCanvas* Draw(int id=0) const;//!  //Exclude from root dictionary
	mutable TH1D* hWave; //!  //Exclude from root dictionary

	double Qphe,Qraw,T,Araw,Aphe;
	double pedMean,pedRMS;
	bool RMSflag;


	ClassDef(IntVetoDigiHit,1);

};
#endif // _IntVetoDigiHit_

