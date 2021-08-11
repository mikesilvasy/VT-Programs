#include "ConfigParser.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>

/* need these */
using std::map;
using std::pair;
using std::endl;
using std::string;
using std::vector;

vector<string> sections;
map<string, map<string, string>> config;


// On my honor:
//
// - I have not discussed the C++ language code in my program with
//   anyone other than my instructor.
//
// - I have not used C++ language code obtained from another student,
//   or any other unauthorized source, either modified or unmodified.
//
// - If any C++ language code or documentation used in my program
//   was obtained from an allowed source, such as a text book or course
//   notes, that has been clearly noted with a proper citation in
//   the comments of my program.
//
//    <Mike Silvasy>



/*
 * Constructor
 *
 */
ConfigParser::ConfigParser()
{
	/* don't have to do anything else here */
	addSection("DEFAULT");
}

/*
 * Destructor
 *
 */
ConfigParser::~ConfigParser()
{
	/* don't have to do anything here */
}


/*
 * Reads/parses configuration information from file_name.
 * See project document for more information.
 *
 *  Returns true:
 *		If the file is opened and parsed correctly.
 *
 *  Returns false:
 *		If the file can't be opened.
 *		If we encounter a duplicate section name other than DEFAULT.
 *
 */
bool ConfigParser::read(const string& file_name)
{
    std::ifstream inputFile(file_name);
    string nextLine;
    std::getline(inputFile, nextLine);

    if (!inputFile) {
        return false;
    }

    bool lastLineKeyValue = false;
    string lastKey;
    string lastSection = "DEFAULT";
    int prevIndex = -1;

    while (inputFile) {
//        std::cout << nextLine << " =======> " << lastLineKeyValue << std::endl;

        vector<string> lines;
        std::stringstream ss(nextLine);
        string token;
        while (std::getline(ss, token, ' ')) {
            lines.push_back(token);
        }

        int index = -1;
        for (int i = 0; i < lines.size(); i++) {
//            std::cout << lines[i];
            if (lines[i].size() > 0 && index == -1) {
                index = i;
            }
        }
/*        if (index != -1){
            std::cout << "-->" << lines[index] << std::endl;
        }
*/
        if (index != -1) {
            string firstWord = lines[index];
            if (firstWord[0] != ';' && firstWord[0] != '#') {
                if (firstWord[0] == '[') {
                    string section;
                    int i = 0;
                    while (nextLine[i] != '[') {
                        i += 1;
                    }
                    i += 1;
                    while (nextLine[i] != ']') {
                        section = section + nextLine[i];
                        i += 1;
                    }

                    for (int x = 0; x < sections.size(); x++) {
                        if (section.compare(sections[x]) == 0 && section.compare("DEFAULT") != 0) {
                            return false;
                        }
                    }
                    addSection(section);

                    lastLineKeyValue = false;
                    lastSection = section;
                }
                else {
                    vector<string> linesByEqual;
                    std::stringstream ss(nextLine.substr(index));
                    string token;
                    while (std::getline(ss, token, '=')) {
                        linesByEqual.push_back(token);
                    }

/*                    for (int i = 0; i < linesByEqual.size(); i++) {
                        std::cout << linesByEqual[i] << "/";
                    }
                    std::cout << std::endl;
*/

                    vector<string> linesByColon;
                    std::stringstream ss2(nextLine.substr(index));
                    while (std::getline(ss2, token, ':')) {
                        linesByColon.push_back(token);
                    }

/*                    for (int i = 0; i < linesByColon.size(); i++) {
                        std::cout << linesByColon[i] << "$";
                    }
                    std::cout << std::endl;
*/

                    string key;
                    string value;
                    if (linesByEqual.size() > 1) {
                        string keyLine = linesByEqual[0];
                        string valueLine = linesByEqual[1];

                        int endIndex = keyLine.size() - 1;
                        while (keyLine[endIndex] == ' ') {
                            endIndex -= 1;
                        }
                        key = keyLine.substr(0, endIndex + 1);

                        int startIndex = 0;
                        while (valueLine[startIndex] == ' ') {
                            startIndex += 1;
                        }
                        value = valueLine.substr(startIndex, valueLine.size());

                        lastLineKeyValue = true;
                        lastKey = key;
                        prevIndex = index;
                    }
                    else if (linesByColon.size() > 1) {
                        string keyLine = linesByColon[0];
                        string valueLine = linesByColon[1];

                        int endIndex = keyLine.size() - 1;
                        while (keyLine[endIndex] == ' ') {
                            endIndex -= 1;
                        }
                        key = keyLine.substr(0, endIndex + 1);

                        int startIndex = 0;
                        while (valueLine[startIndex] == ' ') {
                            startIndex += 1;
                        }
                        value = valueLine.substr(startIndex, valueLine.size());

                        lastLineKeyValue = true;
                        lastKey = key;
                        prevIndex = index;
                    }
                    else {
//                        std::cout << "INDENT" << std::endl;
                        if (lastLineKeyValue && prevIndex != -1 && index > prevIndex) {
                            value = "\n" + linesByEqual[0];
                        }
                        else {
//                            std::cout << linesByEqual.size() << "/" << linesByColon.size() << std::endl;
                            string line = linesByEqual[0];
                            if (line[line.size() - 1] == '=' || line[line.size() - 1] == ';') {
                                int endIndex = line.size() - 2;
                                while (line[endIndex] == ' ') {
                                    endIndex -= 1;
                                }
                                line = line.substr(0, endIndex + 1);
                            }

                            lastLineKeyValue = true;
                            lastKey = line;
                            value = "";
                            prevIndex = index;
                        }
                    }

//                    std::cout << key << "/" << value << std::endl;
                    config[lastSection][lastKey] = config[lastSection][lastKey] + value;
                }
            }
            else {
                lastLineKeyValue = false;
            }
        }
        else {
            lastLineKeyValue = false;
        }

        std::getline(inputFile, nextLine);
    }

/*    std::cout << std::endl;
    for (auto e : config) {
        std::cout << "[ " << e.first << " ]" << std::endl;
        for (auto elem : config[e.first]) {
            std::cout << elem.first << " ----> " << elem.second << std::endl;
        }
    }
*/

//    std::cout << std::endl;

    return true;
}


