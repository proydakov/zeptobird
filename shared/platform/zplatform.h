#pragma once

class isound;
class iresource;

class zplatform final
{
public:
    zplatform(isound* sound, iresource* resource);
    ~zplatform();

    isound* get_sound();
    iresource* get_resource();

private:
    isound*    m_sound;
    iresource* m_resource;
};
