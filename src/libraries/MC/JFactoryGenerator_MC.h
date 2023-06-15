// $Id$
//
//    File: JFactoryGenerator_MC.h
// Created: Tue Mar  1 00:57:57 CET 2016
// Creator: celentan (on Linux localhost.localdomain 2.6.32-573.12.1.el6.x86_64 x86_64)
//

#ifndef _JFactoryGenerator_MC_
#define _JFactoryGenerator_MC_

#include <JANA/jerror.h>
#include <JANA/JFactoryGenerator.h>
#include <JANA/JFactory.h>

#include "GenParticle.h"
#include "CalorimeterMCHit.h"
#include "IntVetoMCHit.h"
#include "ExtVetoMCHit.h"
#include "PaddlesMCHit.h"
#include "UserMCData.h"

class JFactoryGenerator_MC: public jana::JFactoryGenerator{
	public:
		JFactoryGenerator_MC(){}
		virtual ~JFactoryGenerator_MC(){}
		virtual const char* className(void){return static_className();}
		static const char* static_className(void){return "JFactoryGenerator_MC";}
		
		jerror_t GenerateFactories(jana::JEventLoop *loop){
			loop->AddFactory(new JFactory<GenParticle> ());
			loop->AddFactory(new JFactory<CalorimeterMCHit> ());
			loop->AddFactory(new JFactory<IntVetoMCHit> ());
			loop->AddFactory(new JFactory<ExtVetoMCHit> ());
			loop->AddFactory(new JFactory<PaddlesMCHit> ());
			loop->AddFactory(new JFactory<UserMCData> ());

			return NOERROR;
		}

};

#endif // _JFactoryGenerator_MC_

