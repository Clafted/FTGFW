#ifndef COMPONENT_H
#define COMPONENT_H

#include <memory>

template <typename T>
using sPtr = std::shared_ptr<T>;

struct Component {
	bool skip = false;

	virtual ~Component() {};
};

#endif