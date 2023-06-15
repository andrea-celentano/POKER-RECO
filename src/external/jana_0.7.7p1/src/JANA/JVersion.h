// $Id: JVersion.h 2446 2017-01-17 13:49:37Z davidl $
//
//    File: JVersion.h
// Created: Wed Apr  2 12:39:36 EDT 2008
// Creator: davidl (on Darwin fwing-dhcp13.jlab.org 8.11.1 i386)
//

#ifndef _JVersion_
#define _JVersion_

#include <string>
#include <sstream>


class JVersion{
	public:
		JVersion();
		virtual ~JVersion();
		virtual const char* className(void){return static_className();}
		static const char* static_className(void){return "JVersion";}
		
		enum{
			major = 0,
			minor = 7,
			build = 7
		};
		
		static unsigned int GetMajor(void){return major;}
		static unsigned int GetMinor(void){return minor;}
		static unsigned int GetBuild(void){return build;}
		      static string GetDevStatus(void){return string("p1");} // return either "dev" or ""
		
		static string GetVersion(void){
			std::stringstream ss;
			ss<<major<<"."<<minor<<"."<<build<<GetDevStatus();
			return ss.str();
		}
		
		static string GetIDstring(void){return "$Id: JVersion.h 2446 2017-01-17 13:49:37Z davidl $";}
		static string GetSVNrevision(void){return ExtractContent("$Revision: 2446 $");}
		static string GetDate(void){return ExtractContent("$Date: 2017-01-17 08:49:37 -0500 (Tue, 17 Jan 2017) $");}
		static string GetURL(void){return ExtractContent("$URL: https://phys12svn.jlab.org/repos/tags/jana_0.7.7p1/src/JANA/JVersion.h $");}
		
	protected:
		
		static string ExtractContent(const char *ccstr){
			/// Attempt to cut off everything leading up to and including
			/// the first space character and everything after and
			/// including the last space character of the given string.
			string str = ccstr;
			string::size_type pos_start = str.find_first_of(" ", 0);
			if(pos_start==string::npos)return str;
			string::size_type pos_end = str.find_last_of(" ", str.size());
			if(pos_end==string::npos)return str;
			return str.substr(pos_start+1, pos_end-(pos_start+1));
		}
		
	
	private:

};

#endif // _JVersion_


