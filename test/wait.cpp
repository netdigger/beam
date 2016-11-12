/* Copyright ©2016 All right reserved*/

#include <sys/time.h>
#include <stddef.h>

void Wait(int msec) {
	if (msec <= 0) return;
	struct timeval tval;
	tval.tv_sec = msec / 1000;
	tval.tv_usec = (msec % 1000) * 1000; 
	::select(0, NULL, NULL, NULL, &tval);
}

