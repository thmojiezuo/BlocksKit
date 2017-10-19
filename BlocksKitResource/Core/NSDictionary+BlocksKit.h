//
//  NSDictionary+BlocksKit.h
//  BlocksKit
//

#import "BKDefines.h"
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN


@interface __GENERICS(NSDictionary, KeyType, ObjectType) (BlocksKit)

/**
     串行遍历容器中所有元素
 */
- (void)bk_each:(void (^)(KeyType key, ObjectType obj))block;

/**
 并发遍历容器中所有元素（不要求容器中元素顺次遍历的时候可以使用此种遍历方式来提高遍历速度）
 */
- (void)bk_apply:(void (^)(KeyType key, ObjectType obj))block;

/**
     返回第一个符合block条件（让block返回YES）的对象
 */
- (nullable id)bk_match:(BOOL (^)(KeyType key, ObjectType obj))block;

/**
 返回所有符合block条件（让block返回YES）的对象
 */
- (NSDictionary *)bk_select:(BOOL (^)(KeyType key, ObjectType obj))block;

/** Loops through a dictionary to find the key/value pairs not matching the block.

 This selector performs *literally* the exact same function as bk_select: but in reverse.

 This is useful, as one may expect, for filtering objects.
	 NSDictionary *strings = [userData bk_reject:^BOOL(id key, id value) {
	   return ([obj isKindOfClass:[NSString class]]);
	 }];

 @param block A BOOL-returning code block for a key/value pair.
 @return Returns a dictionary of all objects not found.
 */
- (NSDictionary *)bk_reject:(BOOL (^)(KeyType key, ObjectType obj))block;

/** Call the block once for each object and create a dictionary with the same keys
 and a new set of values.

 @param block A block that returns a new value for a key/value pair.
 @return Returns a dictionary of the objects returned by the block.
 */
- (NSDictionary *)bk_map:(id (^)(KeyType key, ObjectType obj))block;

/** Loops through a dictionary to find whether any key/value pair matches the block.

 This method is similar to the Scala list `exists`. It is functionally
 identical to bk_match: but returns a `BOOL` instead. It is not recommended
 to use bk_any: as a check condition before executing bk_match:, since it would
 require two loops through the dictionary.

 @param block A two-argument, BOOL-returning code block.
 @return YES for the first time the block returns YES for a key/value pair, NO otherwise.
 */
- (BOOL)bk_any:(BOOL (^)(KeyType key, ObjectType obj))block;

/** Loops through a dictionary to find whether no key/value pairs match the block.

 This selector performs *literally* the exact same function as bk_all: but in reverse.

 @param block A two-argument, BOOL-returning code block.
 @return YES if the block returns NO for all key/value pairs in the dictionary, NO otherwise.
 */
- (BOOL)bk_none:(BOOL (^)(KeyType key, ObjectType obj))block;

/** Loops through a dictionary to find whether all key/value pairs match the block.

 @param block A two-argument, BOOL-returning code block.
 @return YES if the block returns YES for all key/value pairs in the dictionary, NO otherwise.
 */
- (BOOL)bk_all:(BOOL (^)(KeyType key, ObjectType obj))block;

@end

NS_ASSUME_NONNULL_END
