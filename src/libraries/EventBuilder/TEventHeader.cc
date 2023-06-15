/*
 * TEventHeader.cc
 *
 *  Created on: Dec 23, 2016
 *      Author: celentan
 */

#include "TEventHeader.h"
#include "EPICS/epicsData.h"

TEventHeader::TEventHeader() {
	// TODO Auto-generated constructor stub
	m_epicsData = new epicsData();
	m_eventTime = 0;
	m_runNumber = 0;
	m_eventNumber = 0;
	m_eventTS = 0;
	m_eventType = 0;
	m_eventFineTime = 0;
	m_weight = 1;
}

TEventHeader::~TEventHeader() {
	// TODO Auto-generated destructor stub
	if (m_epicsData) delete m_epicsData;
}

epicsData* TEventHeader::getEpicsData() const {
	return m_epicsData;
}

void TEventHeader::setEpicsData(epicsData *epicsData) {
	m_epicsData = epicsData;
}
void TEventHeader::copyEpicsData(const epicsData* epicsData) {
	*m_epicsData = *epicsData;
}
