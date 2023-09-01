// $Id$
//
//    File: JFactoryGenerator_Cerenkov.h
// Created: Sat Jul 29 03:31:30 EDT 2023
// Creator: clasana (on Linux jdaq8 3.10.0-1160.88.1.el7.x86_64 x86_64)
//

#ifndef _JFactoryGenerator_Cerenkov_
#define _JFactoryGenerator_Cerenkov_

#include <JANA/jerror.h>
#include <JANA/JFactoryGenerator.h>

#include "CerenkovHit_factory.h"

class JFactoryGenerator_Cerenkov: public jana::JFactoryGenerator{
	public:
		JFactoryGenerator_Cerenkov(){}
		virtual ~JFactoryGenerator_Cerenkov(){}
		virtual const char* className(void){return static_className();}
		static const char* static_className(void){return "JFactoryGenerator_Cerenkov";}
		
		jerror_t GenerateFactories(jana::JEventLoop *loop){
			loop->AddFactory(new CerenkovHit_factory());
			return NOERROR;
		}

};

#endif // _JFactoryGenerator_Cerenkov_

