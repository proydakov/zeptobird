#include <iostream>
#include <math/zmath.h>

int main()
{
    zvec2 view{284, 160};

    zmat44 ortho = zortho(-88.75, 88.75, -50, 50, 1000, -1000);

    zmat44 inverse;
    zinvert4(ortho, inverse);

    zvec2 scene = zunproject(ortho, zvec4{0, 0, 568,  320}, view);

    std::cout << "ortho:\n" << ortho << std::endl;
    std::cout << "inverse:\n" << inverse << std::endl;
    std::cout << "scene:\n" << scene << std::endl;

    return 0;
}
