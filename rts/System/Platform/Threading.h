/* This file is part of the Spring engine (GPL v2 or later), see LICENSE.html */

#ifndef _THREADING_H_
#define _THREADING_H_

#include <string>
#ifdef WIN32
	#include <windows.h>
#else
	#include <pthread.h>
#endif


namespace Threading {
#ifdef WIN32
	typedef HANDLE NativeThreadHandle;
#else
	typedef pthread_t NativeThreadHandle;
#endif

#ifdef WIN32
	typedef DWORD NativeThreadId;
#else
	typedef pthread_t NativeThreadId;
#endif

	NativeThreadHandle GetCurrentThread();
	NativeThreadId GetCurrentThreadId();
	bool NativeThreadIdsEqual(const NativeThreadId& thID1, const NativeThreadId& thID2);

	void SetMainThread();
	bool IsMainThread();
	bool IsMainThread(NativeThreadId threadID);

	struct Error {
		Error(const std::string& _caption, const std::string& _message, const unsigned int _flags) : caption(_caption), message(_message), flags(_flags) {};
		std::string caption;
		std::string message;
		unsigned int flags;
	};
	void SetThreadError(const Error& err);
	Error* GetThreadError();
};

#endif // _THREADING_H_
