#pragma once

#include <ctime>
#include <common/zsize.h>

class irender;

class iscene
{
public:
    virtual ~iscene();

    virtual void input() = 0;
    virtual void update(size_t ms) = 0;
    virtual void render(irender* render) const = 0;

    virtual zsize get_size() const = 0;

    virtual bool is_done() const = 0;
};
