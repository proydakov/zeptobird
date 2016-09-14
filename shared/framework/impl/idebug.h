#pragma once

#include <cstdio>

class irender;

class idebug
{
public:
    virtual ~idebug();

    virtual void update(size_t ms) = 0;
    virtual void render(irender* render) = 0;
};
