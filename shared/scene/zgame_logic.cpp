#include "zgame_logic.h"

hole_params zgame_logic::create_hole_params(float hole_y, float hole_height, float scene_size)
{
    hole_params params;

    params.height1 = +hole_y - hole_height / 2;
    params.center1 = -scene_size / 2 + params.height1 / 2;

    params.height2 = scene_size - hole_y - hole_height / 2;
    params.center2 = scene_size / 2 - params.height2 / 2;

    return params;
}
