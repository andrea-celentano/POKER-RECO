/*
 * BDXObject.cc
 *
 *  Created on: Apr 3, 2016
 *      Author: celentan
 */

#include "BDXObject.h"
#include "TCanvas.h"

BDXObject::BDXObject():m_canvas(0){
}

BDXObject::~BDXObject() {
	if (m_canvas) delete m_canvas;
	m_canvas=0;
}


