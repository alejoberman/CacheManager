// CacheManager
//
// Copyright (c) 2012-2015 Alejo Martin Berman.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.


#import "CMCacheModel.h"
#import "CMCacheManager.h"
#import "UIApplication+CMAdditions.h"
#import "CMCacheObject.h"


@implementation CMCacheModel



- (instancetype)init
{
  return [self initWithDelegate:nil];
}

- (instancetype)initWithDelegate:(id<CMCacheManagerDelegate>)delegate
{
  if ((self = [super init])) {
    _delegate = delegate;
    _modelTypeString = NSStringFromClass([self class]);
  }
  return self;
}

- (NSString *)keyCacheModelType
{
  return self.modelTypeString;
}

- (BOOL)hasObject:(id<CMCacheObject>)cacheObject
{
  return NO;
}

- (void)saveObjectCache:(id<CMCacheObject>)cacheObject
{
  
}

- (void)updateObjectCache:(id<CMCacheObject>)cacheObject
{
  
}

- (id<CMCacheObject>)cacheObjectForObject:(id<CMCacheObject>)cacheObject
{
  return nil;
}

- (NSDictionary *)allCacheObjects
{
  return nil;
}

- (id<CMCacheObject>)cacheObjectForObjectId:(NSString *)objectId
{
  return nil;
}

- (void)removeCacheObject:(id<CMCacheObject>)cacheObject
{
  
}

- (void)synchronizeCacheModel
{
  
}

- (void)synchronizeAsyncCacheModel
{
  dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
    
    [self synchronizeCacheModel];
    
  });
}

- (void)refreshCacheModel
{
  
}

- (void)cleanCacheObject
{
  
}

- (NSString *)defaultResourcesPath
{
  return nil;
}

- (void)deleteItemResource:(NSString *)resourcePath
{
  
}

- (NSString *)pathForCacheFileSystemDirectory:(NSString *)directory
{
  /* create path to cache directory inside the application's Documents directory */
  NSString *prefixPath = [[UIApplication sharedApplication] pathAtCacheFor:directory];
  
  /* check for existence of cache directory */
  if (![[NSFileManager defaultManager] fileExistsAtPath:prefixPath]) {
    /* create a new cache directory */
    NSError *error = nil;
    [[NSFileManager defaultManager] createDirectoryAtPath:prefixPath withIntermediateDirectories:NO attributes:nil error:&error];
    if (error) {
      prefixPath = nil;
    }
  }
  return prefixPath;
}

- (void)notifyCacheUpdatesWithNotificationName:(NSString *)notificationName
{
  NSString *notifName = notificationName;
  if (!notifName) {
    notifName = kCMCacheManagerUpdateNotification;
  }
  [[NSNotificationCenter defaultCenter] postNotificationName:notifName object:self];
}


@end