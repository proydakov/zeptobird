#pragma once

#include <vector>
#include <platform/iresource.h>

class linux_resource : public iresource
{
public:
    linux_resource();
    ~linux_resource() override;

    std::string get_text_resource(const std::string& name) const override;

private:
    std::vector<std::string> m_folders;
};
