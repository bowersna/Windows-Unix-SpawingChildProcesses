#ifndef __FORK_EXEC_WAIT_ERROR_CODES_H__
#define __FORK_EXEC_WAIT_ERROR_CODES_H__ 

#include <map>
#include <string>
#include <errno.h>

using namespace std;

// associative arrays that map error codes for fork, exec, and wait to descriptive strings
//
extern map<int, string> forkErrorCodes;
extern map<int, string> execErrorCodes;
extern map<int, string> sigactionErrorCodes;

#endif