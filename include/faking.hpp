#pragma once

#if ENABLE_FAKING

template <typename T>
class FakeHelper
{
public:
  FakeHelper(T* fake, T testDouble) : fake_(fake)
  {
    *fake_ = testDouble;
  }

  ~FakeHelper()
  {
    *fake_ = nullptr;
  }

private:
  T* fake_;
};

template <typename T>
FakeHelper<T> Fake(T* fake, T testDouble)
{
  return FakeHelper<T>(fake, testDouble);
}

#endif // ENABLE_FAKING

#if ENABLE_FAKING

#define FAKE(functionName, testDouble)\
  extern functionName ## Function functionName ## Fake_;\
  auto f ## functionName = Fake(&functionName ## Fake_, testDouble);

#define FAKEABLE(returnType, name, arguments)\
  returnType name arguments;\
  typedef returnType (*name ## Function) arguments;

#define DEFINE_FAKE(name)\
  name ## Function name ## Fake_ = nullptr;

#define CALL_FAKE(name, arguments)\
  if (name ## Fake_ != nullptr)\
    return name ## Fake_ arguments;

#else

#define FAKE(functionName, testDouble)

#define FAKEABLE(returnType, name, arguments)\
  returnType name arguments;

#define DEFINE_FAKE(name)

#define CALL_FAKE(name, arguments)

#endif //ENABLE_FAKING

