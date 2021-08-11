#ifndef MAP_H
#define MAP_H

#include <vector>
#include <utility>


/* Interface (and base class) for our Map types */
/* See the other header files for more details */

template <class K, class V>
class Map
{

public:
	Map() {};
	virtual ~Map() {};

	/* Empties the map, so that its size is 0 */
	virtual void clear() = 0;
	/* returns the number of the elements (key/value pairs) in the map */
	virtual size_t size() const = 0;
	/* returns true if the map is empty (size is 0), false otherwise */
	virtual bool empty() const = 0;

	/* returns true if the map contains a mapping */
	/* for the key and returns false otherwise */
	virtual bool contains(const K& key) const = 0;

	/* gets all of the keys in the map */
	virtual std::vector<K> keys() const = 0;

	/* stores the associated values for a key in a vector. if the map */
        /* doesn't have any values for key an empty vector is returned */
	virtual std::vector<V> get(const K& key) const = 0;

	/* allows us to access values in the map like std::map type */
	/* creates a new map element if key doesn't already exist */
        virtual V& operator[] (const K& key) = 0;

	/* also lets us access values in the map like std::map type */
	/* but should throw an out_of_range exception if the key */
	/* isn't already in the map. */
        virtual V& at(const K& key) = 0;

	/* inserts the key/value pair into the map */
	virtual void put(const K& key, const V& value) = 0;

	/* erases the value associated with key */
	/* returns the true if the method found the element and erased it */
	/* if the key doesn't exist in the map, false should be returned */
	virtual bool erase(const K& key) = 0;
};


#endif

