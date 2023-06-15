/* 
 * File:   EvioDataDescriptor.cpp
 * Author: gavalian
 * 
 * Created on May 13, 2014, 11:29 AM
 */

#include "EvioDataDescriptor.h"
/**
 * default constructor.
 */
EvioDataDescriptor::EvioDataDescriptor() 
{
}
/**
 * copy constructor.
 * @param orig
 */
EvioDataDescriptor::EvioDataDescriptor(const EvioDataDescriptor& orig) 
{
    bankTag = orig.bankTag;
    bankentries = orig.bankentries;
}
/**
 * Default destructor
 */
EvioDataDescriptor::~EvioDataDescriptor() {
}
/**
 * Add an entry into the descriptor.
 * @param e_name entry name
 * @param e_num entry number
 * @param e_type entry type (double = 1, int = 2)
 */
void EvioDataDescriptor::addEntry(const char *e_name, int e_num, int e_type)
{
    DescriptorEntry_t entry;
    entry.name = e_name;
    entry.num  = e_num;
    entry.type = e_type;
    bankentries.push_back(entry);
}
/**
 * Parse the input string for the format
 * @param tag the tag for the bank.
 * @param format format of the bank. 
 */
void EvioDataDescriptor::parseFormat(int tag, const char *format)
{
    bankentries.clear();
    bankTag = tag;
    vector<string> tokens = stringTokenize(string(format),string(":"));
    for(int loop = 0; loop < tokens.size(); loop+=3){
        DescriptorEntry_t entry;
        entry.name  = tokens[loop];
        entry.num   = atoi(tokens[loop+1].c_str());
        entry.type  = atoi(tokens[loop+2].c_str());
        entry.tag   = tag;
        cout << "[adding] -----> " << entry.name.c_str() << " " << entry.tag
                << "  " << entry.num << "  " << entry.type << endl;
        bankentries.push_back(entry);
    }
}

int  EvioDataDescriptor::entries()
{
    return bankentries.size();
}

DescriptorEntry_t EvioDataDescriptor::getEntry(int index)
{
    return bankentries[index];
}

vector<string> EvioDataDescriptor::stringTokenize(const string &_str,const string &_delim)
{
  vector<string> tokens;
  string::size_type lastPos = _str.find_first_not_of(_delim, 0);
  string::size_type pos = _str.find_first_of(_delim, lastPos);
  while (string::npos != pos || string::npos != lastPos)
    {
      // found a token, add it to the vector.
      tokens.push_back(_str.substr(lastPos, pos - lastPos));
      
      // skip delimiters.  Note the "not_of"
      lastPos = _str.find_first_not_of(_delim, pos);
      
      // find next "non-delimiter"
      pos = _str.find_first_of(_delim, lastPos);
    }
  return tokens;
}

