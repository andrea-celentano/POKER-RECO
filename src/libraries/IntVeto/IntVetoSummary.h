// $Id$
//
//    File: IntVetoSummary.h
// Created: Tue Mar 29 15:07:39 CEST 2016
// Creator: celentan (on Linux apcx4 2.6.32-504.30.3.el6.x86_64 x86_64)
//

#ifndef _IntVetoSummary_
#define _IntVetoSummary_

#include <JANA/JObject.h>
#include <JANA/JFactory.h>
#include <TT/TranslationTable.h>

#include <system/BDXObject.h>

class TCanvas;
class TH1D;

class IntVetoSummary:public BDXObject{
	public:
		JOBJECT_PUBLIC(IntVetoSummary);
		
		// Add data members here. For example:
		// int id;
		// double E;
		
		// This method is used primarily for pretty printing
		// the second argument to AddString is printf style format
		void toStrings(vector<pair<string,string> > &items)const{
			 AddString(items, "sector", "%4d",sector);
			 AddString(items, "Nhits\n","%4d",hits.size());
			 for (int ii=0;ii<hits.size();ii++){
				 AddString(items, "component hit layer", "%4d", hits[ii].layer);
				 AddString(items, "component hit component\n", "%4d", hits[ii].component);
			 }
		}
		int sector;
		
		int nHits;
		vector<TranslationTable::INT_VETO_Index_t> hits;


		virtual TCanvas* Draw(int id)const;

	private:
		vector <TH1D*> hWaves;
};

#endif // _IntVetoSummary_

