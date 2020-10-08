#include "zplatform.h"

zplatform::zplatform(isound& sound, iresource& resource) :
    m_sound(sound),
    m_resource(resource)
{
}

zplatform::~zplatform()
{
}

isound& zplatform::get_sound()
{
    return m_sound;
}

iresource& zplatform::get_resource()
{
    return m_resource;
}
