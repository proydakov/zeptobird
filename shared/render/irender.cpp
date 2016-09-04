#include <cassert>

#include "irender.h"

irender::irender(const iresource* resource) :
    m_resource(resource)
{
    assert(resource);
}

irender::~irender()
{
}

const iresource* irender::get_resource() const
{
    return m_resource;
}
