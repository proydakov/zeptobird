#include <iostream>

#include <animation/zscale_animation.h>

int main()
{
    zscale_animation animation(2);

    const int step = 16;
    for(int i = 0; i < 1000; i += step) {
        animation.update(step);
        std::cout << "scale: " << animation.get_scale() << std::endl;
    }
}
