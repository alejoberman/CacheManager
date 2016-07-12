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


#import "CMCacheManagerDelegate.h"
#import "CMCacheObject.h"

@interface CMCacheManager : NSObject
{
  __weak id<CMCacheManagerDelegate> _delegate;
  //Cache systems
  NSMutableDictionary *_cacheModels;
}

@property (nonatomic, weak)id<CMCacheManagerDelegate> delegate;

+ (CMCacheManager *)sharedCacheManager;

/**
 @brief Returns the cache path for a given cacheModel.
 @return the prefix path or nil in error case.
 */
- (NSString *)pathForCacheFileSystemDirectoryForCacheModel:(Class)classModel;

/**
 @brief : retur YES if a CacheObject found;
 @param cacheObject : the object to search.
 @param classModel : the class model for the cacheObject.
 */
- (BOOL)hasObject:(id<CMCacheObject>)cacheObject classModel:(Class)classModel;

/**
 @brief retrieves asyncronusly a cache object from cache.
 @param cacheObject : a cacheObject that contains the data to retrieve.
 @param classModel : the class model for the cacheObject.
 @remarks This method dereference its delegate!
 */
- (void)retrieveAsynchronousCacheObject:(id<CMCacheObject>)cacheObject classModel:(Class)classModel;

/**
 @brief refresh operations for a CacheModel in separated thread.
 @param classModel : the class model for the cacheObject.
 */
- (void)refreshAsynchronousCacheModel:(Class)classModel;

/**
 @brief save a cache object into cache.
 @param cacheObject : a cacheObject that contains the data to save.
 @param classModel : the class model for the cacheObject.
 */
- (void)saveCacheObject:(id<CMCacheObject>)cacheObject classModel:(Class)classModel;

/**
 @brief retrieves syncronusly a cache object from cache.
 @param cacheObject : a cacheObject that contains the data to retrieve.
 @param classModel : the class model for the cacheObject.
 */
- (id<CMCacheObject>)cacheObjectForObject:(id<CMCacheObject>)cacheObject classModel:(Class)classModel;

/**
 @brief retrieves syncronusly all cache objects from cache.
 @param classModel : the class model for the cacheObject.
 */
- (NSDictionary *)allCacheObjectsForClassModel:(Class)classModel;


/**
 @brief remove a cacheObject from cache.
 @param cacheObject : the cacheObject to remove from cache.
 @param classModel : the class model for the cacheObject.
 */
- (void)removeCacheObject:(id<CMCacheObject>)cacheObject classModel:(Class)classModel;

/**
 @brief synchronize all cache objects into persistent model.
 @note the cache instance in memory is writed to persistent support.
 */
- (void)synchronizeCacheModel:(Class)classModel;

/**
 @brief synchronize asyncronusly all cache objects into persistent model.
 @note the cache instance in memory is writed to persistent support.
 */
- (void)synchronizeAsyncCacheModel:(Class)classModel;

/**
 @brief refresh operations for a CacheModel.
 @param classModel : the class model for the cacheObject.
 */
- (void)refreshCacheModel:(Class)classModel;

/**
 @brief clean cache for a CacheModel.
 @param classModel : the class model for the cacheObject.
 */
- (void)cleanCacheModel:(Class)classModel;

/**
 @brief remove a given resource from cache.
 @param resourcePath : the path for resource to remove from cache.
 @param classModel : the class model for the cacheObject.
 */
- (void)deleteItemResource:(NSString *)resourcePath classModel:(Class)classModel;

@end
