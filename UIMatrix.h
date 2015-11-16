/**
 * Define the User-Item Matrix
 */
#include <map>
#include <assert.h>
#include "UVector.h"

class UIMatrix{
	const size_t start_i;
	const size_t start_j;
	const size_t size_n;
	typedef std::map<size_t, UVector<int> >::const_iterator iterator;
	std::map<size_t, UVector<int> > matrixMap;

public:
	UIMatrix(const size_t& i, const size_t& j, const size_t& n): start_i(i),
		start_j(j), size_n(n) {}

	void set(const size_t& i, const size_t& j, const int& val) {
		assert(i < this->start_i + this->size_n);
		assert(j < this->start_j + this->size_n);
		assert(val != 0);
		iterator it = this->matrixMap.find(i);
  		if (it != this->matrixMap.end()) {
    		this->matrixMap[it->first].set(j, val);
		} else {
			UVector<int> v(this->start_j, this->size_n);
			v.set(j, val);
			this->matrixMap.insert(std::pair<size_t, UVector<int> >(i, v));
		}
	}

	void dotProduct(const UVector<int>& v, UVector<int*>& res) {
		assert(this->start_j == v.getStartIndex());
		//assert(res);

		for(iterator row = this->matrixMap.begin(); row != this->matrixMap.end(); 
			row++) 
		{
			int* tmp = new int[3];
			tmp[0] = 0;
			tmp[1] = 0;
			tmp[2] = 0;
			UVector<int>::iterator vj = v.begin();
			UVector<int>::iterator mj = row->second.begin();
			while (vj != v.end() && mj != row->second.end()) {
				// check if indeces are equals
				if (mj->first == vj->first) {
					tmp[0] += vj->second * mj->second;
					tmp[1] += pow(mj->second, 2.0);
					tmp[2] += pow(vj->second, 2.0);
					mj++;
					vj++;
				} else if (mj->first < vj->first) {
					tmp[1] += pow(mj->second, 2.0);
					mj++;
				} else {
					tmp[2] += pow(vj->second, 2.0);
					vj++;
				}
			}
			//std::cout << row->first << tmp[0] << tmp[1] << tmp[2] << std::endl;
			res.set(row->first, tmp);
		}
	} 
};
