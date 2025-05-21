#pragma once

//#include <string>
//#include <exception>

#define FATAL_EXCEPTION(msg) throw msg;
#define ASSERT(condition) if(!(condition)) { throw "assert fail"; }
#define ASSERT(condition, msg) if(!(condition)) { throw "assert fail: " msg; }
