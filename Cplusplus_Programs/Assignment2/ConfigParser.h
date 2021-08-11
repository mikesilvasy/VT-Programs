
#ifndef CONFIG_PARSER_H__
#define CONFIG_PARSER_H__

#include <string>
#include <vector>
#include <utility>
#include <map>



class ConfigParser
{

public:
	ConfigParser();
	~ConfigParser();

	bool read(const std::string& file_name);
	bool write(const std::string& file_name);

	bool set(const std::string& section,
		 const std::string& option, const std::string& value);

	std::pair<bool, std::string> get(const std::string& section,
					 const std::string& option) const;

	std::pair<bool, int> getInt(const std::string& section,
				    const std::string& option) const;

	std::pair<bool, double> getDouble(const std::string& section,
					  const std::string& option) const;

	std::pair<bool, bool> getBool(const std::string& section,
				      const std::string& option) const;

	bool hasSection(const std::string& section) const;
	bool hasOption(const std::string& section,
                       const std::string& option) const;

	std::vector<std::string> getSections() const;
	std::vector<std::string> getOptions(const std::string& section) const;

	bool addSection(const std::string& section);

	bool removeSection(const std::string& section);

	bool removeOption(const std::string& section,
			  const std::string& option);


private:
	std::map<std::string, std::map<std::string, std::string>> config;

};

std::ostream& operator<< (std::ostream& stream, const ConfigParser& cfg);

#endif
