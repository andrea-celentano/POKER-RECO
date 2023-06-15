// $Id$
//
//    File: genParticle.h
// Created: Tue Mar  1 00:59:14 CET 2016
// Creator: celentan (on Linux localhost.localdomain 2.6.32-573.12.1.el6.x86_64 x86_64)
//

#ifndef _JIntVetoMCHit_
#define _JIntVetoMCHit_

#include <JANA/JObject.h>
#include <JANA/JFactory.h>
#include <MC/VetoMCHit.h>

/*This class is basically a place-holder for the data coming from EVIO file,
 * for the raw and digitized banks
 */
class IntVetoMCHit: public VetoMCHit {
public:
	JOBJECT_PUBLIC(IntVetoMCHit)
	;

	//dgtz banks
	int adc1, adc2, adc3, adc4,adc5,adc6,adc7,adc8;
	int tdc1, tdc2, tdc3, tdc4,tdc5,tdc6,tdc7,tdc8;

	//raw banks
	double totEdep;
	int sector,channel,system;
	// This method is used primarily for pretty printing
	// the second argument to AddString is printf style format
	void toStrings(vector<pair<string, string> > &items) const {
		AddString(items,"sector","%i",sector);
		AddString(items,"system","%i",system);
		AddString(items,"channel","%i",channel);
		AddString(items, "totEdep", "%f", totEdep);
		AddString(items, "adc1", "%d", adc1);
		AddString(items, "adc2", "%d", adc2);
		AddString(items, "adc3", "%d", adc3);
		AddString(items, "adc4", "%d", adc4);
		AddString(items, "adc5", "%d", adc5);
		AddString(items, "adc6", "%d", adc6);
		AddString(items, "adc7", "%d", adc7);
		AddString(items, "adc8", "%d", adc8);
		AddString(items, "tdc1", "%d", tdc1);
		AddString(items, "tdc2", "%d", tdc2);
		AddString(items, "tdc3", "%d", tdc3);
		AddString(items, "tdc4", "%d", tdc4);
		AddString(items, "tdc5", "%d", tdc5);
		AddString(items, "tdc6", "%d", tdc6);
		AddString(items, "tdc7", "%d", tdc7);
		AddString(items, "tdc8", "%d", tdc8);

	}
};

#endif

