#include "MovieClipModifier.h"

namespace scNapi
{
    void MovieClipModifier::Initialize(Napi::Env& env, Napi::Object& exports)
    {
        Napi::Function func =
            DefineClass(env, "Shape",
                {
                    InstanceAccessor("type", &MovieClipModifier::get_Type, &MovieClipModifier::set_Type)
                });

        constructor = Napi::Persistent(func);
        constructor.SuppressDestruct();

        exports.Set("MovieClipModifier", func);
    }

    Napi::FunctionReference MovieClipModifier::constructor;
    MovieClipModifier::MovieClipModifier(const Napi::CallbackInfo& info)
        : Napi::ObjectWrap<MovieClipModifier>(info)
    {
        Utils::initializeClass(this, info);
    };

    void MovieClipModifier::set_Type(const Napi::CallbackInfo& info, const Napi::Value& value)
    {
        parent->type((sc::MovieClipModifier::Type)ToNativeValue<uint8_t>(value));
    }
    Napi::Value MovieClipModifier::get_Type(const Napi::CallbackInfo& info)
    {
        return ToJSValue(info, (uint8_t)parent->type());
    }
}