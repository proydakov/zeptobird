#pragma once

#include <ctime>
#include <common/zsize.h>
#include <common/ztime.h>

class irender;

class iscene
{
public:
    virtual ~iscene();

    virtual void input() = 0;
    virtual void update(ztime ms) = 0;
    virtual void render(irender* render) const = 0;

    virtual zsize get_size() const = 0;

    virtual bool is_done() const = 0;
};
