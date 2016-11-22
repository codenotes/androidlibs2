#include <ros/ros.h>
#include <rosclientinterop/ROSClientInteropPrototypes.h>
#include "ROSinteropUtils.h"

#ifdef WIN32
thread_local uint8_t * msgbuf =NULL ;
#else
__thread uint8_t * msgbuf =NULL ;	
#endif