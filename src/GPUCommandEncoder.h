#ifndef __GPU_COMMAND_ENCODER_H__
#define __GPU_COMMAND_ENCODER_H__

#include "Base.h"

class GPUCommandEncoder : public Napi::ObjectWrap<GPUCommandEncoder> {

  public:

    static Napi::Object Initialize(Napi::Env env, Napi::Object exports);
    static Napi::FunctionReference &GetConstructor();

    GPUCommandEncoder(const Napi::CallbackInfo &info);
    ~GPUCommandEncoder();

    Napi::Value beginRenderPass(const Napi::CallbackInfo &info);
    Napi::Value beginComputePass(const Napi::CallbackInfo &info);
#if 0
    Napi::Value beginRayTracingPass(const Napi::CallbackInfo &info);

    Napi::Value buildRayTracingAccelerationContainer(const Napi::CallbackInfo &info);
    Napi::Value copyRayTracingAccelerationContainer(const Napi::CallbackInfo &info);
    Napi::Value updateRayTracingAccelerationContainer(const Napi::CallbackInfo &info);
#endif

    Napi::Value copyBufferToBuffer(const Napi::CallbackInfo &info);
    Napi::Value copyBufferToTexture(const Napi::CallbackInfo &info);
    Napi::Value copyTextureToBuffer(const Napi::CallbackInfo &info);
    Napi::Value copyTextureToTexture(const Napi::CallbackInfo &info);
    Napi::Value copyImageBitmapToTexture(const Napi::CallbackInfo &info);

    Napi::Value pushDebugGroup(const Napi::CallbackInfo &info);
    Napi::Value popDebugGroup(const Napi::CallbackInfo &info);
    Napi::Value insertDebugMarker(const Napi::CallbackInfo &info);

    Napi::Value finish(const Napi::CallbackInfo &info);

    Napi::ObjectReference device;

    WGPUCommandEncoder instance;
  private:

};

#endif
