#ifndef HASHMAP_H
#define HASHMAP_H

#include <iostream>
#include <vector>
#include <utility>
#include <functional>
#include <exception>
#include <stdexcept>
#include <algorithm>

#include "Map.h"

// On my honor:
//
// - I have not discussed the C++ language code in my program with
//   anyone other than my instructor or the teaching assistants
//   assigned to this course.
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

/* forward declaration, you can ignore me */
template<class K, class V>
class HashMap;

/* Have to do this for the << with templates */
template<class K, class V>
std::ostream& operator<< (std::ostream& stream, const HashMap<K, V>& hm);

/* Our class, look here */
template <class K, class V>
class HashMap : virtual public Map <K, V>
{

public:
	HashMap(size_t buckets = 5);
	virtual ~HashMap() {};

	/* methods from the Map interface */
	virtual void clear();
	virtual size_t size() const;
	virtual bool empty() const;

	virtual bool contains(const K& key) const;

	virtual std::vector<K> keys() const;
	virtual std::vector<V> get(const K& key) const;

	virtual void put(const K& key, const V& value);
	virtual bool erase(const K& key);

	virtual V& operator[] (const K& key);
	virtual V& at(const K& key);

	/* HashMap specific functions and members */
	virtual void rehash(size_t buckets);
	virtual void set_max_load_factor(double factor);
	virtual double get_max_load_factor() const;
	virtual size_t buckets() const;

protected:
	/* the hash function */
	std::hash<K> mapHash;

	/* the hash table */
	std::vector<std::vector<std::pair<K, V>>> table;

	/* the number of elements in the HashMap */
	size_t table_size;

	/* max load factor before resizing the table
	 * the load factor is table_size / buckets (the table capactity)
	 * and when the load factor is >= to the max_load_factor
	 * the table should be resized and it's elements rehashed and stored.
	 */
	double max_load_factor;

	/* this function is a friend so it can access private members */
	friend std::ostream& operator<<<K, V> (std::ostream& stream,
						const HashMap<K, V>& hm);
};

/*constructor*/

template <class K, class V>
HashMap<K, V>::HashMap(size_t buckets)
: table(buckets), table_size(0), max_load_factor(0.75)
{
	/* above we are intialzing table, table_size, and max_load_factor */
	/* but don't we need to do anything in here */
}

/*empties the map, so that its size is 0, don't just use table.clear(),
instead iterate through each bucket and clear each vector separately.
that way the table is never truly empty and we don't have worry about
table.size() = 0; */

template <class K, class V>
void HashMap<K, V>::clear()
{
    for (std::vector<std::pair<K, V>> bucket : table) {
        bucket.clear();
    }
    table_size = 0;
}

/*returns the number of the elements (key/value pairs) in the map */

template <class K, class V>
size_t HashMap<K, V>::size() const
{
	return table_size;
}

/*returns true if the map is empty (size is 0), false otherwise */

template <class K, class V>
bool HashMap<K, V>::empty() const
{
	return table_size == 0;
}

/* sets max_load_factor to factor and if necessary resizes and
rehashes the table to meet the new max_load_factor. */

template <class K, class V>
void HashMap<K, V>::set_max_load_factor(double factor)
{
    max_load_factor = factor;
    if ((double)table_size / (double)table.size() >= factor) {
        rehash(2 * table.size() + 1);
    }
}

/*returns the max_load_factor*/

template <class K, class V>
double HashMap<K, V>::get_max_load_factor() const
{
    return max_load_factor;
}

/*returns the number of buckets in the table*/

template <class K, class V>
size_t HashMap<K,V>::buckets() const
{
    return table.size();
}

/*resizes the hash table. resizing involves creating a new table of size buckets,
then rehashing and inserting all of the elements of the current table and storing
them in the new table.*/

template <class K, class V>
void HashMap<K, V>::rehash(size_t buckets)
{
    std::vector<std::vector<std::pair<K, V>>> tempTable(buckets);
    for (int i = 0; i < table.size(); i++) {
        for (int j = 0; j < table.at(i).size(); j++) {
            int bucketNum = mapHash(table.at(i).at(j).first) % tempTable.size();
            tempTable.at(bucketNum).push_back(std::make_pair
                (table.at(i).at(j).first, table.at(i).at(j).second));
        }
    }
    table = tempTable;
}

/*allows us to access/modify values in the map like std::map type
like std::map [] will create a new map element (with a default value)
if the key doesn't already exist and then insert it.for example:put(key, V());
would insert a new element with key and default value for the type of V. */

