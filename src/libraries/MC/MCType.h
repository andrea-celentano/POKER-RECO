#ifndef MCTYPE_H_
#define MCTYPE_H_


#include <JANA/JObject.h>
#include <JANA/JFactory.h>

class MCType {


public:
	enum TYPE{
			CATANIA_V1=1,
			CATANIA_V2=2,
			FULL_V1=10,
			FULL_V2=20,
			JLAB_FLUX_V1=100,
			BDXmini_V1=200
	};


};

#endif /* VETOMCHIT_H_ */
