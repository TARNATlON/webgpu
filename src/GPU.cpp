#include "GPU.h"
#include "GPUAdapter.h"

GPU::GPU(const Napi::CallbackInfo& info) : Napi::ObjectWrap<GPU>(info) { }
GPU::~GPU() { }

Napi::Value GPU::requestAdapter(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();
  auto deferred = Napi::Promise::Deferred::New(env);

  std::vector<napi_value> args = {};
  if (info[0].IsObject()) args.push_back(info[0].As<Napi::Value>());
  else args.push_back(env.Undefined());
  args.push_back(Napi::String::New(env, ""
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    "win32"
#elif defined(__APPLE__)
    "darwin"
#elif defined(__linux__)
    "linux"
#else
#error Platform not supported.
#endif
  ));

  deferred.Resolve(GPUAdapter::GetConstructor().New(args));

  return deferred.Promise();
}

Napi::Object GPU::Initialize(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);
  Napi::Function func = DefineClass(env, "GPU", {
    StaticMethod(
      "requestAdapter",
      &GPU::requestAdapter,
      napi_enumerable
    )
  });
  thread_local Napi::FunctionReference constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();
  exports.Set("GPU", func);
  return exports;
}
