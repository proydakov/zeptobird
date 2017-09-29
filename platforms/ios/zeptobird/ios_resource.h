//
//  ios_resource.h
//  zeptobird
//
//  Created by Admin on 04.09.16.
//  Copyright © 2016 proydakov. All rights reserved.
//

#pragma once

#include <platform/iresource.h>

class ios_resource : public iresource
{
public:
    ~ios_resource() override;

    std::string get_text_resource(const std::string& name) const override;
    void save_text_data(const std::string& name, const std::string& data) override;
    std::string load_text_data(const std::string& name) const override;
};
