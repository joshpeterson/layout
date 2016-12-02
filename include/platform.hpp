#pragma once

#ifdef __APPLE__
const char* SystemIncludeDirectoryArgument =
    "-I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/"
    "Developer/SDKs/MacOSX.sdk/usr /include";
#else
const char* SystemIncludeDirectoryArgument =
    "-I/usr/lib/llvm-3.8/lib/clang/3.8.0/include";
#endif
