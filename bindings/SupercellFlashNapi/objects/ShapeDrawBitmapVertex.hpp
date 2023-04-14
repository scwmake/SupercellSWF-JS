#pragma once

#include <SupercellFlash.h>
#include <napi.h>

#include "Utils/Utils.h"
#include "Utils/LinkedObject.h"
#include "Utils/Macros.h"

namespace scNapi
{
    class ShapeDrawBitmapCommandVertex: public Napi::ObjectWrap<ShapeDrawBitmapCommandVertex>, public LinkedObject<sc::ShapeDrawBitmapCommandVertex>
    {
    public:
        inline static void Initialize(Napi::Env& env, Napi::Object& target)
        {
            Napi::Function func =
                DefineClass(env, "ShapeDrawBitmapCommandVertex",
                    {
                        PROPERTY_ACCESSOR(x),
                        PROPERTY_ACCESSOR(y),
                        PROPERTY_ACCESSOR(u),
                        PROPERTY_ACCESSOR(v)
                    });

            constructor = Napi::Persistent(func);
            constructor.SuppressDestruct();

            target.Set("ShapeDrawBitmapCommandVertex", func);
        }

        inline static Napi::FunctionReference constructor;

        ShapeDrawBitmapCommandVertex(const Napi::CallbackInfo& info): Napi::ObjectWrap<ShapeDrawBitmapCommandVertex>(info)
        {
            INITIALIZER(ShapeDrawBitmapCommandVertex);
        };

        void fromObject(const Napi::CallbackInfo& info, Napi::Object object) override
        {
            PROPERTY_INIT(x);
            PROPERTY_INIT(y);

            PROPERTY_INIT(u);
            PROPERTY_INIT(v);
        }

    private:
        PROPERTY(x, float);
        PROPERTY(y, float);

        PROPERTY(u, float);
        PROPERTY(v, float);
    };
}