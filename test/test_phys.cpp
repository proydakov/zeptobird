#include <memory>
#include <iomanip>
#include <sstream>
#include <iostream>

#include <phys/zworld.h>
#include <phys/zrect_body.h>
#include <phys/zcircle_body.h>

namespace
{

ibody* create_body(const zbody_def& def)
{
    ibody* ptr = nullptr;

    switch(def.type) {
    case zbody_def::btype::circle:
        ptr = new zcircle_body(def.radius);
        break;

    case zbody_def::btype::rect:
        ptr = new zrect_body(def.width, def.height);
        break;

    default:
        break;
    }

    return ptr;
}

}

int main()
{
    const zvec2 gravity(0, -9.8);
    zworld world(gravity);

    zbody_def def_hero;
    def_hero.type = zbody_def::btype::circle;
    def_hero.radius = 10;
    std::unique_ptr<ibody> hero( create_body( def_hero ) );
    hero->set_position(zvec2(0, 10));
    world.set_hero(hero.get());

    zbody_def def_floor;
    def_floor.type = zbody_def::btype::rect;
    def_floor.width = 100;
    def_floor.height = 0.5;
    std::unique_ptr<ibody> floor( create_body( def_floor ) );
    floor->set_position(zvec2(0, 0));
    world.add_body(floor.get());

    const size_t format_width(6);
    std::cout << std::setw(format_width) << "p0: " << hero->get_position() << std::endl;

    for(size_t i = 0; !hero->get_collided(); i++) {
        world.update(10);
        std::stringstream sstream;
        sstream << "p" << i << ": ";
        std::cout << std::setw(format_width) << sstream.str() << hero->get_position() << std::endl;
    }

    return 0;
}
