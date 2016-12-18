[![Build Status](https://travis-ci.org/joshpeterson/layout.svg?branch=master)](https://travis-ci.org/joshpeterson/layout)

# Layout

Determine the layout of C and C++ types, including their size, and the size,
offset, and padding of each field in the type.

The `layout` utility uses libclang to generate a C or C++ file with calls to
`sizeof` and `offsetof` that can be used with a specific compiler to understand the
layout of a given type.o

## Example

Suppose we have the following C++ struct defined in a file named `test.cpp`:

```
struct Type;
struct String;
struct Method;
struct Array;

struct EventInfo
{
  Type* declaringType;
  Type* reflectedType;
  String* name;
  Method* addMethod;
  Method* removeMethod;
  Method* raiseMethod;
  int eventAttributes;
  Array* otherMethods;
};
```

Then we can run `layout` like this:

```
$ layout test.cpp | g++ -xc++ -;./a.out
EventInfo (64 bytes):
          Field |     Type | Offset | Size | Padding
  declaringType |   Type * |      0 |    8 |       0
  reflectedType |   Type * |      8 |    8 |       0
           name | String * |     16 |    8 |       0
      addMethod | Method * |     24 |    8 |       0
   removeMethod | Method * |     32 |    8 |       0
    raiseMethod | Method * |     40 |    8 |       0
eventAttributes |      int |     48 |    4 |       4
   otherMethods |  Array * |     56 |    8 |       0
```

## Building

The `layout` utility depends on libclang.

### Linux

```
$ sudo apt-get install -y libclang-3.8-dev
$ ./build.sh
```

### macOS

```
$ brew install llvm38
$ /build.sh
```

## License

This source code is licensed under the [MIT License](http://opensource.org/licenses/MIT).
