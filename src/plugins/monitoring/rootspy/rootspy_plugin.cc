// $Id$
//
//    File: rootspy_plugin.cc
// Created: Tue Sep 15 11:45:07 EDT 2009
// Creator: davidl (on Darwin harriet.jlab.org 9.8.0 i386)
//

// Routine used to create our JEventProcessor


#include <JANA/JApplication.h>
#include <JANA/JFactory.h>
using namespace jana;

#include <DRootSpy.h>


// Entrance point for plugin
extern "C"{
void InitPlugin(JApplication *japp){
//void InitPlugin(void *japp){
	cout<<"Before InitJANAPlugin"<<endl;fflush(stdout);
	//InitJANAPlugin(japp);
	cout<<"After InitJANAPlugin"<<endl;fflush(stdout);
	DRootSpy *spy=new DRootSpy();
	}
}
