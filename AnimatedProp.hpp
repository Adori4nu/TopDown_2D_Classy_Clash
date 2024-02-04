#pragma once

#include "Prop.hpp"

class AnimatedProp : public Prop
{
public:
    // TODO: FIX constructor
    AnimatedProp(ObjectType type
                , const Vector2& world_position
                , int texture
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
};