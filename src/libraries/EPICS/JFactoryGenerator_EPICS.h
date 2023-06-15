// $Id$
//
//    File: JFactoryGenerator_EPICS.h
// Created: Fri Mar  9 11:23:04 EST 2018
// Creator: celentan (on Darwin celentano-macbook 17.4.0 i386)
//

#ifndef _JFactoryGenerator_EPICS_
#define _JFactoryGenerator_EPICS_

#include <JANA/jerror.h>
#include <JANA/JFactoryGenerator.h>

#include "epicsData_factory.h"

class JFactoryGenerator_EPICS: public jana::JFactoryGenerator{
	public:
		JFactoryGenerator_EPICS(){}
		virtual ~JFactoryGenerator_EPICS(){}
		virtual const char* className(void){return static_className();}
		static const char* static_className(void){return "JFactoryGenerator_EPICS";}
		
		jerror_t GenerateFactories(jana::JEventLoop *loop){
			loop->AddFactory(new epicsData_factory());
			return NOERROR;
		}

};

#endif // _JFactoryGenerator_EPICS_

