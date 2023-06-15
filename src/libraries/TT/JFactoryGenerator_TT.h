// $Id$
//
//    File: JFactoryGenerator_TranslationTable.h
// Created: Tue Jan 12 09:28:57 CET 2016
// Creator: celentan (on Linux apcx4 2.6.32-504.30.3.el6.x86_64 x86_64)
//

#ifndef _JFactoryGenerator_TranslationTable_
#define _JFactoryGenerator_TranslationTable_

#include <JANA/jerror.h>
#include <JANA/JFactoryGenerator.h>

#include "TranslationTable_factory.h"

class JFactoryGenerator_TT: public jana::JFactoryGenerator{
	public:
		JFactoryGenerator_TT(){}
		virtual ~JFactoryGenerator_TT(){}
		virtual const char* className(void){return static_className();}
		static const char* static_className(void){return "JFactoryGenerator_TT";}
		
		jerror_t GenerateFactories(jana::JEventLoop *loop){
			loop->AddFactory(new TranslationTable_factory());
			return NOERROR;
		}

};

#endif // _JFactoryGenerator_TranslationTable_

