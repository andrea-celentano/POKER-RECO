#include "JTxtOutput.h"

JTxtOutput::JTxtOutput() :
		m_file(0){
	jout << "JTxtOutput creator called" << endl;

}

JTxtOutput::~JTxtOutput() {
  if (m_file) {
  		delete m_file;
		m_file=0;
  	}

  jout<<"JTxtOutput destructor ends"<<endl;fflush(stdout);
}

int JTxtOutput::OpenOutput(string fname) {
	jout << "JTxtOutput::OpenOutput is called with filename: " << fname << endl;
	if (m_isOpen == 0) {
		m_file = new ofstream(fname.c_str());
		m_isOpen = 1;

	} else {
		jout << "Already opened, nothing to do" << endl;
	}
}

int JTxtOutput::CloseOutput() {
  jout << "JTxtOutput::CloseOutput is called m_isOpen:" <<m_isOpen<< endl;
  fflush(stdout);
	if (m_isOpen!=0) {
	  	m_isOpen = 0;
		m_file->close();
	
	} else {
		jout << "Already closed, nothing to do" << endl;
	}
	return NOERROR;
}


ofstream* JTxtOutput::GetPointer() {
	return m_file;
}
