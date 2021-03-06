 
#include "File.h"
#include <string>
#include <fstream>
#include <iostream>
#include <istream>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

namespace fs = boost::filesystem;

void File::Read
	(const string& filename,
	 vector<string>* dst)
{
	std::ifstream src(filename);
	char buf[2048];
	while (src.getline(buf, 2048))
	{
		dst->push_back(string(buf));
	}
}

namespace
{
	bool IsSlash(char c)
	{
		return c == '/' || c == '\\';
	}

	// open source globbing function, lightly edited
	bool wildcmp(const char *wild, const char *string)
	{
		// Written by Jack Handy - <A href="mailto:jakkhandy@hotmail.com">jakkhandy@hotmail.com</A>
		const char *cp = NULL, *mp = NULL;

		while (*string && *wild != '*')
		{
			if (*wild != *string && *wild != '?')
				return false;
			++wild;
			++string;
		}

		while (*string)
		{
			if (*wild == '*')
			{
				if (!*++wild)
					return true;
				mp = wild;
				cp = string + 1;
			}
			else if (*wild == *string || *wild == '?')
			{
				++wild;
				++string;
			}
			else
			{
				wild = mp;
				string = cp++;
			}
		}

		while (*wild == '*')
			++wild;
		return !*wild;
	}
}

string File::Path(const string& dir_in)
{
	return (dir_in.empty() || dir_in == ".")
			? string()
			: (IsSlash(dir_in.back()) ? dir_in : dir_in + "\\");
}
string File::CombinedPath(const string& path1, const string& path2)
{
	return (path2.empty() || path2[0] == '.')
			? path1 + path2 // path2 is relative
			: path2;	
}

string File::PathOnly(const string& filename)
{
	string retval(filename);
	while (!retval.empty() && !IsSlash(retval.back()))
		retval.pop_back();
	return retval;
}

vector<string> File::List
	(const string& dir,
	 const string& pattern,
	 const vector<string>& reject_patterns)
{
	fs::recursive_directory_iterator it(dir);
	fs::recursive_directory_iterator endit;
	vector<string> retval;
	const boost::regex filter(pattern);
	while(it != endit)
	{
		bool reject = false;
		boost::smatch what;
		string file_name = it->path().filename().string();
		if(boost::regex_match(file_name, what, filter)) {
			for (auto pr = reject_patterns.begin(); pr != reject_patterns.end() && !reject; ++pr)
				reject = wildcmp(pr->c_str(), file_name.c_str());
			if (!reject)
				retval.push_back(file_name);
		}
		++it;
	}
	return retval;
}

string File::InfoType(const string& filename)
{
	// filenames should have the form "<name>.<type>.if"
	auto dot = filename.find('.');
	REQUIRE(dot != string::npos, "Input filename should have two separator periods");
	string rest = filename.substr(dot + 1);
	dot = rest.find('.');
	REQUIRE(dot != string::npos, "Input filename should have two separator periods");
	return rest.substr(0, dot);
}

string File::InfoName(const string& filename)
{
	// filenames should have the form "<name>.<type>.if"
	auto dot = filename.find('.');
	REQUIRE(dot != string::npos, "Input filename should have two separator periods");
	return filename.substr(0, dot);
}

string File::DirInfoName(const string& dir)
{
    // only take the leaf directory name
    auto last = dir.find_last_of("/\\");
    return last == string::npos 
                    ? dir
                    : dir.substr(last + 1);
}
