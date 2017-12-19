#pragma once

#ifdef __APPLE__
const char* SystemIncludeDirectoryArgument =
    "-I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/"
    "Developer/SDKs/MacOSX.sdk/usr /include";
#else
const char* SystemIncludeDirectoryArgument =
    "-I/usr/lib/llvm-5.0/lib/clang/5.0.1/include";
#endif
