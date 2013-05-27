// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_SYSTEM_CORE_H__
#define __GEL_SYSTEM_CORE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Style/Style.h>
// - ------------------------------------------------------------------------------------------ - //
namespace System {
// - ------------------------------------------------------------------------------------------ - //
// Core Features //
extern Signal GainFocus;
extern Signal LoseFocus;

extern char BaseDir[2048];
extern char SaveDir[2048];

void Init();
void Exit();						// NOTE: This doesn't need to be called //

const char* GetUserName();
const char* GetComputerName();
const char** GetEnv();
const char* GetEnv( const char* Var );

const size_t GetMemoryUsage();
// - ------------------------------------------------------------------------------------------ - //
// Timer Specific Features //
void TimeInit();					// Called from Init() //
void TimeExit();					// Called from Exit() //

// 64bit Timer Code, figures in 1000ths of a Second //
typedef unsigned long long		tick_t;
const tick_t GetTick();
const int GetTickDiff( const tick_t Start, const tick_t End );
// - ------------------------------------------------------------------------------------------ - //
// Graphics Specific Features //
void GraphicsInit();				// Called from Init() //
void GraphicsExit();				// Called from Exit() //

enum eGPU {
	GPU_NONE = 0,					// No GPU, or Not Applicable //
	GPU_UNKNOWN,
	
	GPU_INTEL,						// GMA/GMA HD //
	GPU_NVIDIA,						// GeForce/Quadro/Tegra //
	GPU_ATI,						// Radeon/FireGL //
	GPU_AMD = GPU_ATI,				// Radeon/FireGL //
	GPU_POWERVR,					// PowerVR/IMG //
	GPU_QUALCOMM,					// Adreno //
	GPU_ARM, 						// Mali //
	GPU_VIVANTE,					// GC //
	GPU_HISILICON,					// Immersion //
	GPU_BROADCOM,					// VideoCore //
	GPU_ZIILABS,					// ZMS //
	GPU_AGC,						// S //
};

extern eGPU GPUVendor;
// - ------------------------------------------------------------------------------------------ - //
}; // namespace System //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_SYSTEM_CORE_H__ //
// - ------------------------------------------------------------------------------------------ - //
