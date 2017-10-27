/*
 * utils.h
 *
 *  Created on: 27/10/2017
 *      Author: Toshiba
 */

#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include <vector>

using namespace std;

template<class T>
unsigned int numberDifferent (const vector<T> & v1){

	vector<T> unique;

	for(int i = 0; i < v1.size(); i++){
		if(find(unique.begin(), unique.end(),v1.at(i)) == unique.end())
			unique.push_back(v1.at(i));
	}

	return unique.size();
}

#endif /* SRC_UTILS_H_ */
