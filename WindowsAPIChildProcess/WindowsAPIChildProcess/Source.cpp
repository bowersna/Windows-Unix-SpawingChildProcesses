#include <windows.h>
#include <iostream>

using namespace std;

// start cmd.exe as a console process
//
int main(int argc, char *argv[], char **env)
{
	// *** *** set parameters for process creation *** ***
	//
	// supporting documentation:
	//    security attributes block:   https://msdn.microsoft.com/en-us/library/windows/desktop/aa379560(v=vs.85).aspx
	//    process creation flags:      https://msdn.microsoft.com/en-us/library/windows/desktop/ms684863(v=vs.85).aspx
	//    startup info block:          https://msdn.microsoft.com/en-us/library/windows/desktop/ms686331(v=vs.85).aspx
	//    process information block:   https://msdn.microsoft.com/en-us/library/windows/desktop/ms684873(v=vs.85).aspx
	//
	LPCTSTR applicationName = NULL;                     // module name; NULL => take module name from command line to execute
	LPTSTR  commandLine = "cmd /c dir &pause";          // command line to execute
	LPSECURITY_ATTRIBUTES processSecurityAttrs = NULL;  // security descriptor for child process; NULL => child doesn't inherit handle for parent process
	LPSECURITY_ATTRIBUTES threadSecurityAttrs = NULL;   // security descriptor for child process main thread; NULL => child doesn't inherit handle for parent process's main thread
	BOOL inheritHandles = FALSE;                        // false => child doesn't inherit parent prorcess handles
	DWORD creationFlags = CREATE_NEW_CONSOLE;           // process creation flags: control a process's creation modes and priority
	LPVOID  environmentBlock = NULL;                    // pointer to environment block; NULL => use parent process's environment block
	LPCTSTR currentDirectory = NULL;                 // pointer to initial current directory; NULL => use parent process's current directory
	STARTUPINFO si{};                                   // Specifies the window station, desktop, standard handles, and appearance of a process's main window at creation time." (MSDN)
	si.cb = sizeof(si);                                 // size of a startupinfo structure - must be null
	PROCESS_INFORMATION pi{};                           // "[Returns] information about a newly created process and its primary thread."  (MSDN)

	//display proper error message if invalid number of command line arguments
	int halt;
	if (argc != 2)
	{
		cerr << "   | Invalid Number of Command Line Arguments |\n  -- Please pass one argument to this program --\n" 
			 << " *** Please enter a DIGIT to terminate and re-run *** " << endl;
	
		cout << endl;
		cin >> halt;
		exit(2);
	}

	//set the current directory to the argument passed via command line
	currentDirectory = argv[1];

	// *** *** create the process *** ***
	//
	// CreateProcess:  create a child process;  see https://msdn.microsoft.com/en-us/library/windows/desktop/ms682512(v=vs.85).aspx
	// 
	BOOL processStatus = CreateProcess(applicationName, commandLine, processSecurityAttrs, threadSecurityAttrs, inheritHandles, creationFlags, environmentBlock, currentDirectory, &si, &pi);

	if (processStatus != true) {
		// retrieve and show the process's error code; see https://msdn.microsoft.com/en-us/library/windows/desktop/ms679360%28v=vs.85%29.aspx
		cout << "CreateProcess failed: error code " << GetLastError() << endl;
		// use non-zero value to signal failure to command environment; see https://msdn.microsoft.com/en-us/library/windows/desktop/ms682658(v=vs.85).aspx
		ExitProcess(1);
	}

	// *** *** Process created; ensure child process graceful termination *** ***

	cout << "Process " << pi.hProcess << " created" << endl;

	// WaitForSingleObject:  Wait until child process exits;  see https://msdn.microsoft.com/en-us/library/windows/desktop/ms687032(v=vs.85).aspx
	//
	WaitForSingleObject(pi.hProcess, INFINITE);

	// GetExitCodeProcess:  Get exit status; see  https://msdn.microsoft.com/en-us/library/windows/desktop/ms687032(v=vs.85).aspx
	//
	DWORD exitStatus;
	GetExitCodeProcess(pi.hProcess, &exitStatus);
	cout << "final status for process " << pi.hProcess << ": " << exitStatus << endl;

	// CloseHandle:  close handle on system resource;  see https://msdn.microsoft.com/en-us/library/windows/desktop/ms724211%28v=vs.85%29.aspx
	//
	CloseHandle(pi.hProcess);    // close child process handle
	CloseHandle(pi.hThread);     // close child thread handle
	ExitProcess(0);
}