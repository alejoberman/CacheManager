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


#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface UIApplication (CMAdditions)

/**
 @param pDirectory if passed nil, the base folder is returned without appending pDirectory
 @return the full path with pDirectory in the application cache directory
 */
- (NSString *)pathAtCacheFor:(NSString *)pDirectory;

/**
 @param pDirectory if passed nil, the base folder is returned without appending pDirectory
 @return the full path with pDirectory in the application library directory
 */
- (NSString *)pathAtLibraryFor:(NSString *)pDirectory;

/**
 @param pDirectory if passed nil, the base folder is returned without appending pDirectory
 @return the full path with pDirectory in the application documents directory
 */
- (NSString *)pathAtDocumentsFor:(NSString *)pDirectory;

/**
 @return the application version
 */
- (NSString *)appVersion;

/*!
 @abstract Gets the bundle path for a given resource.
 */
- (NSString *)bundlePathForResource:(NSString *)resource;


@end