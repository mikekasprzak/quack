
How to Build Android SDL Build:

1. Download Android SDK and NDK. **DO NOT INSTALL IN A FOLDER WITH SPACES!!!**
2. Download and Install Cygwin. Be sure you have GNU Make.
3. Put the latest SDL in "\jni\SDL". **WINDOWS SYMLINKS DO NOT WORK (not detected as directories)**
4. Add the following lines to the end of your ~/.bash_profile file.

ANDROID_SDK_ROOT="/cygdrive/c/Development/AndroidSDK"
ANDROID_NDK_ROOT="/cygdrive/c/Development/AndroidNDK"
PATH="${ANDROID_SDK_ROOT}/tools:${ANDROID_SDK_ROOT}/platform-tools:${ANDROID_SDK_ROOT}/build-tools/17.0.0:${ANDROID_NDK_ROOT}:${PATH}"

5. Done'ish. Now read README-android.txt
6. cd jni; ndk-build; cd ..; ant debug; ant installd

NOTES:
- libstlport_static.a has bad permissions. Right click and give yourself permission to access it.
- all mentions of the "android" command are "android.bat".
- $(SDL_PATH)/test/testgles.c needs $(SDL_PATH)/src/test/SDL_test_common.c
- use "stlfix.sh" to fix the broken libstlport_static.a
  - the originals are in \AndroidNDK\sources\cxx-stl\stlport\libs, but break after being copied.
- ndk-build V=1 for verbose output
- adb push localfile remotefile
- adb devices
- adb install
- adb logcat


TODO:
1. Create a shell script or makefile that generates the list of files to be compiled.
2. Use a makefile command to load that file/execute that command in jni/src/Android.mk under LOCAL_SRC_FILES.
3. Profit
