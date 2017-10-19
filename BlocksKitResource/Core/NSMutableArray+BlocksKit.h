//
//  NSMutableArray+BlocksKit.h
//  BlocksKit
//

#import "BKDefines.h"
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN


@interface __GENERICS(NSMutableArray, ObjectType) (BlocksKit)

/**
     删除容器中!!!不符合block条件的对象，即只保留符合block条件的对象
 */
- (void)bk_performSelect:(BOOL (^)(id ObjectType))block;

/**
     删除容器中符合block条件的对象
 */
- (void)bk_performReject:(BOOL (^)(id ObjectType))block;

/** 容器中的对象变换为自己的block映射对象

 This is sometimes referred to as a transform, mutating one of each object:
	[foo bk_performMap:^id(id obj) {
	  return [dateTransformer dateFromString:obj];
	}];

 @param block A single-argument, object-returning code block.
 @see <NSArray(BlocksKit)>bk_map:
 */
- (void)bk_performMap:(id (^)(id ObjectType))block;

@end

NS_ASSUME_NONNULL_END
