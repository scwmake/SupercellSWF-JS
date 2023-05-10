#pragma once

#include <SupercellFlash.h>
#include <napi.h>

#include "Utils/Utils.h"
#include "Utils/LinkedObject.h"
#include "Utils/Macros.h"

#include "MovieClipFrameElement.hpp"
#include "DisplayObjectInstance.hpp"
#include "MovieClipFrame.hpp"

using namespace node_binding;

namespace scNapi
{
    class MovieClip : public Napi::ObjectWrap<MovieClip>, public LinkedObject<sc::MovieClip>
    {
    public:
        inline static Napi::FunctionReference constructor;

        inline static void Initialize(Napi::Env& env, Napi::Object& target)
        {
            Napi::Function func =
                DefineClass(env, "MovieClip",
                    {
                        PROPERTY_ACCESSOR(scNapi::MovieClip, id),
                        PROPERTY_ACCESSOR(scNapi::MovieClip, frameRate),
                        PROPERTY_ACCESSOR(scNapi::MovieClip, matrixBankIndex),
                        PROPERTY_ACCESSOR(scNapi::MovieClip, unknownFlag),
                        PROPERTY_ACCESSOR(scNapi::MovieClip, scalingGrid),
                        VECTOR_ACCESSOR(MovieClip, frameElements),
                        VECTOR_ACCESSOR(MovieClip, instances),
                        VECTOR_ACCESSOR(MovieClip, frames)

                    });

            constructor = Napi::Persistent(func);
            constructor.SuppressDestruct();

            target.Set("MovieClip", func);
        }

        MovieClip(const Napi::CallbackInfo& info) : Napi::ObjectWrap<MovieClip>(info)
        {
            INITIALIZER(MovieClip);
        };

        void fromObject(const Napi::CallbackInfo& info, Napi::Object object) override
        {
            PROPERTY_INIT(id);
            PROPERTY_INIT(frameRate);
            PROPERTY_INIT(matrixBankIndex);
            PROPERTY_INIT(unknownFlag);
            PROPERTY_INIT(scalingGrid);

            VECTOR_PROPERTY_INIT(frameElements, MovieClipFrameElement);
            VECTOR_PROPERTY_INIT(instances, DisplayObjectInstance);
            VECTOR_PROPERTY_INIT(frames, MovieClipFrame);
        }

    private:
        PROPERTY(id)
            parent->id(ToNativeValue<uint16_t>(value));
        PROPERTY_GET(id)
            return ToJSValue(info, parent->id());
        PROPERTY_END;


        PROPERTY(unknownFlag)
            parent->unknownFlag(ToNativeValue<bool>(value));
        PROPERTY_GET(unknownFlag)
            return ToJSValue(info, parent->unknownFlag());
        PROPERTY_END;


        PROPERTY(frameRate)
            parent->frameRate(ToNativeValue<uint8_t>(value));
        PROPERTY_GET(frameRate)
            return ToJSValue(info, parent->frameRate());
        PROPERTY_END;


        PROPERTY(matrixBankIndex)
            parent->matrixBankIndex(ToNativeValue<uint8_t>(value));
        PROPERTY_GET(matrixBankIndex)
            return ToJSValue(info, parent->matrixBankIndex());
        PROPERTY_END;


        VECTOR(frameElements, MovieClipFrameElement);
        VECTOR(instances, DisplayObjectInstance);
        VECTOR(frames, MovieClipFrame);

        PROPERTY(scalingGrid)
            if (value.IsUndefined())
            {
                parent->scalingGrid(nullptr);
            }

        Napi::Object grid = value.As<Napi::Object>();
        sc::ScalingGrid* nativeGrid = new sc::ScalingGrid();

        if (grid.Has("x"))
        {
            TOSTRING("coc");
            nativeGrid->x = ToNativeValue<float>(grid.Get("x"));
        }

        if (grid.Has("y"))
        {
            nativeGrid->y = ToNativeValue<float>(grid.Get("y"));
        }

        if (grid.Has("width"))
        {
            nativeGrid->width = ToNativeValue<float>(grid.Get("width"));
        }

        if (grid.Has("height"))
        {
            nativeGrid->height = ToNativeValue<float>(grid.Get("height"));
        }

        parent->scalingGrid(nativeGrid);
        PROPERTY_GET(scalingGrid)
            if (parent->scalingGrid() == nullptr)
            {
                return info.Env().Undefined();
            }

        Napi::Object grid = Napi::Object::New(info.Env());
        sc::ScalingGrid* nativeGrid = parent->scalingGrid();

        grid.Set("x", ToJSValue(info, nativeGrid->x));
        grid.Set("y", ToJSValue(info, nativeGrid->y));
        grid.Set("width", ToJSValue(info, nativeGrid->width));
        grid.Set("height", nativeGrid->height);

        return grid;
        PROPERTY_END

    };
}
