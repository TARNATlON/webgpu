#include "GPUCommandBuffer.h"

GPUCommandBuffer::GPUCommandBuffer(const Napi::CallbackInfo& info) : Napi::ObjectWrap<GPUCommandBuffer>(info) {

}

GPUCommandBuffer::~GPUCommandBuffer() {
  wgpuCommandBufferRelease(this->instance);
}

Napi::Object GPUCommandBuffer::Initialize(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);
  Napi::Function func = DefineClass(env, "GPUCommandBuffer", {

  });
  auto &constructor = GetConstructor();
  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();
  exports.Set("GPUCommandBuffer", func);
  return exports;
}

Napi::FunctionReference &GPUCommandBuffer::GetConstructor() {
  thread_local Napi::FunctionReference constructor;
  return constructor;
}
