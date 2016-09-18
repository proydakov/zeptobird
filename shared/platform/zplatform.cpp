#include "zplatform.h"

zplatform::zplatform(isound* sound, iresource* resource) :
    m_sound(sound),
    m_resource(resource)
{
}

zplatform::~zplatform()
{
    m_sound = nullptr;
    m_resource = nullptr;
}

isound* zplatform::get_sound()
{
    return m_sound;
}

iresource* zplatform::get_resource()
{
    return m_resource;
}
