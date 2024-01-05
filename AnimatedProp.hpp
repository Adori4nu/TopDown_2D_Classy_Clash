#pragma once

#include "Prop.hpp"

class AnimatedProp : public Prop
{
public:
    AnimatedProp(ObjectType type
                , const Vector2& world_position
                , Texture2D& texture
                , float sprite_scale
                , int sprite_count
                )
                : Prop(type
                    , world_position
                    , texture
                    , sprite_scale)
                    , _sprite_count(sprite_count)
                     {};
protected:

private:
    int _sprite_count{};
    Rectangle _source{};
};