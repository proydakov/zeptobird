#pragma once

#include <memory>
#include <framework/impl/idebug.h>

class znodebug : public idebug
{
public:
    znodebug();
    ~znodebug() override;

    void update(ztime ms) override;
    void render(irender& render) override;
};
