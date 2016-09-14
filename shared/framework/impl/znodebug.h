#pragma once

#include <memory>
#include <framework/impl/idebug.h>

class znodebug : public idebug
{
public:
    znodebug();
    ~znodebug() override;

    void update(size_t ms) override;
    void render(irender* render) override;
};
