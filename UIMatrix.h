/**
 * Define the User-Item Matrix
 */
#include <map>
#include <assert.h>
#include "UVector.h"

template<typename T>
class UIMatrix{
	const size_t start_i;
	const size_t start_j;
	const size_t size_n;
	typedef typename std::map<size_t, T>::const_iterator m_iter;
	std::map<size_t, T > matrixMap;

public:
	UIMatrix(const size_t& i, const size_t& j, const size_t& n): start_i(i),
		start_j(j), size_n(n) {}

	void set(const size_t& i, const size_t& j, const int& val) {
		assert(i < this->start_i + this->size_n);
		assert(j < this->start_j + this->size_n);
		assert(val != 0);
		m_iter it = this->matrixMap.find(i);
  		if (it != this->matrixMap.end()) {
    		this->matrixMap[it->first].set(j, val);
		} else {
			T v(this->start_j, this->size_n);
			v.set(j, val);
			this->matrixMap.insert(std::pair<size_t, T >(i, v));
		}
	}

	/**
	 * Requires a triple for returning 3 values 
	 * a, b, c, where 
	 * a is sum(Xi * Yi) for i in  [0, n[
	 * b = ||X|| (norm)
	 * c = ||Y|| (norm)
	 * 
	 * These are the 3 operands required for the cosine distance computation:  
	 * cos(angle) = a / b * c
	 * The caller cam slice the matrix in submatrices and run the computation
	 * in parallel, than merge (reduce) the operands and compute the distance.
	 */ 
	template <typename E>
	void getPartialOperands(const T& v, UVector<E>& res) {
		assert(this->start_j == v.getStartIndex());

		for(m_iter row = this->matrixMap.begin(); row != this->matrixMap.end(); 
			row++) 
		{
			E tmp(3);
			typename T::v_iter vj = v.begin();
			typename T::v_iter mj = row->second.begin();
			while (vj != v.end() && mj != row->second.end()) {
				// check if indeces are equals
				std::cout << "It " << mj->first << " " << vj->first;
				if (mj->first == vj->first) {
					std::cout << " -> Eq" << std::endl;
					tmp[0] += vj->second * mj->second;
					tmp[1] += pow(mj->second, 2.0);
					tmp[2] += pow(vj->second, 2.0);
					mj++;
					vj++;
				} else if (mj->first < vj->first) {
					std::cout << " -> Forward mj" << std::endl;
					tmp[1] += pow(mj->second, 2.0);
					mj++;
				} else {
					std::cout << " -> Forward vj" << std::endl;
					tmp[2] += pow(vj->second, 2.0);
					vj++;
				}
			}
			//std::cout << row->first << tmp[0] << tmp[1] << tmp[2] << std::endl;
			res.set(row->first, tmp);
		}
	} 
};
