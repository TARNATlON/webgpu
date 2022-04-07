#include "GPUSampler.h"
#include "GPUDevice.h"

#include "DescriptorDecoder.h"

GPUSampler::GPUSampler(const Napi::CallbackInfo& info) : Napi::ObjectWrap<GPUSampler>(info) {
  Napi::Env env = info.Env();

  this->device.Reset(info[0].As<Napi::Object>(), 1);
  GPUDevice* device = Napi::ObjectWrap<GPUDevice>::Unwrap(this->device.Value());

  auto descriptor = DescriptorDecoder::GPUSamplerDescriptor(device, info[1].As<Napi::Value>());

  this->instance = wgpuDeviceCreateSampler(device->instance, &descriptor);
}

GPUSampler::~GPUSampler() {
  this->device.Reset();
  wgpuSamplerRelease(this->instance);
}

Napi::Object GPUSampler::Initialize(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);
  Napi::Function func = DefineClass(env, "GPUSampler", {

  });
  auto &constructor = GetConstructor();
  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();
  exports.Set("GPUSampler", func);
  return exports;
}

Napi::FunctionReference &GPUSampler::GetConstructor() {
  thread_local Napi::FunctionReference constructor;
  return constructor;
}
