#include "JEventSourceTRIDASDAQ.h"

// C++ headers
#include <iostream>
#include <time.h>
#include <unistd.h>
using namespace std;

// JANA headers
#include <JANA/JEvent.h>
#include <JANA/JParameterManager.h>
#include <JANA/JApplication.h>

//DAQ
#include <DAQ/fa250WaveboardV1Hit.h>
#include <DAQ/eventData.h>
#include <DAQ/epicsRawData.h>

// Constructor
JEventSourceTRIDASDAQ::JEventSourceTRIDASDAQ(const char* source_name) :
		JEventSource(source_name), curRunNumber(0), curEventNumber(0), ptReader(0), ptTimeSlice(0), ptEvent(0) {

	jout << "JEventSourceTRIDASDAQ creator: " << this << endl;

	curEventType = 0;
	source_type = kNoSource;
	overwriteRunNumber = -1;

	//TODO: check if file exists
	ptReader = new PtFileReader<sample::uncompressed>(source_name);
	source_type = kFileSource;

	//point to the first time slice
	it_ptReader = ptReader->begin();
	nEventsTimeSlice = (*it_ptReader).nEvents();
	//Create a new time slice
	ptTimeSlice = new TimeSlice<sample::uncompressed>(*it_ptReader);
	it_ptTimeSlice = ptTimeSlice->begin();

	//currEventTimeSlice = 0;
	jout << "JEventSourceTRIDASDAQ creator DONE: " << this << endl;

}

// Destructor
JEventSourceTRIDASDAQ::~JEventSourceTRIDASDAQ() {
	cout << " Closing input file " << source_name << " ." << endl;

}

// GetEvent
jerror_t JEventSourceTRIDASDAQ::GetEvent(JEvent &event) {

	event.SetRef(NULL);
	if (this->source_type == kFileSource) {
		//The counter on events is at the end of current time slice. Try to move to next time slice
		//if (currEventTimeSlice == nEventsTimeSlice) {
		if (it_ptTimeSlice == ptTimeSlice->end()) {
			it_ptReader++;
			delete ptTimeSlice;
			//It the iterator on time slices is at the end, the source is completely read.
			if (it_ptReader == ptReader->end()) {
				jout << "Source done" << endl;
				fflush(stdout);
				return NO_MORE_EVENTS_IN_SOURCE;
			} else {
				nEventsTimeSlice = (*it_ptReader).nEvents();
				ptTimeSlice = new TimeSlice<sample::uncompressed>(*it_ptReader);
				it_ptTimeSlice = ptTimeSlice->begin();
				//currEventTimeSlice = 0;
			}
		}

		ptEvent = new Event<sample::uncompressed>(*it_ptTimeSlice);

		event.SetJEventSource(this);
		event.SetRef((void*) ptEvent);
		event.SetEventNumber(ptEvent->id());
		event.SetEventTS(ptTimeSlice->id());

		curRunNumber = ptReader->runNumber();
		fflush(stdout);
		if (overwriteRunNumber != -1) {
			event.SetRunNumber(overwriteRunNumber);
		} else {
			event.SetRunNumber(curRunNumber);
		}
		it_ptTimeSlice++;
		//	currEventTimeSlice++;
		return NOERROR;

	} else {
		return EVENT_SOURCE_NOT_OPEN;
	}
}

// FreeEvent
void JEventSourceTRIDASDAQ::FreeEvent(JEvent &event) {
	if (event.GetRef() != NULL) {
		delete (Event<sample::uncompressed>*) event.GetRef();
	}
}

