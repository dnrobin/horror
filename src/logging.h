#ifndef __MAZE_GAME_LOGGING_H__
#define __MAZE_GAME_LOGGING_H__

#define STATUS_FAILURE -1
#define STATUS_SUCCESS 0

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define __LOG(fp,fmt,...) fprintf(fp,fmt,#__VA_ARGS__)
#define PRINT(fmt,...) __LOG(stderr,KGRN fmt KNRM,__VA_ARGS__)
#define ERROR(fmt,...) __LOG(stderr,KRED fmt KNRM,__VA_ARGS__)
#define WARN(fmt,...) __LOG(stderr,KYEL fmt KNRM,__VA_ARGS__)

#define ERROR_RET(fmt,...) do {\
	ERROR(fmt,__VA_ARGS__);\
	return STATUS_FAILURE;\
} while(0);

#define FATAL_RET(fmt,...) do {\
	ERROR(fmt,__VA_ARGS__);\
	return STATUS_FAILURE;\
} while(0);

#endif