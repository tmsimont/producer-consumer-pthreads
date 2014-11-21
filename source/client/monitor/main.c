#include <windows.h>
#include <stdio.h>
#include <tchar.h>


STARTUPINFO si[5];
PROCESS_INFORMATION pi[5];
int procIndex = 0;
void monitor_new_process();
void monitor_shutdown();

/**
 *
 * @see: http://msdn.microsoft.com/en-us/library/windows/desktop/ms682512(v=vs.85).aspx
 */
void _tmain(int argc, TCHAR *argv[]) {
	monitor_new_process();
	monitor_new_process();
	monitor_new_process();
	monitor_shutdown();
}

void monitor_new_process() {
	ZeroMemory(&si[procIndex], sizeof(si[procIndex]));
	si[procIndex].cb = sizeof(si[procIndex]);
	ZeroMemory(&pi[procIndex], sizeof(pi[procIndex]));

	// Start the child process. 
	if (!CreateProcess(NULL,   // No module name (use command line)
		"consumer",        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si[procIndex],            // Pointer to STARTUPINFO structure
		&pi[procIndex])           // Pointer to PROCESS_INFORMATION structure
		)
	{
		printf("CreateProcess failed (%d).\n", GetLastError());
		return;
	}

	procIndex++;
}

void monitor_shutdown() {
	while (procIndex >= 0){
		// Wait until child process exits.
		WaitForSingleObject(pi[procIndex].hProcess, INFINITE);

		// Close process and thread handles. 
		CloseHandle(pi[procIndex].hProcess);
		CloseHandle(pi[procIndex].hThread);
		procIndex--;
	}
}
