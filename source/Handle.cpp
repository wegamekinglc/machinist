 
#include "Handle.h"
#include <cstdlib>

string EnvironmentValue(const string& name)
{
	string retval;
	char* ret = getenv(name.c_str());
	if(ret == nullptr) {
		THROW("Can't find '" + name + "' in environment");
	} else {
		retval = string(ret);
	}
	return retval;
}
