#include "Shape.h"

using namespace node_binding;

namespace scNapi
{
    /*
    ^ Shape
    */
    /*
     * Addon initializator
     */
    void Shape::Initialize(Napi::Env& env, Napi::Object& exports)
    {
        Napi::Function func =
            DefineClass(env, "Shape",
                {
                    InstanceAccessor("id", &Shape::get_id, &Shape::set_id),

                    InstanceMethod("__get_command__", &Shape::get_command),
                    InstanceMethod("__insert_command__", &Shape::insert_command),
                    InstanceMethod("__remove_command__", &Shape::remove_command),
                    InstanceMethod("__get_commands_length__", &Shape::get_commands_length),
                    InstanceMethod("__set_commands_length__", &Shape::set_commands_length)
                });

        constructor = Napi::Persistent(func);
        constructor.SuppressDestruct();

        exports.Set("Shape", func);
    }

    Napi::FunctionReference Shape::constructor;
    Shape::Shape(const Napi::CallbackInfo& info)
        : Napi::ObjectWrap<Shape>(info)
    {
        Utils::initializeClass(this, info);

        commands = new Vector<sc::ShapeDrawBitmapCommand>(&parent->commands, &Shape::constructor);
    };

    /* 
    & Id getter
    */

    void Shape::set_id(const Napi::CallbackInfo& info, const Napi::Value& value)
    {
        parent->id(ToNativeValue<uint16_t>(value));
    }
    Napi::Value Shape::get_id(const Napi::CallbackInfo& info)
    {
        return ToJSValue(info, parent->id());
    }

    /*
    ! Bitmap getters
    */
    Napi::Value Shape::get_command(const Napi::CallbackInfo& info)
    {
        return commands->get_item(info);
    }
    Napi::Value Shape::insert_command(const Napi::CallbackInfo& info)
    {
        return commands->insert_item(info, ShapeDrawBitmapCommand::Unwrap(info[0].ToObject())->get_parent());
    };
    Napi::Value Shape::remove_command(const Napi::CallbackInfo& info)
    {
        return commands->remove_item(info);
    };
    Napi::Value Shape::get_commands_length(const Napi::CallbackInfo& info)
    {
        return commands->get_length(info);
    }
    void Shape::set_commands_length(const Napi::CallbackInfo& info)
    {
        return commands->set_length(info);
    }


    /*
    ^ ShapeDrawCommand
    */
    /*
     * Addon initializator
     */
    void ShapeDrawBitmapCommand::Initialize(Napi::Env& env, Napi::Object& exports)
    {
        Napi::Function func =
            DefineClass(env, "ShapeDrawBitmapCommand",
                {
                    InstanceAccessor("textureIndex",
                    &ShapeDrawBitmapCommand::get_TextureIndex,
                    &ShapeDrawBitmapCommand::set_TextureIndex),

                    /*
                    ! Vertices
                    */
                    InstanceMethod("__get_vertex__", &ShapeDrawBitmapCommand::get_vertex),
                    InstanceMethod("__insert_vertex__", &ShapeDrawBitmapCommand::insert_vertex),
                    InstanceMethod("__remove_vertex__", &ShapeDrawBitmapCommand::remove_vertex),
                    InstanceMethod("__get_vertices_length__", &ShapeDrawBitmapCommand::get_vertices_length),
                    InstanceMethod("__set_vertices_length__", &ShapeDrawBitmapCommand::set_vertices_length)
                });

        constructor = Napi::Persistent(func);
        constructor.SuppressDestruct();

        exports.Set("ShapeDrawBitmapCommand", func);
    }

    Napi::FunctionReference ShapeDrawBitmapCommand::constructor;
    ShapeDrawBitmapCommand::ShapeDrawBitmapCommand(const Napi::CallbackInfo& info)
        : Napi::ObjectWrap<ShapeDrawBitmapCommand>(info)
    {
        Utils::initializeClass<sc::ShapeDrawBitmapCommand>(this, info);

        vertices = new Vector<sc::ShapeDrawBitmapCommandVertex>(&parent->vertices, &ShapeDrawBitmapCommand::constructor);
    };

    /*
    & Texture index getter
    */

