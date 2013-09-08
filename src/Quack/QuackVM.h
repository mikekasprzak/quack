// - ------------------------------------------------------------------------------------------ - //
#ifndef __QUACK_QUACKVM_H__
#define __QUACK_QUACKVM_H__
// - ------------------------------------------------------------------------------------------ - //
extern HSQUIRRELVM vm;
// - ------------------------------------------------------------------------------------------ - //
void QuackVMInit();
void QuackVMExit(); // Queued for atexit //

bool QuackVMCallSetup(); // Called the very first time only //

bool QuackVMCallInit();
bool QuackVMCallExit();
bool QuackVMCallStep();
bool QuackVMCallDraw();

bool QuackVMCallGainFocus();
bool QuackVMCallLoseFocus();

bool QuackVMCallRequestExit();
// - ------------------------------------------------------------------------------------------ - //
#endif // __QUACK_QUACKVM_H__ //
// - ------------------------------------------------------------------------------------------ - //
