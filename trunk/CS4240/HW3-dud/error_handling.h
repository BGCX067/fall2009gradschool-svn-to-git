
#ifndef ERROR_H
#define ERROR_H

#include <iostream>

#define EXIT_WITH_ERROR(msg) \
	std::cout << "(" << __FILE__ << ":" << __LINE__ << ")" << " ERROR: " << msg << std::endl; \
	exit(1); \


#endif
