// $Id$
//
//    File: fa250Mode1CalibPedSubHitFFT.h
// Created: Mon May 27 15:32:26 CEST 2019
// Creator: celentan (on Linux apcx4 3.10.0-957.el7.x86_64 x86_64)
//

#ifndef _fa250Mode1CalibPedSubHitFFT_
#define _fa250Mode1CalibPedSubHitFFT_

#include <JANA/JObject.h>
#include <JANA/JFactory.h>

#include "fa250Mode1Hit.h"

class fa250Mode1CalibPedSubHitFFT: public fa250Mode1Hit {
public:
	JOBJECT_PUBLIC(fa250Mode1CalibPedSubHitFFT)
	;
	fa250Mode1CalibPedSubHitFFT();
	virtual ~fa250Mode1CalibPedSubHitFFT();

	// Add data members here. For example:
	// int id;
	// double E;

	// This method is used primarily for pretty printing
	// the second argument to AddString is printf style format
	void toStrings(vector<pair<string, string> > &items) const {
		AddString(items, "crate", "%4d", m_channel.rocid);
		AddString(items, "slot", "%4d", m_channel.slot);
		AddString(items, "channel", "%4d", m_channel.channel);
		AddString(items, "nsamples", "%4d", samples.size());
	}

	virtual TCanvas* Draw(int id = 0) const;
	void toHisto(TH1D *h) const;
};

#endif // _fa250Mode1CalibPedSubHitFFT_