/*
 * Writes the contents of the ConfigParser object to file_name.
 *
 * Format:
 *
 * [ Section Name ]
 * key1 = value1
 * key2 = value2
 * 			; this a blank line
 * [ Other Sections]
 * ...
 *
 *  Returns true:
 *		If the file is opened and written correctly.
 */
bool ConfigParser::write(const string& file_name)
{
/*    char file[file_name.size()];
    for (int i = 0; icout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
		cout << cfg << endl; < file_name.size(); i++) {
        file[i] = file_name[i];
    }
*/
    std::ofstream fP(file_name);
    if (!fP) {
//        std::cout << "Didn't work." << std::endl;
        return false;
    }
    else {
        for (auto e : config) {
            fP << "[ " << e.first << " ]\n";
            for (auto elem : config[e.first]) {
                fP << elem.first << " = " << elem.second << "\n";
            }
            fP << "\n";
        }

    }

    for (auto e: config) {
//        std::cout << e.first << "$$$$$$$" << std::endl;
    }

    fP.close();

    return true;
}


/*
 * Sets option in section to value.
 *
 * Return false:
 *	If the section doesn't exist.
 *
 * Returns true otherwise.
 */
bool ConfigParser::set(const string& section,
			const string& option, const string& value)
{
    if (hasSection(section)) {
        config[section][option] = value;
        return true;
    }
    return false;
}


/*
 * Searches for option's value in section.
 *
 * If section/option don't exist the conversion fails.
 *
 * Returns a pair of <bool, string>
 * 	first is set to true if the value exists, false otherwise.
 *	If the conversion succeeds, second is the stored string value.
 *	If the value doesn't exist, it doesn't matter what second is set to.
 *
 *
 */
pair<bool, string> ConfigParser::get(const string& section,
				     const string& option) const
{
    pair<bool, string> p;
    p.first = false;
    p.second = "";
    for (auto const &e : config) {
        if (section.compare(e.first) == 0) {
            for (auto const &elem : e.second) {
                if (option.compare(elem.first) == 0) {
                    p.first = true;
                    p.second = elem.second;
                }
            }
        }
    }
    return p;
}


/*
 * Searches for option's value in section and converts it to a int if possible.
 *
 * If section/option don't exist the conversion fails.
 *
 * Returns a pair of <bool, int>
 * 	first is set to true if converison succeeded, false otherwise.
 *	If the conversion succeeds, second is the converted int value.
 *	If the conversion fails, it doesn't matter what second is set to.
 *
 *
 */
pair<bool, int> ConfigParser::getInt(const string& section,
				     const string& option) const
{
	pair<bool, int> p;
	p.first = false;
	p.second = -1;
    for (auto const &e : config) {
        if (section.compare(e.first) == 0) {
            for (auto const &elem : e.second) {
                if (option.compare(elem.first) == 0) {
                    string value = elem.second;
                    int val;
                    try {
                        val = stoi(value);
                        p.first = true;
                        p.second = val;
                    }
                    catch (std::invalid_argument& e) {
                        return p;
                    }
                }
            }
        }
    }
    return p;
}



/*
 * Searches for option's value in section and converts it to a double
 * if possible.
 *
 * If section/option don't exist the conversion fails.
 *
 * Returns a pair of <bool, bool>
 * 	first is set to true if converison succeeded, false otherwise.
 *	If the conversion succeeds, second is the converted double value.
 *	If the conversion fails, it doesn't matter what second is set to.
 *
 *
 */
pair<bool, double> ConfigParser::getDouble(const string& section,
					   const string& option) const
{
    pair<bool, double> p;
    p.first = false;
    p.second = -1.0;
    for (auto const &e : config) {
        if (section.compare(e.first) == 0) {
            for (auto const &elem : e.second) {
                if (option.compare(elem.first) == 0) {
                    string value = elem.second;
                    double val;
                    try {
                        val = stod(value);
                        p.first = true;
                        p.second = val;
                    }
                    catch (std::invalid_argument& e) {
                        return p;
                    }
                }
            }
        }
    }
    return p;
}


