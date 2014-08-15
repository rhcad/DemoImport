// GlyphParser.h
//
// Created by Zhang Yungui on 14-8-15.
// Copyright (c) 2014, LGPL 2.1 license, https://github.com/touchvg/DemoImport

#ifndef __VGDEMO__GlyphParser__
#define __VGDEMO__GlyphParser__

class GlyphParser
{
public:
    static bool loadFile(const long cmdview, const char* filename);
    
private:
    GlyphParser() {}
};

#endif // __VGDEMO__GlyphParser__
