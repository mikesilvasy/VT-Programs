#include <iostream>
#include "ConfigParser.h"


using namespace std;


int main()
{
	ConfigParser cfg;
	string file_name, val;

	cout << "Enter ini file name: ";
	cin >> file_name;

	if(cfg.read(file_name.c_str()))
	{
		cout << "Print out starting values: " << endl;
		cout << cfg;


		cout << "Looking at section DEFAULT for ";
		cout << "option ServerAliveInterval" << endl;;

		if(cfg.hasOption("DEFAULT", "ServerAliveInterval"))
		{
			val = cfg.get("DEFAULT", "ServerAliveInterval").second;
			cout << "Found it. Current value: " << val << endl;

			cout << "Trying to set it to 255." << endl;
			cfg.set("DEFAULT", "ServerAliveInterval", "255");

			val = cfg.get("DEFAULT", "ServerAliveInterval").second;
			cout << "New value: " << val << endl;

			auto p = cfg.getInt("DEFAULT", "ServerAliveInterval");

			if(!p.first)
			{
				cout << "Couldn't convert value into ";
				cout << "an integer." << endl;
			}
			else if(p.second != 255)
			{
				cout << "Wrong number." << endl;
			}
			else
			{
				cout << "Properly converted value ";
				cout << "into an integer." << endl;
			}
		}

		if(cfg.hasSection("foobar"))
		{
			cout << "Found an unexpected section: foobar" << endl;
		}


		if(cfg.addSection("canvas.vt.edu"))
		{
			cout << "Added section canvas.vt.edu ";
			cout << "with port option with value 22" << endl;
			cfg.set("canvas.vt.edu", "port", "22");
		}
		else
		{
			cout << "Couldn't add section: canvas.vt.edu" <<endl;
		}


//		cout << "Testing All Values Are Strings value for are they treated as numbers?" << std::endl;
//		auto b = cfg.getBool(/*"canvas.vt.edu"*/"All Values Are Strings", "are they treated as numbers?");
		cout << "Testing DEFAULT value for Compression" <<endl;
        auto b = cfg.getBool(/*"canvas.vt.edu"*/"DEFAULT", "Compression");

		if(b.first)
		{
            cout << "are they treated as numbers?: " << b.second << std::endl;
//			cout << "Compression: " << b.second << endl;
		}
		else
		{
			cout << "Couldn't convert bool." << endl;
		}

		cout << "Trying to remove ForwardX11 from ";
		cout << "topsecret.server.com" << endl;

		if(cfg.removeOption("topsecret.server.com", "ForwardX11"))
		{
			cout << "Success!" <<endl;
		}

		cout << "Removing section topsecret.server.com." << endl;

		if(cfg.removeSection("topsecret.server.com"))
		{
			cout << "Success!" <<endl;
		}

//		cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
//		cout << cfg << endl;

		cout << "Now write the modified file to: ";
		cout << ("new_" + file_name) << endl;

		cfg.write("new_" + file_name);

	}

	return 0;
}

