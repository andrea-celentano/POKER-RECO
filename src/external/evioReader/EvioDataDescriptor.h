/* 
 * File:   EvioDataDescriptor.h
 * Author: gavalian
 *
 * Created on May 13, 2014, 11:29 AM
 */

#ifndef __EVIODATADESCRIPTOR__
#define	__EVIODATADESCRIPTOR__
#include <iostream>
#include <string>
#include <vector>
#include "common_std.h"

using namespace std;

typedef  struct {
    string name;
    int    type;
    int    tag;
    int    num;
} DescriptorEntry_t;

class EvioDataDescriptor {
	
public:
    
    EvioDataDescriptor();
    EvioDataDescriptor(int tag);
    EvioDataDescriptor(int tag, const char *format);
    EvioDataDescriptor(const EvioDataDescriptor& orig);
    
    virtual ~EvioDataDescriptor();
    
    void addEntry(const char *name, int num, int type);
    void parseFormat(int tag, const char *format);
    int  entries();
    DescriptorEntry_t getEntry(int index);
    int  getTag(){ return bankTag;};
    
    //void show();
    
private:
    vector<string> stringTokenize(const string &_str,const string &_delim);
    int  bankTag;
    vector<DescriptorEntry_t> bankentries;
    
};

#endif	/* EVIODATADESCRIPTOR_H */

