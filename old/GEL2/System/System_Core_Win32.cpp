// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_WINDOWS
// - ------------------------------------------------------------------------------------------ - //
#include <windows.h>	// prerequisites, GetCurrentProcessId //
#include <psapi.h> 		// GetProcessMemoryInfo, PROCESS_MEMORY_COUNTERS //

#include <stdlib.h>		// getenv //
// - ------------------------------------------------------------------------------------------ - //
#include "System_Core.h"
#include "System_Core_Win32.h"
// - ------------------------------------------------------------------------------------------ - //
namespace System {
// - ------------------------------------------------------------------------------------------ - //
const char* GetUserName() {
	return getenv("USERNAME");
}
// - ------------------------------------------------------------------------------------------ - //
const char* GetComputerName() {
	return getenv("USERDOMAIN");
	//return getenv("COMPUTERNAME");	// All Caps //
}
// - ------------------------------------------------------------------------------------------ - //
const char** GetEnv() {
	return (const char**)_environ;
}
// - ------------------------------------------------------------------------------------------ - //
const char* GetEnv( const char* Var ) {
	return getenv( Var );
}
// - ------------------------------------------------------------------------------------------ - //
// http://msdn.microsoft.com/en-us/library/ms683219.aspx
const size_t GetMemoryUsage() {
	// http://msdn.microsoft.com/en-us/library/ms684877.aspx
	PROCESS_MEMORY_COUNTERS MemInfo;
	GetProcessMemoryInfo( GetCurrentProcess(), &MemInfo, sizeof(MemInfo) );
	return MemInfo.WorkingSetSize;
}
// - ------------------------------------------------------------------------------------------ - //
const int GetPID() {
	return GetCurrentProcessId();
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace System //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_WINDOWS //
// - ------------------------------------------------------------------------------------------ - //
