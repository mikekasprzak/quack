
How to Build Android SDL Build:

1. Download Android SDK and NDK. **DO NOT INSTALL IN A FOLDER WITH SPACES!!!**
2. Download and Install Cygwin. Be sure you have GNU Make.
3. Put the latest SDL in "\jni\SDL". **WINDOWS SYMLINKS DO NOT WORK (not detected as directories)**
4. Add the following lines to the end of your ~/.bash_profile file.

PATH="/cygdrive/c/Development/AndroidSDK/tools:/cygdrive/c/Development/AndroidSDK/platform-tools:/cygdrive/c/Development/AndroidNDK:${PATH}"
ANDROID_SDK_ROOT="/cygdrive/c/Development/AndroidSDK"
ANDROID_NDK_ROOT="/cygdrive/c/Development/AndroidNDK"

5. Done'ish. Now read README-android.txt

NOTES:
- libstlport_static.a has bad permissions. Right click and give yourself permission to access it.
- all mentions of the "android" command are "android.bat".
- $(SDL_PATH)/test/testgles.c needs $(SDL_PATH)/src/test/SDL_test_common.c


TODO:
1. Create a shell script or makefile that generates the list of files to be compiled.
2. Use a makefile command to load that file/execute that command in jni/src/Android.mk under LOCAL_SRC_FILES.
3. Profit