// GetObjects
jerror_t JEventSourceTRIDASDAQ::GetObjects(JEvent & event, JFactory_base * factory) {
/// This gets called through the virtual method of the
/// JEventSource base class. It creates the objects of the type
/// which factory is based.

/// Example: DCsegment needs DCHit. If DCHit doesn't exist already, then
/// it will be read here.
// We must have a factory to hold the data
	if (!factory) throw RESOURCE_UNAVAILABLE;

// Get name of data class we're trying to extract
	string dataClassName = factory->GetDataClassName();
//As suggested by David, do a check on the factory type to decide what to do
	JFactory<fa250WaveboardV1Hit> *fac_fa250WaveboardV1Hit = dynamic_cast<JFactory<fa250WaveboardV1Hit>*>(factory);
	JFactory<eventData> *fac_eventData = dynamic_cast<JFactory<eventData>*>(factory);

	if (fac_eventData != NULL) {
		vector<eventData*> data;
		eventData *this_eventData = new eventData();
		this_eventData->eventType = DAQ;

		Event<sample::uncompressed> *ptEvent_pointer = (Event<sample::uncompressed>*) event.GetRef();

		//take the first hit time (4 ns from 1 Jan. 2000) -- all hits in the event are within the same second!
		fine_time minTime = getDFHFullTime((*(ptEvent_pointer->begin())).frameHeader(0));

		this_eventData->time = std::chrono::duration_cast<std::chrono::seconds>(minTime).count(); //seconds from 1 Jan. 2000
		this_eventData->time += 946684800; //unix time of 1 Jan 2000 first second

		this_eventData->runN = event.GetRunNumber();
		this_eventData->eventN = event.GetEventNumber();
		this_eventData->eventTS = event.GetEventTS();

		this_eventData->triggerWords.push_back(Event<sample::uncompressed>::max_triggers_number); //currently 5
		for (int ii = 0; ii < Event<sample::uncompressed>::max_triggers_number; ii++) {
			this_eventData->triggerWords.push_back(ptEvent_pointer->nseeds(ii));
		}

		this_eventData->triggerWords.push_back(Event<sample::uncompressed>::max_plugins_number); //currently 8
		for (int ii = 0; ii < Event<sample::uncompressed>::max_plugins_number; ii++) {
			this_eventData->triggerWords.push_back(ptEvent_pointer->plugin_nseeds(ii));
		}
		for (int ii = 0; ii < Event<sample::uncompressed>::max_plugins_number; ii++) {
			this_eventData->triggerWords.push_back(ptEvent_pointer->plugin_trigtype(ii));
		}

		data.push_back(this_eventData);
		fac_eventData->CopyTo(data);
		return NOERROR;
	}
	if (fac_fa250WaveboardV1Hit != NULL) {
		vector<fa250WaveboardV1Hit*> data;
		Event<sample::uncompressed> *ptEvent_pointer = (Event<sample::uncompressed>*) event.GetRef();
		fine_time minTime = getDFHFullTime((*(ptEvent_pointer->begin())).frameHeader(0));  //take the first hit time

		//First, find the min. hit time
		for (Event<sample::uncompressed>::iterator it = ptEvent_pointer->begin(); it != ptEvent_pointer->end(); ++it) {

			Hit<sample::uncompressed> hit = (*it);	//This is the HIT
			auto abs_time = getDFHFullTime(hit.frameHeader(0));  //absolute time in 4 ns
			if (abs_time < minTime) minTime = abs_time;
		}

		//Then get hits
		for (Event<sample::uncompressed>::iterator it = ptEvent_pointer->begin(); it != ptEvent_pointer->end(); ++it) {
			Hit<sample::uncompressed> hit = (*it);	//This is the HIT
			fa250WaveboardV1Hit *fahit = new fa250WaveboardV1Hit();

			auto abs_time = getDFHFullTime(hit.frameHeader(0));  //absolute time in 4 ns
			auto delta_time = abs_time - minTime; //always >= 0a
			auto Ndelay = delta_time.count();

			fahit->m_channel.rocid = hit.frameHeader(0).TowerID;
			fahit->m_channel.slot = hit.frameHeader(0).EFCMID;
			fahit->m_channel.channel = hit.frameHeader(0).PMTID;

			fahit->chargeFirstDBnopedsub = hit.frameHeader(0).Charge;

			fahit->trigger = 0; //TODO
			fahit->timestamp = abs_time.count();

			/*To account for delays between waveforms,
			 * a number of fake samples is added at the beginning of each, equivalent to the relative delay with respect to the earliest waveform.
			 * The fake sample is the first sample in the waveform
			 */
			auto firstSample = *(hit.begin());
			for (int ii = 0; ii < Ndelay; ii++) {
				fahit->samplesRaw.push_back(firstSample);
			}

			for (auto it_ptSample = hit.begin(); it_ptSample != hit.end(); it_ptSample++) {
				fahit->samplesRaw.push_back(*it_ptSample);
			}

			data.push_back(fahit);
		}

		fac_fa250WaveboardV1Hit->CopyTo(data);
		return NOERROR;

	}
	return OBJECT_NOT_AVAILABLE;
}

