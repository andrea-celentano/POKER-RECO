// $Id$
//
//    File: JOutput.h
// Created: Tue Jan 12 14:45:40 CET 2016
// Creator: celentan (on Linux apcx4 2.6.32-504.30.3.el6.x86_64 x86_64)
//

#ifndef _JTxtOutput_
#define _JTxtOutput_

#include <JANA/JObject.h>
#include <JANA/JFactory.h>
#include "JOutput.h"

#include <string>

//ROOT headers
#include "TFile.h"
#include "TObject.h"
#include "TList.h"
#include "TCollection.h"

using namespace std;

class JTxtOutput:public JOutput{
	public:
		JOBJECT_PUBLIC(JTxtOutput);
		
		// Add data members here. For example:
		// int id;
		// double E;
		
		// This method is used primarily for pretty printing
		// the second argument to AddString is printf style format
		void toStrings(vector<pair<string,string> > &items)const{
			// AddString(items, "id", "%4d", id);
			// AddString(items, "E", "%f", E);
		}
		
		JTxtOutput();
		~JTxtOutput();


		ofstream* GetPointer();
		virtual int CloseOutput();
		virtual int OpenOutput(std::string name);
	private:
		ofstream *m_file;
};

#endif // _JOutput_

