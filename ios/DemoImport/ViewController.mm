//
//  ViewController.m
//  DemoImport
//
//  Created by Zhang Yungui on 14-8-15.
//  Copyright (c) 2014, LGPL 2.1 license, https://github.com/touchvg/DemoImport
//

#import "ViewController.h"
#import "GiViewHelper.h"
#include "GlyphParser.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    GiViewHelper *hlp = [GiViewHelper sharedInstance];
    
    [hlp createGraphView:self.view.bounds
                  inView:self.view
                   flags:GIViewFlagsNoBackLayer|GIViewFlagsZoomExtent];
    
    NSString *path = [[NSBundle mainBundle] pathForResource:@"example1" ofType:@"json"];
    GlyphParser::loadFile([hlp cmdViewHandle], [path UTF8String]);
    
    hlp.command = @"select";
}

@end
