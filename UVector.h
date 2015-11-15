/**
 * Define the User profile vector
 */
#include <map>
#include <assert.h>


class UVector{
	const size_t start_j;
	const size_t size_n;
	std::map<size_t, int> vectorMap;

public:
	typedef std::map<size_t, int>::const_iterator iterator;

	UVector(): start_j(0), size_n(0) {};
	UVector(const size_t& startFrom, const size_t& size): start_j(startFrom), 
		size_n(size) {}

	size_t getStartIndex() const {return this->start_j;}

	iterator begin() const {return this->vectorMap.begin();}

	iterator end() const {return this->vectorMap.end();}

	void set(const size_t& j, const int& vj) {
		assert(j < this->size_n);
		this->vectorMap.insert(std::pair<char,int>(j, vj));
	}

	int get(const size_t& j) {
		assert(j < this->size_n);
		return this->vectorMap.at(j);
	}	
};