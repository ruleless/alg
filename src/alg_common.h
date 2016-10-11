#ifndef __ALG_COMMON_H__
#define __ALG_COMMON_H__

/******************************************************************/
/* common include */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <assert.h>

/* windows include */
#if defined( __WIN32__ ) || defined( WIN32 ) || defined( _WIN32 )

# ifndef WINVER
#  define WINVER 0x0501
# endif
# ifndef _WIN32_WINNT
#  define _WIN32_WINNT 0x0501
# endif
# ifndef _WIN32_WINDOWS
#  define _WIN32_WINDOWS 0x0410
# endif

# pragma warning(disable:4996)
# pragma warning(disable:4819)
# pragma warning(disable:4049)
# pragma warning(disable:4217)

# include <io.h>
# include <time.h> 
// # define FD_SETSIZE 1024
# ifndef WIN32_LEAN_AND_MEAN 
#  include <winsock2.h> // 必须在windows.h之前包含， 否则网络模块编译会出错
#  include <mswsock.h> 
#  define WIN32_LEAN_AND_MEAN
# endif

# include <windows.h>
# include <process.h>

# define _SCL_SECURE_NO_WARNINGS

#else // #if defined( __WIN32__ ) || defined( WIN32 ) || defined( _WIN32 )

/* linux include */
# include <errno.h>
# include <float.h>
# include <pthread.h>	
# include <fcntl.h>
# include <unistd.h>
# include <signal.h>
# include <netdb.h>
# include <iconv.h>
# include <langinfo.h>
# include <stdint.h>
# include <signal.h>
# include <dirent.h>
# include <net/if.h>
# include <netinet/in.h>
# include <netinet/tcp.h> 
# include <netinet/ip.h>
# include <arpa/inet.h>
# include <linux/types.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <sys/socket.h>
# include <sys/uio.h>
# include <sys/resource.h>
# include <linux/errqueue.h>

#endif // #if defined( __WIN32__ ) || defined( WIN32 ) || defined( _WIN32 )

#include <signal.h>

#if !defined( _WIN32 )
# include <pwd.h>
#else
# define SIGHUP	1
# define SIGINT	2
# define SIGQUIT 3
# define SIGUSR1 10
# define SIGPIPE 13
# define SIGSYS	32
#endif
/******************************************************************/

/******************************************************************/
/* 平台定义 */
#define PLATFORM_WIN32 0
#define PLATFORM_UNIX  1
#define PLATFORM_APPLE 2
#define PLATFORM_INTEL 3

#define UNIX_FLAVOUR_LINUX	1
#define UNIX_FLAVOUR_BSD	2
#define UNIX_FLAVOUR_OTHER	3
#define UNIX_FLAVOUR_OSX	4

#if defined( __WIN32__ ) || defined( WIN32 ) || defined( _WIN32 )
# define PLATFORM PLATFORM_WIN32
#elif defined( __INTEL_COMPILER )
# define PLATFORM PLATFORM_INTEL
#elif defined( __APPLE_CC__ )
# define PLATFORM PLATFORM_APPLE
#else
# define PLATFORM PLATFORM_UNIX
#endif

#if PLATFORM == PLATFORM_UNIX || PLATFORM == PLATFORM_APPLE
# ifdef HAVE_DARWIN
#  define PLATFORM_TEXT "MacOSX"
#  define UNIX_FLAVOUR UNIX_FLAVOUR_OSX
# else
#  ifdef USE_KQUEUE
#   define PLATFORM_TEXT "FreeBSD"
#   define UNIX_FLAVOUR UNIX_FLAVOUR_BSD
#  else
#   ifdef USE_KQUEUE_DFLY
#    define PLATFORM_TEXT "DragonFlyBSD"
#    define UNIX_FLAVOUR UNIX_FLAVOUR_BSD
#   else
#    define PLATFORM_TEXT "Linux"
#    define UNIX_FLAVOUR UNIX_FLAVOUR_LINUX
#   endif
#  endif
# endif
#elif PLATFORM == PLATFORM_WIN32
# define PLATFORM_TEXT "Win32"
#endif
/******************************************************************/

/******************************************************************/
/* 编译器定义 */
#define COMPILER_MICROSOFT 0
#define COMPILER_GNU	   1
#define COMPILER_BORLAND   2
#define COMPILER_INTEL     3
#define COMPILER_CLANG     4

#ifdef _MSC_VER
# define COMPILER COMPILER_MICROSOFT
#elif defined( __INTEL_COMPILER )
# define COMPILER COMPILER_INTEL
#elif defined( __BORLANDC__ )
# define COMPILER COMPILER_BORLAND
#elif defined( __GNUC__ )
# define COMPILER COMPILER_GNU
#elif defined( __clang__ )
# define COMPILER COMPILER_CLANG
#else
# pragma error "FATAL ERROR: Unknown compiler."
#endif
/******************************************************************/

/******************************************************************/
/* 宏定义 */
#ifndef NAME_PATH
# define NAME_PATH 255
#endif

#ifndef NAME_MAX
# define NAME_MAX 255
#endif

#ifndef MAX_NAME
# define MAX_NAME 256
#endif

#ifndef MAX_IP
# define MAX_IP 50
#endif

#ifndef MAX_BUF
# define MAX_BUF 256
#endif

#ifndef MAX_PATH
# define MAX_PATH 260
#endif

