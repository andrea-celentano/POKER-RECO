// $Id$
//
//    File: CalorimeterCluster.h
// Created: Tue Mar 22 11:19:57 CET 2016
// Creator: celentan (on Linux apcx4 2.6.32-504.30.3.el6.x86_64 x86_64)
//

#ifndef _CalorimeterCluster_
#define _CalorimeterCluster_

#include <JANA/JObject.h>
#include <JANA/JFactory.h>

#include <system/BDXObject.h>
#include "TObject.h"

class TH1D;
class TCanvas;

class CalorimeterCluster: public BDXObject {
private:
	mutable vector<TH1D*> hWaves; //!

public:
	JOBJECT_PUBLIC(CalorimeterCluster)
	;

	// Add data members here. For example:
	// int id;
	// double E;

	// This method is used primarily for pretty printing
	// the second argument to AddString is printf style format
	void toStrings(vector<pair<string, string> > &items) const {
		// AddString(items, "id", "%4d", id);

		AddString(items, "sector", "%i", m_sector);
		AddString(items, "x", "%f", x);
		AddString(items, "y", "%f", y);

		AddString(items, "E", "%f", E);
		AddString(items, "Eseed", "%f", Eseed);
		AddString(items, "T", "%f", T);
		AddString(items,"Nhits","%i",Nhits);
		AddString(items,"NhitsNearSeed","%i",Nhits_near_seed);

	}

	double Eseed;
	double E, T;
	double x, y;
	int Nhits, Nhits_near_seed, m_sector;

	virtual TCanvas* Draw(int id) const; //!
	ClassDef(CalorimeterCluster,1);

};

#endif // _CalorimeterCluster_

