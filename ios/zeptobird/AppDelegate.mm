//
//  AppDelegate.m
//  zeptobird
//
//  Created by Evgeny Proydakov on 03.09.16.
//  Copyright © 2016 proydakov. All rights reserved.
//

#import "AppDelegate.h"

#import "GLView.h"
#import "GLViewController.h"

#include <iostream>

@implementation AppDelegate
@synthesize window, rootController;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    std::cout << "didFinishLaunchingWithOptions" << std::endl;

    [rootController initialize];
    [window setRootViewController:rootController];
    //rootController.view.frame = window.frame;
    //rootController.view.contentScaleFactor = window.contentScaleFactor;
    [window makeKeyAndVisible];

    [(GLView *)rootController.view startAnimation];

    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    std::cout << "applicationWillResignActive" << std::endl;

    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    std::cout << "applicationDidEnterBackground" << std::endl;

    [rootController pause];
    [(GLView *)rootController.view stopAnimation];

    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    std::cout << "applicationWillEnterForeground" << std::endl;

    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    std::cout << "applicationDidBecomeActive" << std::endl;

    [(GLView *)rootController.view startAnimation];

    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    std::cout << "applicationWillTerminate" << std::endl;

    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

@end
