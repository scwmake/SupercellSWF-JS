#pragma once

#include <SupercellFlash.h>
#include <napi.h>

#include "Matrix2x3.h"
#include "ColorTransform.h"
#include "Utils/Utils.h"

namespace scNapi
{
    class MatrixBank: public Napi::ObjectWrap<MatrixBank>, public LinkedObject<sc::MatrixBank>
    {
    public:
        static void Initialize(Napi::Env& env, Napi::Object& target); // Export initialize in Addon
        MatrixBank(const Napi::CallbackInfo& info); // Node constructor
        static Napi::FunctionReference constructor; // C++ constrcutor to init class in Node.js

        void fromObject(Napi::Env env, Napi::Object object) override
        {
            if (object.Has("matrices"))
            {
                Napi::Object matrixVector = object.Get("matrices").ToObject();
                for (Napi::Value value : Utils::IteratorData(env, matrixVector))
                {
                    parent->matrices.push_back(*(
                        scNapi::Matrix2x3::Unwrap(
                            value.As<Napi::Object>()
                        )->get_parent())
                    );
                }
            }

            if (object.Has("colorTransforms"))
            {
                Napi::Object colorVector = object.Get("colorTransforms").ToObject();
                for (Napi::Value value : Utils::IteratorData(env, colorVector))
                {
                    parent->colorTransforms.push_back(*(
                        scNapi::ColorTransform::Unwrap(
                            value.As<Napi::Object>()
                        )->get_parent())
                    );
                }
            }

        }

    private:
        Vector<sc::Matrix2x3>* matrices = nullptr;
        Vector<sc::ColorTransform>* colorTransforms = nullptr;

        Napi::Value getMatrixIndex(const Napi::CallbackInfo& info);
        Napi::Value getColorTransformIndex(const Napi::CallbackInfo& info);

        /*
        ! Matrcies
        */
        Napi::Value get_matrix(const Napi::CallbackInfo& info);
        Napi::Value insert_matrix(const Napi::CallbackInfo& info);
        Napi::Value remove_matrix(const Napi::CallbackInfo& info);
        Napi::Value get_matrices_length(const Napi::CallbackInfo& info);
        void set_matrices_length(const Napi::CallbackInfo& info);

        /*
        ! Colors
        */
        Napi::Value get_color(const Napi::CallbackInfo& info);
        Napi::Value insert_color(const Napi::CallbackInfo& info);
        Napi::Value remove_color(const Napi::CallbackInfo& info);
        Napi::Value get_colors_length(const Napi::CallbackInfo& info);
        void set_colors_length(const Napi::CallbackInfo& info);
    };
}