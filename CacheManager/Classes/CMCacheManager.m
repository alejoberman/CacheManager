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


#import "CMCacheManager.h"
#import "CMCacheModel.h"


static CMCacheManager *sharedInstance = nil;




@implementation CMCacheManager



#pragma mark - Singleton

+ (CMCacheManager *)sharedCacheManager {
  
  static dispatch_once_t pred;
  
  dispatch_once(&pred, ^{
    sharedInstance = [[CMCacheManager alloc] init];
  });
  
  return sharedInstance;
}

- (instancetype)init
{
  if ((self = [super init])) {
    _cacheModels = [[NSMutableDictionary alloc] init];
  }
  return self;
}


#pragma mark - Asynchronous Tasks


- (void)retrieveAsynchronousCacheObject:(id<CMCacheObject>)cacheObject classModel:(Class)classModel
{
  dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
    
    [self taskCacheObject:cacheObject classModel:classModel];
    
  });
}

- (void)refreshAsynchronousCacheModel:(Class)classModel
{
  dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
    
    [self taskRefreshCacheClassModel:classModel];
    
  });
}


#pragma mark - Synchronous Tasks


- (BOOL)hasObject:(id<CMCacheObject>)cacheObject classModel:(Class)classModel
{
  CMCacheModel *aModel = [self cacheModelForClassModel:classModel];
  @synchronized(aModel){
    return [aModel hasObject:cacheObject];
  }
}

- (void)saveCacheObject:(id<CMCacheObject>)cacheObject classModel:(Class)classModel
{
  CMCacheModel *aModel = [self cacheModelForClassModel:classModel];
  @synchronized(aModel){
    [aModel saveObjectCache:cacheObject];
  }
}

- (id<CMCacheObject>)cacheObjectForObject:(id<CMCacheObject>)cacheObject classModel:(Class)classModel
{
  CMCacheModel *aModel = [self cacheModelForClassModel:classModel];
  @synchronized(aModel){
    return [aModel cacheObjectForObject:cacheObject];
  }
}

- (NSDictionary *)allCacheObjectsForClassModel:(Class)classModel
{
  CMCacheModel *aModel = [self cacheModelForClassModel:classModel];
  @synchronized(aModel){
    return [aModel allCacheObjects];
  }
}

- (void)removeCacheObject:(id<CMCacheObject>)cacheObject classModel:(Class)classModel
{
  CMCacheModel *aModel = [self cacheModelForClassModel:classModel];
  @synchronized(aModel){
    [aModel removeCacheObject:cacheObject];
  }
}

- (void)synchronizeCacheModel:(Class)classModel
{
  CMCacheModel *aModel = [self cacheModelForClassModel:classModel];
  @synchronized(aModel){
    [aModel synchronizeCacheModel];
  }
}

- (void)synchronizeAsyncCacheModel:(Class)classModel
{
  dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
    
    [self synchronizeCacheModel:classModel];
    
  });
}

- (void)refreshCacheModel:(Class)classModel
{
  CMCacheModel *aModel = [self cacheModelForClassModel:classModel];
  @synchronized(aModel){
    [aModel refreshCacheModel];
  }
}

- (void)cleanCacheModel:(Class)classModel
{
  CMCacheModel *aModel = [self cacheModelForClassModel:classModel];
  @synchronized(aModel){
    [aModel cleanCacheObject];
  }
}

- (NSString *)pathForCacheFileSystemDirectoryForCacheModel:(Class)classModel
{
  CMCacheModel *aModel = [self cacheModelForClassModel:classModel];
  @synchronized(aModel){
    return [aModel defaultResourcesPath];
  }
}

- (void)deleteItemResource:(NSString *)resourcePath classModel:(Class)classModel
{
  CMCacheModel *aModel = [self cacheModelForClassModel:classModel];
  @synchronized(aModel){
    [aModel deleteItemResource:resourcePath];
  }
}

#pragma mark - Utilities

- (void)taskCacheObject:(id<CMCacheObject>)cacheObject classModel:(Class)classModel
{
  __block id cObject = [self cacheObjectForObject:cacheObject classModel:classModel];
  if ([cObject conformsToProtocol:@protocol(CMCacheObject)]) {
    if ([_delegate respondsToSelector:@selector(didReceiveCacheObject:)]) {
      //Warn delegate in main thread.
      dispatch_async(dispatch_get_main_queue(), ^{
        [self->_delegate didReceiveCacheObject:cObject];
      });
      //delegate non more necessary (delegate secure mode!)
      _delegate = nil;
    }
  }
}


- (void)taskRefreshCacheClassModel:(Class)classModel
{
  [self refreshCacheModel:classModel];
  if ([_delegate respondsToSelector:@selector(didRefreshCacheModel)]) {
    [_delegate didRefreshCacheModel];
    
    //delegate non more necessary (delegate secure mode!)
    _delegate = nil;
  }
}


- (CMCacheModel *)cacheModelForClassModel:(Class)classModel
{
  CMCacheModel *theModel = nil;
  NSString *keyModel = NSStringFromClass(classModel);
  if (keyModel) {
    
    theModel = _cacheModels[keyModel];
    if (!theModel) {
      
      theModel = [[classModel alloc] init];
      if ([theModel isKindOfClass:[CMCacheModel class]]) {
        
        _cacheModels[keyModel] = theModel;
      }
      else {
        // Unknown Class!
        theModel = nil;
      }
    }
  }
  return theModel;
}


@end