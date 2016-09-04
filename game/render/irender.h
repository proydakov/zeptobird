#pragma once

class iresource;

class irender
{
public:
    virtual ~irender();

    virtual void init(const iresource* resource, int width, int height) = 0;
    virtual void deinit() = 0;

    virtual void render() = 0;

    virtual void input() = 0;
};
