//
//  WXApiManager.m
//  SDKSample
//
//  Created by Jeason on 16/07/2015.
//
//

#import "baidu/ios/BDApiManager.h"
#include "userdata/UserData.h"

BMKLocationManager* _locationManager;

@implementation BDApiManager

#pragma mark - LifeCycle
+(instancetype)sharedManager {
    static dispatch_once_t onceToken;
    static BDApiManager *instance;
    dispatch_once(&onceToken, ^{
        instance = [[BDApiManager alloc] init];
    });
    return instance;
}

- (void)dealloc {
    [super dealloc];
}

-(void)checkPermisionWithKey{
     [[BMKLocationAuth sharedInstance] checkPermisionWithKey:@"tkBRUjtTGkjPD9nYCLGTAgwzyC0HppMb" authDelegate:self];
}

- (void)onCheckPermissionState:(BMKLocationAuthErrorCode)iError
{
     NSLog(@"location auth onGetPermissionState %ld",(long)iError);
    if((int)iError == 0){
        [_locationManager requestLocationWithReGeocode:TRUE withNetworkState:TRUE completionBlock:self.completionBlock];
    }
}

-(void)initLocation
{
    _locationManager = [[BMKLocationManager alloc] init];
    _locationManager.delegate = self;
    _locationManager.coordinateType = BMKLocationCoordinateTypeBMK09LL;
    _locationManager.distanceFilter = kCLDistanceFilterNone;
    _locationManager.desiredAccuracy = kCLLocationAccuracyBest;
    _locationManager.activityType = CLActivityTypeAutomotiveNavigation;
    _locationManager.pausesLocationUpdatesAutomatically = NO;
    _locationManager.allowsBackgroundLocationUpdates = YES;
    _locationManager.locationTimeout = 10;
    _locationManager.reGeocodeTimeout = 10;
    
}

-(void)initBlock
{
    self.completionBlock = ^(BMKLocation *location, BMKLocationNetworkState state, NSError *error)
    {
        if (error)
        {
            NSLog(@"aa locError:{%ld - %@};", (long)error.code, error.localizedDescription);
        }
        
        if (location.location) {
            NSString *longitude = [NSString stringWithFormat:@"%f", location.location.coordinate.longitude];
            NSString *latitude = [NSString stringWithFormat:@"%f", location.location.coordinate.latitude];
            NSLog(@"longitude = %@",longitude);
            NSLog(@"latitude = %@",latitude);
            UserData::getInstance()->setLongitude(std::string([longitude UTF8String]));
            UserData::getInstance()->setLatitude(std::string([latitude UTF8String]));
        }
        if (location.rgcData) {
            NSLog(@"rgc = %@",[location.rgcData description]);
        }

        NSLog(@"aa netstate = %d",state);
    };
}

- (void)getMapLoction{
    [_locationManager requestLocationWithReGeocode:TRUE withNetworkState:TRUE completionBlock:self.completionBlock];
}

@end