template <class K, class V>
V& HashMap<K, V>::operator[] (const K& key)
{
    int bucketNum = mapHash(key) % table.size();
    for (int i = 0; i < table.at(bucketNum).size(); i++) {
        if (table.at(bucketNum).at(i).first == key) {
            return table.at(bucketNum).at(i).second;
        }
    }

    put(key, V());
    // Have to reassign a new value to bucketNum in case the table is resized and rehashed.
    bucketNum = mapHash(key) % table.size();
    return table.at(bucketNum).at(table.at(bucketNum).size() - 1).second;
}

/*also lets us access values in the map like std::map type but should throw
a std::out_of_range exception if the key isn't already in the map.*/

template <class K, class V>
V& HashMap<K, V>::at(const K& key)
{
	int bucketNum = mapHash(key) % table.size();
    for (int i = 0; i < table.at(bucketNum).size(); i++) {
        if (table.at(bucketNum).at(i).first == key) {
            return table.at(bucketNum).at(i).second;
        }
    }

	throw std::out_of_range("Key not found in the map.");
}

/*if the key is in the map, true should be returned.
if the key doesn't exist in the map, false should be returned.*/

template <class K, class V>
bool HashMap<K, V>::contains(const K& key) const
{
    int bucketNum = mapHash(key) % table.size();
    for (int i = 0; i < table.at(bucketNum).size(); i++) {
        if (table.at(bucketNum).at(i).first == key) {
            return true;
        }
    }
    return false;
}

/* gets all of the keys in the map and stores them in a vector*/

template <class K, class V>
std::vector<K> HashMap<K, V>::keys() const
{
	std::vector<K> all_keys;

	for(const auto& bucket : table)
	{
		for(const auto& elem : bucket)
		{
			all_keys.push_back(elem.first);
		}
	}

	return all_keys;
}

/* returns all of the values that match key inside of a vector
if the key doesn't exist in the map, an empty vector should be
returned in a HashMap there should at most be 1 element in the
resulting vector.*/

template <class K, class V>
std::vector<V> HashMap<K, V>::get(const K& key) const
{
    std::vector<V> values;
    int bucketNum = mapHash(key) % table.size();
    for (int i = 0; i < table.at(bucketNum).size(); i++) {
        if (table.at(bucketNum).at(i).first == key) {
            values.push_back(table.at(bucketNum).at(i).second);
        }
    }
    return values;
}

/*inserts the key/value pair into the map if the key/value
pair is already in the map, the value is updated but the size
of the table should not change. if inserting the element increases
the load factor beyond (>=) max_load_factor, the table should be
rehashed. The table size should increase to 2*original size + 1.*/

template <class K, class V>
void HashMap<K, V>::put(const K& key, const V& value)
{
    int bucketNum = mapHash(key) % table.size();
    int keyIndex = -1;
    for (int i = 0; i < table.at(bucketNum).size(); i++) {
        if (table.at(bucketNum).at(i).first == key) {
            keyIndex = i;
        }
    }
    if (keyIndex == -1) {
        table.at(bucketNum).push_back(std::make_pair(key, value));
        table_size += 1;
        if ((double)table_size / (double)table.size() >= max_load_factor) {
            rehash(2 * table.size() + 1);
        }
    }
    else {
        table.at(bucketNum).at(keyIndex).second = value;
    }
}

/*erases the value associated with key returns the true if
the method found the element and erased it if the key doesn't
exist in the map, or the map is empty false should be returned
table_size should be updated if an element is removed.*/

template <class K, class V>
bool HashMap<K, V>::erase(const K& key)
{
    int bucketNum = mapHash(key) % table.size();
    for (int i = 0; i < table.at(bucketNum).size(); i++) {
        if (table.at(bucketNum).at(i).first == key) {
            table.at(bucketNum).erase(table.at(bucketNum).begin() + i);
            table_size -= 1;
            return true;
        }
    }
    return false;
}

/*Allows us to print out a HashMap<K, V> using <<i.e. cout << hm; You shouldn't modify this function.*/

template <class K, class V>
std::ostream& operator<< (std::ostream& stream,  const HashMap<K, V>& hm)
{
	for(int b = 0; b < hm.table.size(); b++)
	{
		if(hm.table.at(b).size() == 0)
		{
			continue;
		}

		stream << "Bucket " << b << " contains: " << std::endl;


		for(const auto & p : hm.table.at(b))
		{
			stream << "\t" << p.first << " : ";
			stream << p.second << std::endl;
		}
	}


	return stream;
}

#endif
