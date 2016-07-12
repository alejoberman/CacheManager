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


#import "CMCacheObject.h"

/** @brief default update notification name */
#define kCMCacheManagerUpdateNotification @"kCMCacheManagerUpdateNotification"

@protocol CMCacheManagerDelegate;
@class CMCacheObject;


/**
 @brief Abstract CMCacheModel
 You must overwrite all well-defineds methods except initialisation method.
 */

@interface CMCacheModel : NSObject
{
  id<CMCacheManagerDelegate> _delegate;
  NSString *_modelTypeString;
}

@property (readonly, strong) NSString *modelTypeString;



/**
 @brief Gives a key thats identify a ModelType.
 @return the string with key for a ModelType.
 */
- (NSString *)keyCacheModelType;

/**
 @brief initialisation method.
 */
- (instancetype)initWithDelegate:(id<CMCacheManagerDelegate>)delegate;

/**
 @brief : retur YES if a CacheObject found;
 @param cacheObject : the object to search. You must create a new object to use as search predicate.
 */
- (BOOL)hasObject:(id<CMCacheObject>)cacheObject;

/**
 @brief save CacheObject;
 @param cacheObjectId : the object id.
 */
- (void)saveObjectCache:(id<CMCacheObject>)cacheObject;

/**
 @brief updates CacheObject if exist in cache;
 @param cacheObjectId : the object id.
 */
- (void)updateObjectCache:(id<CMCacheObject>)cacheObject;

/**
 @brief : retur the CacheObject if found;
 @param cacheObject : the object to search.
 */
- (id<CMCacheObject>)cacheObjectForObject:(id<CMCacheObject>)cacheObject;

/**
 @brief : retur the CacheObject if found;
 @param objectId : the object identifier.
 */
- (id<CMCacheObject>)cacheObjectForObjectId:(NSString *)objectId;

/**
 @brief : retur all Cache Objects from cache;
 @return all <CMCacheObject> object into a dictionary. Each object correspond to a dictionary key by her ID.
 @see CMCacheObject.
 */
- (NSDictionary *)allCacheObjects;

/**
 @brief : remove a CacheObject;
 @param cacheObject : the object to remove from cache.
 */
- (void)removeCacheObject:(id<CMCacheObject>)cacheObject;

/**
 @brief synchronize all cache objects into persistent model.
 @note the cache instance in memory is cleaned. You must use this method if unused cache times. 
 */
- (void)synchronizeCacheModel;

/**
 @brief synchronize asynchronusly all cache objects into persistent model.
 @note the cache instance in memory is cleaned. You must use this method if unused cache times.
 */
- (void)synchronizeAsyncCacheModel;

/**
 @brief purge all invalids objects.
 Each CacheModel must match all valids objects.
 */
- (void)refreshCacheModel;

/**
 @brief Clean all cache objects.
 */
- (void)cleanCacheObject;

/**
 @brief Take the default resources cache path.
 @return the default resources cache path or nil in error case.
 */
- (NSString *)defaultResourcesPath;

/**
 @brief Take the cache path.
 @return the prefix path or nil in error case.
 */
- (NSString *)pathForCacheFileSystemDirectory:(NSString *)directory;

/**
 * @brief notify update.
 */
- (void)notifyCacheUpdatesWithNotificationName:(NSString *)notificationName;

/**
 @brief remove resource in current model.
 @param the relative path string.
 */
- (void)deleteItemResource:(NSString *)resourcePath;
@end
