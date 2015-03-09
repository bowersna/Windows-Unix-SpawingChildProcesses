#include "fork_exec_wait_error_codes.h"
#include <signal.h>

// associative arrays that map error codes for fork, exec, and wait to descriptive strings
//
map<int, string> forkErrorCodes {
    { EAGAIN, "(1) can't allocate sufficient memory for child, or (2) child process imit reached" },
    { ENOMEM, "insufficient kernel memory" }
};
map<int, string> execErrorCodes {
    { E2BIG,        "The total number of bytes in the environment (envp) and argument list (argv) is too large" },
    { EACCES,       "Search permission is denied, file isn't a regular file, or execute permission denied" },
    { EFAULT,       "The named file's filename points outside user's accessible address space" },
    { EINVAL,       "An ELF executable tried to name more than one interpreter" },
    { EIO,          "An I/O error occurred" },
    { EISDIR,       "An ELF interpreter was a directory" },
    { ELIBBAD,      "An ELF interpreter was not in a recognized format" },
    { ELOOP,        "Too many symbolic links were encountered in resolving filename or the name of a script or ELF interpreter" },
    { EMFILE,       "The process has the maximum number of files open" },
    { ENAMETOOLONG, "The named file's filename is too long", },
    { ENFILE,       "The system limit on the total number of open files has been reached" },
    { ENOENT,       "The named file or a script or ELF interpreter does not exist, or a supporting shared library can't be found" },
    { ENOEXEC,      "An  executable is in an unrecognized format, is for the wrong architecture, or has some other format error" },
    { ENOMEM,       "Insufficient kernel memory" },
    { ENOTDIR,      "A component of the path prefix of the named file or a script or ELF interpreter is not a directory" },
    { EPERM,        "The file system is mounted nosuid, the user isn't superuser, and the file has the set-user-ID or set-group-ID bit set" },
    { ETXTBSY,      "The executable was open for writing by one or more processes" }
};
map<int, string> sigactionErrorCodes {
	{ EFAULT, 		"Parent or child process point to memory which is not a valid part of the process address space" },
	{ EINVAL, 		"Invalid signal was specified" }
};
