#pragma once

struct hole_params
{
    float height1;
    float center1;

    float height2;
    float center2;
};

class zscene_game_logic
{
public:
    static hole_params create_hole_params(float hole_y, float hole_height, float scene_size);
};
