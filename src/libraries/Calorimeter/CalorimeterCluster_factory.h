// $Id$
//
//    File: CalorimeterCluster_factory.h
// Created: Tue Mar 22 11:19:57 CET 2016
// Creator: celentan (on Linux apcx4 2.6.32-504.30.3.el6.x86_64 x86_64)
//

#ifndef _CalorimeterCluster_factory_
#define _CalorimeterCluster_factory_

#include <JANA/JFactory.h>
#include "CalorimeterCluster.h"
#include <vector>
#include <utility>      // std::pair, std::make_pair



class CalorimeterHit;

class CalorimeterCluster_factory:public jana::JFactory<CalorimeterCluster>{
	public:
		CalorimeterCluster_factory();
		~CalorimeterCluster_factory(){};



		void setCluster(CalorimeterCluster *cluster,const CalorimeterHit *seed,const std::vector<const CalorimeterHit*> &hits)const;


	private:
		jerror_t init(void);						///< Called once at program start.
		jerror_t brun(jana::JEventLoop *eventLoop, int32_t runnumber);	///< Called everytime a new run number is detected.
		jerror_t evnt(jana::JEventLoop *eventLoop, uint64_t eventnumber);	///< Called every event.
		jerror_t erun(void);						///< Called everytime run number changes, provided brun has been called.
		jerror_t fini(void);						///< Called after last event of last event source has been processed.

		double m_CLUSTER_HIT_THR;
		double m_CLUSTER_SEED_THR;
		double m_CLUSTER_POS_W0;
};

#endif // _CalorimeterCluster_factory_

