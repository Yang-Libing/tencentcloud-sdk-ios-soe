//
//  PrivateInfo.m
//  TAIDemo
//
//  Created by kennethmiao on 2019/2/26.
//  Copyright © 2019年 kennethmiao. All rights reserved.
//

#import "PrivateInfo.h"

@implementation PrivateInfo

+ (instancetype)shareInstance
{
    static PrivateInfo *instance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
//        自行传入appId, secretId, secretKey参数
        instance = [[PrivateInfo alloc] init];
        instance.appId = @"1317592671";
        instance.secretId = @"AKIDc87Hc7wFPrmOYopiF8VBg7YZnQz0LYgRE4WOse3-fQy6FlqeAK-2YSsAhhRTTMzM";
        instance.secretKey = @"TZLKhg7coMaENFYO78WBxo5vpDsy/sVDx85Rf7z1N8M=";
        instance.token = @"4swZfTw5ILo1idZ5uKP7j2p7AJ1nlWhae5eff5137947773a1e987d873ded3c44gLvxjGgsBtDwXzvzrWm7srDAApwOzqzFFmEPxvwm4ZgXLfUdTivteHNjf63gypv6Dn8Isibc5M1OaWJCfTak22k0fHN_HQuG49cWktqXWLsbzfZin9L4B2cCcjFYxzekotuF0eudsrCNT0Bicipd5SXIuZEPLqdepTqIwprxDYpHWT-87wKOjUmuDXOuYZzpbK47Ll_XAa3am2z5z7C_9zGsv59HbDqDyZqBLjEWSKLUa20JEoL_w4uWSJZffc_O2HGDLnXAZiODph0T0OboRMwBok1AaI5liYyXdbWiMXCv80irsdtbACScV2vMw_t1mHaLGlkElYH4j3BRAuAYuw";
        instance.soeAppId = @"";
        instance.hcmAppId = @"";
    });
    return instance;
}
@end
