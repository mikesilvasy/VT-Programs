#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <cassert>
#include <stdexcept>

#include "Map.h"
#include "HashMap.h"

using namespace std;


int main ()
{
	HashMap<string, string> test;

	cout << "Print empty map: (shouldn't print anything) " << endl;
	cout << test;

	cout << "Add a bunch of values to the map." << endl;

	test.put("hello", "world");
	test.put("CS2304", "Fall2019");
	test.put("key 1", "value 1");
	test.put("key 2", "value 2");
	test.put("key 3", "value 3");
	test.put("key 4", "value 4");
	test.put("key 5", "value 5");

	cout << "Print the filled map: " << endl;
	cout << test;

	cout << "Print the contents of the map using the public methods.\n";
	for(auto const& key : test.keys())
	{
		auto values = test.get(key);
		assert(values.size() == 1);
		cout << "\t" << key << " : " << test.get(key)[0] << endl;
	}

	cout << "Test setting and getting values:" << endl;

	cout << "Trying test[\"value 1\"] = \"another value\";\n";
	test["value 1"] = "another value";
	cout << test["value 1"] << endl;

	cout << "Testing out test.at(\"key 4\")\n";
	cout << test.at("key 4") << endl;

	cout << "Trying map[\"notinhere\"], it should print an empty string:\n";
	cout << '"' << test["notinhere"] << '"' <<  endl;

	try
	{
		cout << test.at("exceptions") << endl;
		cout << "This should never happen." << endl;

	}
	catch (std::out_of_range& e)
	{
		cout << "Properly caught exception: " << e.what() << endl;
	}

	cout << "Print the filled map: " << endl;
	cout << test;

	cout << "Is the HashMap empty?" << endl;
	cout << test.empty() << endl;

	cout << "How many elements are in the HashMap?" << endl;
	cout << test.size() << endl;

	cout << "How many buckets are in the HashMap?" << endl;
	cout << test.buckets() << endl;

	cout << "The max load factor is: " << endl;
	double factor = test.get_max_load_factor();
	cout << factor << endl;

	cout << "Halving the max load factor, should result in a rehash: \n";
	test.set_max_load_factor(factor / 2.0);

	cout << "Print the map with the new load factor: " << endl;
	cout << test;

	cout << "Delete some values and print the map: " << endl;

	test.erase("key 4");
	test.erase("key 4");
	test.erase("notinhere");

	cout << test;

	cout << "Clear the map, print the size: " << endl;
	test.clear();
	cout << test.size() << endl;


	return 0;
}
