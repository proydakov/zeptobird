#include <iostream>

#include <phys/zworld.h>
#include <scene/zscene_wall_object.h>
#include <scene/zgame_logic.h>

const int WALL_WIDTH  = 10;
const int HOLE_HEIGHT = 20;
const int SCENE_SIZE  = 100;

int main()
{
    zworld world(zvec2(0, 0));

    const int hole_y = 50;
    const auto params1 = zgame_logic::create_hole_params(hole_y, HOLE_HEIGHT, SCENE_SIZE);

    zscene_wall_object wall(&world, WALL_WIDTH, params1.height1);
    wall.set_position(zvec2(0, params1.center1));

    return 0;
}
