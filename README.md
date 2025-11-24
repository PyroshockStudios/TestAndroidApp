# Test android/windows App with CMake and C++

### Installing the required tools
For the native desktop app build tools you need your preferred build tool, e.g. MSVC, GCC, Clang, etc.

You also need to download [Gradle](https://gradle.org/releases/#8.6) (Do not use newer than than 8.6!) and extract it and place it in your PATH environment variable e.g. `C:\Gradle\gradle-8.6\bin`.
*Note, just download the binary-only option, it's smaller*
As well as JDK 17 ([windows MSI](https://aka.ms/download-jdk/microsoft-jdk-17.0.9-windows-x64.msi))

To configure the android tools, install the [Android NDK](https://developer.android.com/ndk/downloads) and the [Android SDK Tools](https://developer.android.com/studio) 
> Scroll all the way down and install the command line tools only! You don't need the IDE!

Make sure your android command line tools are structured like this

```text
C:\android-sdk\
└── cmdline-tools\
    └── latest\
        ├── bin\
        │   ├── sdkmanager.bat
        │   └── ...
        ├── lib\
        └── ...
```

### Environment Variables
To set up the environment, you must set the `ANDROID_NDK_HOME` to your NDK path, and the `ANDROID_HOME` to your android sdk tools path


### Configuring the SDK
After installing the SDK, run

```ps
cd C:\android-sdk\cmdline-tools\latest\bin

# Accept all licenses
.\sdkmanager.bat --licenses

# Install Platform Tools (adb), Build Tools (packaging), and the target API
.\sdkmanager.bat "platform-tools" "platforms;android-33" "build-tools;33.0.1"
```

Optional but not required, but it's useful to add the following variables to PATH to access commands such as `adb`.

```text
%ANDROID_HOME%\platform-tools
%ANDROID_HOME%\cmdline-tools\latest\bin
```

To verify that everything was correctly installed, run `adb --version` and it should show the version info!

### Building and running

Install [CMAKE](https://cmake.org/download/) and set it up, and verify that it was installed correctly.

Now you should be ready to build!

To build and run, there are 4 powershell scripts for windows, there are build scripts that set up the build environment, and the run scripts execute it. 
**Note: running on android requires you to connect your android device via USB and have USB debug trace enabled!**