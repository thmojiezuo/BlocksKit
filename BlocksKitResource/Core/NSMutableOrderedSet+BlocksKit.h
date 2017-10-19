//
//  NSMutableOrderedSet+BlocksKit.h
//  BlocksKit
//

#import "BKDefines.h"
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN


@interface __GENERICS(NSMutableOrderedSet, ObjectType) (BlocksKit)

/** Filters a mutable ordered set to the objects matching the block.

 @param block A single-argument, BOOL-returning code block.
 @see <NSOrderedSet(BlocksKit)>bk_reject:
 */
- (void)bk_performSelect:(BOOL (^)(id ObjectType))block;

/** Filters a mutable ordered set to all objects but the ones matching the
 block, the logical inverse to bk_select:.

 @param block A single-argument, BOOL-returning code block.
 @see <NSOrderedSet(BlocksKit)>bk_select:
 */
- (void)bk_performReject:(BOOL (^)(id ObjectType))block;

/** Transform the objects in the ordered set to the results of the block.

 This is sometimes referred to as a transform, mutating one of each object:
	 [foo bk_performMap:^id(id obj) {
		 return [dateTransformer dateFromString:obj];
	 }];

 @param block A single-argument, object-returning code block.
 @see <NSOrderedSet(BlocksKit)>bk_map:
 */
- (void)bk_performMap:(id (^)(id ObjectType))block;

@end

NS_ASSUME_NONNULL_END