/*
 * Searches for option's value in section and converts it to a bool if possible.
 *
 * If the value isn't one of the options below or if section/option
 * don't exist the conversion fails.
 *
 * Returns a pair of <bool, bool>
 * 	first is set to true if converison succeeded, false otherwise.
 *	If the conversion succeeds, second is the converted boolean value.
 *	If the conversion fails, it doesn't matter what second is set to.
 *
 * 	Converts to true: "true", "yes", "on", "1"
 * 	Converts to false: "false", "no", "off", "0"
 *
 */
pair<bool, bool> ConfigParser::getBool(const string& section,
					const string& option) const
{
	pair<bool, bool> p(false, false);
    for (auto const &e : config) {
        if (section.compare(e.first) == 0) {
//            std::cout << "*******" << std::endl;
            for (auto const &elem : e.second) {
//a                std::cout << "*******" << elem.first << std::endl;
                if (option.compare(elem.first) == 0) {
                    string value = elem.second;
//                    std::cout << "*******" << value << std::endl;
                    if (value.compare("true") == 0 || value.compare("yes") == 0 ||
                        value.compare("on") == 0 || value.compare("1") == 0) {
                        p.first = true;
                        p.second = true;
                    }
                    else if (value.compare("false") == 0 || value.compare("no") == 0 ||
                             value.compare("off") == 0 || value.compare("0") == 0) {
                        p.first = true;
                        p.second = false;
                    }
                }
            }
        }
    }
    return p;
}


/*
 * Returns true if the section exists, false otherwise.
 *
 */
bool ConfigParser::hasSection(const string& section) const
{
    for (int i = 0; i < sections.size(); i++) {
        if (section.compare(sections[i]) == 0) {
            return true;
        }
    }
    return false;
}


/*
 * Returns true if section exists and it has option, false otherwise.
 *
 */
bool ConfigParser::hasOption(const string& section, const string& option) const
{
    for (auto const &e : config) {
        if (section.compare(e.first) == 0) {
            for (auto const &elem : e.second) {
                if (option.compare(elem.first) == 0) {
                    return true;
                }
            }
        }
    }
    return false;
}



/*
 * Returns a vector containing all of the section names.
 *
 * Provided for you.
 */
vector<string> ConfigParser::getSections() const
{
	vector<string> sections;

	for(const auto& section : config)
	{
		sections.push_back(section.first);
	}

	return sections;
}


/*
 * Returns a vector containing all of the option names in section.
 *
 */
vector<string> ConfigParser::getOptions(const string& section) const
{
	vector<string> options;
	for (const auto& e : config) {
        if (section.compare(e.first) == 0) {
            for (const auto& elem : e.second) {
                options.push_back(elem.first);
            }
        }
	}
	return options;
}


/*
 * Adds a new section.
 *	If the section doesn't exist, add it and return true
 *	If the section already exists, return false
 *
 */
bool ConfigParser::addSection(const string& section)
{
    bool hasSection = false;
    for (int i = 0; i < sections.size(); i++) {
        if (section.compare(sections[i]) == 0) {
            hasSection = true;
        }
    }

    if (!hasSection) {
        config[section] = map<string, string>();
        sections.push_back(section);
        return true;
    }

    return false;
}


/*
 * Removes a section.
 *	If the section exists and the removal goes fine return true.
 *	If the section doesn't exist return false.
 *
 */
bool ConfigParser::removeSection(const string& section)
{
    if (!hasSection(section)) {
        return false;
    }

    config.erase(section);
    vector<string> temp;
    for (int i = 0; i < sections.size(); i++) {
        if (section.compare(sections[i]) != 0) {
            temp.push_back(sections[i]);
        }
    }
    sections = temp;
    return true;
}


/*
 * Removes a option.
 *	If the section and option exist and the removal goes fine return true.
 *	If the section or option doesn't exist return false.
 *
 */
bool ConfigParser::removeOption(const string& section, const string& option)
{
    map<string, map<string, string>> temp;
    bool removed = false;

    if (hasSection(section) && hasOption(section, option)) {
        config[section].erase(option);
        return true;
    }

    return false;
}

/*
 * Overloaded << operator, lets you type:
 *	 cout << cfg;
 *
 * Where cfg is ConfigParser instance.
 * Works after you implement getSections() and getOptions()
 *
 */
std::ostream& operator<< (std::ostream& stream, const ConfigParser& cfg)
{
	for(const auto &section : cfg.getSections())
	{
		stream << "[ " <<  section << " ]"  << endl;

		for(const auto &option : cfg.getOptions(section))
		{
			size_t pos = 0;
			string value = cfg.get(section, option).second;

			while((pos = value.find("\n", pos)) != string::npos)
			{
				value.replace(pos, 1, "\n\t\t");
				pos +=3;
			}

	  		stream << "\t" << '"' << option << '"';

			if(value != "")
			{
				stream << " = " << '"' << value << '"' << endl;
			}
			else
			{
				stream << endl;
			}

		}
		stream << endl;
	}

	return stream;
}