    void ShapeDrawBitmapCommand::set_TextureIndex(const Napi::CallbackInfo& info, const Napi::Value& value)
    {
        parent->textureIndex(ToNativeValue<uint8_t>(value));
    }
    Napi::Value ShapeDrawBitmapCommand::get_TextureIndex(const Napi::CallbackInfo& info)
    {
        return ToJSValue<uint8_t>(info, parent->textureIndex());
    }

    /*
    ! Vertices
    */
    Napi::Value ShapeDrawBitmapCommand::get_vertex(const Napi::CallbackInfo& info)
    {
        return vertices->get_item(info);
    }
    Napi::Value ShapeDrawBitmapCommand::insert_vertex(const Napi::CallbackInfo& info)
    {
        return vertices->insert_item(info, ShapeDrawBitmapCommandVertex::Unwrap(info[0].ToObject())->get_parent());
    }
    Napi::Value ShapeDrawBitmapCommand::remove_vertex(const Napi::CallbackInfo& info)
    {
        return vertices->remove_item(info);
    }
    Napi::Value ShapeDrawBitmapCommand::get_vertices_length(const Napi::CallbackInfo& info)
    {
        return vertices->get_length(info);
    }
    void ShapeDrawBitmapCommand::set_vertices_length(const Napi::CallbackInfo& info)
    {
        return vertices->set_length(info);
    }


    /*
    ^ ShapeDrawCommandVertex
    */
    /*
     * Addon initializator
     */
    void ShapeDrawBitmapCommandVertex::Initialize(Napi::Env& env, Napi::Object& exports)
    {
        Napi::Function func =
            DefineClass(env, "ShapeDrawBitmapCommandVertex",
                {
                    InstanceAccessor("x",
                    &ShapeDrawBitmapCommandVertex::get_x,
                    &ShapeDrawBitmapCommandVertex::set_x),
                    InstanceAccessor("y",
                    &ShapeDrawBitmapCommandVertex::get_y,
                    &ShapeDrawBitmapCommandVertex::set_y),
                    InstanceAccessor("u",
                    &ShapeDrawBitmapCommandVertex::get_u,
                    &ShapeDrawBitmapCommandVertex::set_u),
                    InstanceAccessor("v",
                    &ShapeDrawBitmapCommandVertex::get_v,
                    &ShapeDrawBitmapCommandVertex::set_v)
                });

        constructor = Napi::Persistent(func);
        constructor.SuppressDestruct();

        exports.Set("ShapeDrawBitmapCommandVertex", func);
    }

    Napi::FunctionReference ShapeDrawBitmapCommandVertex::constructor;
    ShapeDrawBitmapCommandVertex::ShapeDrawBitmapCommandVertex(const Napi::CallbackInfo& info)
        : Napi::ObjectWrap<ShapeDrawBitmapCommandVertex>(info)
    {
        Utils::initializeClass<sc::ShapeDrawBitmapCommandVertex>(this, info);
    };

    /*
    ! ShapeDrawCommandVertex Members
    */
    void ShapeDrawBitmapCommandVertex::set_x(const Napi::CallbackInfo& info, const Napi::Value& value)
    {
        parent->x = ToNativeValue<float>(value);
    }
    Napi::Value ShapeDrawBitmapCommandVertex::get_x(const Napi::CallbackInfo& info)
    {
        return ToJSValue(info, (parent->x));
    }
    void ShapeDrawBitmapCommandVertex::set_y(const Napi::CallbackInfo& info, const Napi::Value& value)
    {
        parent->y = ToNativeValue<float>(value);
    }
    Napi::Value ShapeDrawBitmapCommandVertex::get_y(const Napi::CallbackInfo& info)
    {
        return ToJSValue(info, (parent->y));
    }
    void ShapeDrawBitmapCommandVertex::set_u(const Napi::CallbackInfo& info, const Napi::Value& value)
    {
        parent->u = ToNativeValue<float>(value);
    }
    Napi::Value ShapeDrawBitmapCommandVertex::get_u(const Napi::CallbackInfo& info)
    {
        return ToJSValue(info, (parent->u));
    }
    void ShapeDrawBitmapCommandVertex::set_v(const Napi::CallbackInfo& info, const Napi::Value& value)
    {
        parent->v = ToNativeValue<float>(value);
    }
    Napi::Value ShapeDrawBitmapCommandVertex::get_v(const Napi::CallbackInfo& info)
    {
        return ToJSValue(info, (parent->v));
    }
}