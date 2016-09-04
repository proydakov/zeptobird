//
//  resource.m
//  zeptobird
//
//  Created by Admin on 04.09.16.
//  Copyright © 2016 proydakov. All rights reserved.
//

#import <Foundation/Foundation.h>
#include <OpenGLES/ES2/glext.h>
#include "ios_resource.h"

ios_resource::~ios_resource()
{
}

std::string ios_resource::load_text_resource(const std::string& filename) const
{
    //separate extension and filename:
    std::string baseFileName = filename.substr(0, filename.find_last_of('.'));
    std::string extension = filename.substr(filename.find_last_of('.') + 1, filename.length()-1);

    NSString *fn = [[NSString alloc] initWithCString:baseFileName.c_str() encoding:NSUTF8StringEncoding];
    NSString *ext = [[NSString alloc] initWithCString:extension.c_str() encoding:NSUTF8StringEncoding];

    NSString *path = [[NSBundle mainBundle] pathForResource:fn ofType:ext];

    //load
    const GLchar *sources = (GLchar *)[[NSString stringWithContentsOfFile:path encoding:NSUTF8StringEncoding error:nil] UTF8String];
    const std::string resource(sources);
    return resource;
}
