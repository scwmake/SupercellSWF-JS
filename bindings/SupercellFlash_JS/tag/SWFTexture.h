#pragma once

#include <SupercellFlash.h>
#include <Napi.h>

#include "Utils/Utils.hpp"

namespace scNapi {
    class SWFTexture: public Napi::ObjectWrap<SWFTexture>, public ScObject<sc::SWFTexture>
    {
    public:
        static void Initialize(Napi::Env& env, Napi::Object& target); // Export initialize in Addon
        SWFTexture(const Napi::CallbackInfo& info); // Node constructor
        static Napi::FunctionReference constructor; // C++ constrcutor to init class in Node.js

        sc::SWFTexture* get_parent() override
        {
            return parent;
        };

        void set_parent(sc::SWFTexture* item) override
        {
            parent = item;
        };

        void new_parent() override
        {
            parent = new sc::SWFTexture();
        }

        void fromObject(Napi::Object object) override
        {
            
        }

    private:
        sc::SWFTexture* parent = nullptr; // Pointer to object that this class is attached to

        /* 
        ~ Static methods
         */
        static Napi::Value processLinearData(const Napi::CallbackInfo& info);

        /* 
        & Pixel format
         */

        void set_PixelFormat(const Napi::CallbackInfo& info, const Napi::Value& value);
        Napi::Value get_PixelFormat(const Napi::CallbackInfo& info);


        /* 
        & MagFilter
         */

        void set_MagFilter(const Napi::CallbackInfo& info, const Napi::Value& value);
        Napi::Value get_MagFilter(const Napi::CallbackInfo& info);

        /* 
        & MinFilter
         */

        void set_MinFilter(const Napi::CallbackInfo& info, const Napi::Value& value);
        Napi::Value get_MinFilter(const Napi::CallbackInfo& info);

        /* 
        & Width
         */

        void set_Width(const Napi::CallbackInfo& info, const Napi::Value& value);
        Napi::Value get_Width(const Napi::CallbackInfo& info);

        /* 
        & Height
         */

        void set_Height(const Napi::CallbackInfo& info, const Napi::Value& value);
        Napi::Value get_Height(const Napi::CallbackInfo& info);

        /* 
        & Downscaling
         */

        void set_Downscaling(const Napi::CallbackInfo& info, const Napi::Value& value);
        Napi::Value get_Downscaling(const Napi::CallbackInfo& info);

        /* 
        & Linear
         */

        void set_Linear(const Napi::CallbackInfo& info, const Napi::Value& value);
        Napi::Value get_Linear(const Napi::CallbackInfo& info);

        /* 
        & Data
         */

        void set_Data(const Napi::CallbackInfo& info, const Napi::Value& value);
        Napi::Value get_Data(const Napi::CallbackInfo& info);
        
    };
}