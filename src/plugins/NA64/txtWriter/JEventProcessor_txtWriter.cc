// $Id$
//
//    File: JEventProcessor_txtWriter.cc
// Created: Thu Oct 20 10:07:53 UTC 2022
// Creator: clasrun (on Linux jdaq6 3.10.0-1160.31.1.el7.x86_64 x86_64)
//

#include "JEventProcessor_txtWriter.h"
using namespace jana;

// Routine used to create our JEventProcessor
#include <JANA/JApplication.h>
#include <JANA/JFactory.h>
#include "DAQ/fa250WaveboardV1Hit.h"
#include <DAQ/eventData.h>

#include <system/JTxtOutput.h>
#include <system/BDXEventProcessor.h>

extern "C" {
void InitPlugin(JApplication *app) {
    InitJANAPlugin(app);
    app->AddProcessor(new JEventProcessor_txtWriter());
}
} // "C"

//------------------
// JEventProcessor_txtWriter (Constructor)
//------------------
JEventProcessor_txtWriter::JEventProcessor_txtWriter() {

}

//------------------
// ~JEventProcessor_txtWriter (Destructor)
//------------------
JEventProcessor_txtWriter::~JEventProcessor_txtWriter() {

}

//------------------
// init
//------------------
jerror_t JEventProcessor_txtWriter::init(void) {
    // This is called once at program startup. If you are creating
    // and filling historgrams in this plugin, you should lock the
    // ROOT mutex like this:
    //
    // japp->RootWriteLock();
    //  ... fill historgrams or trees ...
    // japp->RootUnLock();
    //
    m_isFirstCallToBrun = 1;
    return NOERROR;
}

//------------------
// brun
//------------------
jerror_t JEventProcessor_txtWriter::brun(JEventLoop *eventLoop, int32_t runnumber) {
    // This is called whenever the run number changes
    if (m_isFirstCallToBrun) {
        jout << "JEventProcessor_BDXMiniClusters::brun searching m_RootOutput" << endl;
        string class_name, this_class_name;
        string joutput_name;
        BDXEventProcessor *m_BDXEventProcessor;
        vector<JEventProcessor*> m_processors = app->GetProcessors();
        vector<JEventProcessor*>::iterator m_processors_it;

        m_isFirstCallToBrun = 0;
        class_name = "BDXEventProcessor";
        joutput_name = "JTxtOutput";
        //Now I need to determine which processor is the one holding the output. Discussing with David, he suggested just to check the class name, since
        //a dynamic cast may not work with plugins
        for (m_processors_it = m_processors.begin(); m_processors_it != m_processors.end(); m_processors_it++) {
            if ((*m_processors_it) != 0) {
                this_class_name = string((*m_processors_it)->className());
                if (this_class_name == class_name) {
                    m_BDXEventProcessor = (BDXEventProcessor*) (*m_processors_it);
                    if (m_BDXEventProcessor->getOutput() == 0) {
                        jerr << "BDXEventProcessor JOutput is null!" << endl;
                        break;
                    }
                    if (string(m_BDXEventProcessor->getOutput()->className()) == joutput_name) {
                        m_TxtOutput = (JTxtOutput*) (m_BDXEventProcessor->getOutput());
                        jout << "Got JROOTOutput!" << endl;
                    } else {
                        jerr << "BDXEventProcessor JOutput is not null BUT class is: " << m_BDXEventProcessor->getOutput()->className() << endl;
                    }
                }
            }
        }
    }
    return NOERROR;
}

//------------------
// evnt
//------------------
jerror_t JEventProcessor_txtWriter::evnt(JEventLoop *loop, uint64_t eventnumber) {
    // This is called for every event. Use of common resources like writing
    // to a file or filling a histogram should be mutex protected. Using
    // loop->Get(...) to get reconstructed objects (and thereby activating the
    // reconstruction algorithm) should be done outside of any mutex lock
    // since multiple threads may call this method at the same time.
    // Here's an example:
    //
    // vector<const MyDataClass*> mydataclasses;
    // loop->Get(mydataclasses);
    //


       vector<const fa250WaveboardV1Hit*> m_waveforms;
       vector<const fa250WaveboardV1Hit*>::const_iterator m_waveforms_it;

       loop->Get(m_waveforms);

       const eventData *tData;

       try {
           loop->GetSingle(tData);
       } catch (unsigned long e) {
           jout << "JEventProcessor_Trigger::evnt no eventData bank this event" << std::endl;
           return OBJECT_NOT_AVAILABLE;
       }


       // Lock ROOT
       japp->RootWriteLock();
       (*m_TxtOutput->GetPointer())<<tData->runN<<" "<<tData->eventN<<" "<<tData->time<<" "<<m_waveforms.size()<<std::endl;
       for (m_waveforms_it = m_waveforms.begin(); m_waveforms_it != m_waveforms.end(); m_waveforms_it++) {

               int channel = (*m_waveforms_it)->m_channel.channel;
               int size=(*m_waveforms_it)->samples.size();
               (*m_TxtOutput->GetPointer())<<channel<<" "<<size<<std::endl;
               for (int ii=0;ii<size;ii++)
                   (*m_TxtOutput->GetPointer())<<(*m_waveforms_it)->samples[ii]<<" ";
               (*m_TxtOutput->GetPointer())<<std::endl;
       }
    japp->RootUnLock();

    return NOERROR;
}

//------------------
// erun
//------------------
jerror_t JEventProcessor_txtWriter::erun(void) {
    // This is called whenever the run number changes, before it is
    // changed to give you a chance to clean up before processing
    // events from the next run number.
    return NOERROR;
}

//------------------
// fini
//------------------
jerror_t JEventProcessor_txtWriter::fini(void) {
    // Called before program exit after event processing is finished.
    return NOERROR;
}

