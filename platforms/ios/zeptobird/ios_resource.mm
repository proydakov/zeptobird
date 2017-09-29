//
//  resource.m
//  zeptobird
//
//  Created by Admin on 04.09.16.
//  Copyright © 2016 proydakov. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "ios_resource.h"

#include <fstream>
#include <iostream>

namespace {
    std::string build_file_path(const std::string& name)
    {
        NSURL *url = [[[NSFileManager defaultManager] URLsForDirectory:NSDocumentDirectory inDomains:NSUserDomainMask] lastObject];

        NSString *fn = [[NSString alloc] initWithCString:name.c_str() encoding:NSUTF8StringEncoding];
        NSString *path = [url.path stringByAppendingPathComponent:fn];

        std::string filepath = std::string([path UTF8String]);
        return filepath;
    }
}

ios_resource::~ios_resource()
{
}

std::string ios_resource::get_text_resource(const std::string& filepath) const
{
    //separate extension and filename:

    std::cout << "get_text_resource: " << filepath << std::endl;

    std::string filename = filepath.substr(filepath.find_last_of('/') + 1, filepath.length() - 1);

    std::string baseFileName = filename.substr(0, filename.find_last_of('.'));
    std::string extension = filename.substr(filename.find_last_of('.') + 1, filename.length()-1);

    NSString *fn = [[NSString alloc] initWithCString:baseFileName.c_str() encoding:NSUTF8StringEncoding];
    NSString *ext = [[NSString alloc] initWithCString:extension.c_str() encoding:NSUTF8StringEncoding];

    NSString *path = [[NSBundle mainBundle] pathForResource:fn ofType:ext];

    //load
    const char *sources = (char *)[[NSString stringWithContentsOfFile:path encoding:NSUTF8StringEncoding error:nil] UTF8String];
    const std::string resource(sources);
    return resource;
}

void ios_resource::save_text_data(const std::string& name, const std::string& data)
{
    auto filepath = build_file_path(name);
    std::cout << "save_text_data: " << filepath << std::endl;

    std::ofstream fstream(filepath);
    fstream << data;
    fstream.close();
}

std::string ios_resource::load_text_data(const std::string& name) const
{
    auto filepath = build_file_path(name);
    std::cout << "load_text_data: " << filepath << std::endl;

    std::ifstream fstream(filepath);
    std::string str((std::istreambuf_iterator<char>(fstream)), std::istreambuf_iterator<char>());
    fstream.close();

    return str;
}
