// $Id$
//
//    File: Cerenkov.h
// Created: Sat Jul 29 03:31:37 EDT 2023
// Creator: clasana (on Linux jdaq8 3.10.0-1160.88.1.el7.x86_64 x86_64)
//

#ifndef _Cerenkov_
#define _Cerenkov_

#include <JANA/JObject.h>
#include <JANA/JFactory.h>
#include <DAQ/fa250ConvertedHit.h>
#include <TT/TranslationTable.h>

class CerenkovHit:public jana::JObject{
	public:
		JOBJECT_PUBLIC(CerenkovHit);
		
		// Add data members here. For example:
		// int id;
		// double E;
		
		// This method is used primarily for pretty printing
		// the second argument to AddString is printf style format
		void toStrings(vector<pair<string,string> > &items)const{
			AddString(items, "index", "%4d", m_channel.index);
			AddString(items, "readout", "%4d",m_channel.readout);
		}
		
		TranslationTable::CERENKOV_Index_t m_channel;



		ClassDef(CerenkovHit,1);
};

#endif // _Cerenkov_

