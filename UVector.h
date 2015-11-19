/**
 * Define the User profile vector
 */
#include <map>
#include <assert.h>

template<typename T>
class UVector{
	const size_t start_j;
	const size_t size_n;
	std::map<size_t, T> vectorMap;

public:
	typedef T scalarType;
	typedef typename std::map<size_t, T>::const_iterator v_iter;

	UVector(): start_j(0), size_n(0) {};
	UVector(const size_t& startFrom, const size_t& size): start_j(startFrom), 
		size_n(size) {}

	size_t getStartIndex() const {return this->start_j;}

	v_iter begin() const {return this->vectorMap.begin();}

	v_iter end() const {return this->vectorMap.end();}

	void set(const size_t& j, const T vj) {
		assert(j < this->size_n);
		this->vectorMap.insert(std::make_pair<size_t,T>(j, vj));
	}

	T get(const size_t& j) {
		assert(j < this->size_n);
		return this->vectorMap.at(j);
	}
};