#ifndef max
# define max(a, b) ((b) > (a) ? (b) : (a))
#endif
#ifndef min
# define min(a, b) ((b) < (a) ? (b) : (a))
#endif

#ifndef container_of
# define container_of(ptr, type, member)					\
    (type *)((char *)(ptr) - (char *)&((type *)0)->member)
#endif

/* 导入导出定义 */
#if PLATFORM == PLATFORM_WIN32
# ifdef _LIB
#  define CLASS_EXPORT
#  define CLASS_IMPORT
#  define API_EXPORT
#  define API_IMPORT
#  define VAR_EXPORT
#  define VAR_IMPORT
# else
#  define CLASS_EXPORT		__declspec(dllexport)
#  define CLASS_IMPORT		__declspec(dllimport)
#  define API_EXPORT		__declspec(dllexport)
#  define API_IMPORT		__declspec(dllimport)
#  define VAR_EXPORT		__declspec(dllexport)
#  define VAR_IMPORT		__declspec(dllimport)
# endif
#else
# define CLASS_EXPORT
# define CLASS_IMPORT
# define API_EXPORT
# define API_IMPORT
# define VAR_EXPORT
# define VAR_IMPORT
#endif

#ifdef _ALG_DLL_EXPORT
# define ALG_CLASS		CLASS_EXPORT
# define ALG_API		API_EXPORT
# define ALG_VAR		VAR_EXPORT
#else
# define ALG_CLASS		CLASS_IMPORT
# define ALG_API		API_IMPORT
# define ALG_VAR		VAR_IMPORT
#endif
/******************************************************************/

/******************************************************************/
/* 类型定义 */
typedef char					mchar;
typedef wchar_t					wchar;

#ifdef _UNICODE
typedef wchar					tchar;
#else
typedef mchar					tchar;
#endif

typedef unsigned char			uchar;
typedef unsigned short			ushort;
typedef unsigned int			uint;
typedef unsigned long			ulong;

#if COMPILER != COMPILER_GNU

typedef signed __int64			int64;
typedef signed __int32			int32;
typedef signed __int16			int16;
typedef signed __int8			int8;
typedef unsigned __int64		uint64;
typedef unsigned __int32		uint32;
typedef unsigned __int16		uint16;
typedef unsigned __int8			uint8;
typedef INT_PTR					intptr;
typedef UINT_PTR        		uintptr;

#else // #if COMPILER != COMPILER_GNU

typedef int64_t					int64;
typedef int32_t					int32;
typedef int16_t					int16;
typedef int8_t					int8;
typedef uint64_t				uint64;
typedef uint32_t				uint32;
typedef uint16_t				uint16;
typedef uint8_t					uint8;
typedef uint16_t				WORD;
typedef uint32_t				DWORD;

# ifdef _LP64
typedef int64					intptr;
typedef uint64					uintptr;
# else // #ifdef LP64
typedef int32					intptr;
typedef uint32					uintptr;
# endif // #ifdef LP64

#endif // #if COMPILER != COMPILER_GNU

#if PLATFORM == PLATFORM_WIN32

# define IFNAMSIZ				16
typedef UINT_PTR				SOCKET;
# ifndef socklen_t
typedef	int						socklen_t;
# endif

typedef unsigned short			u_int16_t;
typedef unsigned long			u_int32_t;

# ifndef IFF_UP
enum
{
	IFF_UP					= 0x1,
	IFF_BROADCAST			= 0x2,
	IFF_DEBUG				= 0x4,
	IFF_LOOPBACK			= 0x8,
	IFF_POINTOPOINT			= 0x10,
	IFF_NOTRAILERS			= 0x20,
	IFF_RUNNING				= 0x40,
	IFF_NOARP				= 0x80,
	IFF_PROMISC				= 0x100,
	IFF_MULTICAST			= 0x1000
};
# endif // #ifndef IFF_UP
#else // #if PLATFORM == PLATFORM_WIN32
typedef int					SOCKET;
#endif // #if PLATFORM == PLATFORM_WIN32

/* 输出格式宏定义 */
#if COMPILER != COMPILER_GNU
# define PRI64			"lld"
# define PRIu64			"llu"
# define PRIx64			"llx"
# define PRIX64			"llX"
# define PRTime			PRI64
# define PRIzu			"lu"
# define PRIzd			"ld"
#else // #if COMPILER != COMPILER_GNU
# ifdef _LP64
#  ifndef PRI64
#   define PRI64		"ld"
#  endif
#  ifndef PRIu64
#   define PRIu64		"lu"
#  endif
#  ifndef PRIx64
#   define PRIx64		"lx"
#  endif
#  ifndef PRIX64
#   define PRIX64		"lX"
#  endif
#  ifndef PRTime
#   define PRTime		PRI64
#  endif
# else // #ifdef _LP64
#  ifndef PRI64
#   define PRI64		"lld"
#  endif
#  ifndef PRIu64
#   define PRIu64		"llu"
#  endif
#  ifndef PRIx64
#   define PRIx64		"llx"
#  endif
#  ifndef PRIX64
#   define PRIX64		"llX"
#  endif
#  ifndef PRTime
#   define PRTime		"ld"
#  endif
# endif // #ifdef _LP64
# ifndef PRIzd
#  define PRIzd			"zd"
# endif
# ifndef PRIzu
#  define PRIzu			"zu"
# endif
#endif // #if COMPILER != COMPILER_GNU
/******************************************************************/

#endif // __ALG_COMMON_H__
