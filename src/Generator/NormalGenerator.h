/*
 * NormalGenerator.h
 *
 *  Created on: May 30, 2014
 *      Author: Adam Kosiorek Kosiorek
 */

#ifndef NORMALGENERATOR_H_
#define NORMALGENERATOR_H_

#include <vector>

class NormalGenerator {
public:
	
	static std::vector<float> gen(const std::vector<float>& vertices);
};

#endif /* NORMALGENERATOR_H_ */
