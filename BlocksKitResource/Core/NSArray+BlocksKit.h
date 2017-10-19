//
//  NSArray+BlocksKit.h
//  BlocksKit
//

#import "BKDefines.h"
#import <Foundation/Foundation.h>
#import <CoreGraphics/CGBase.h> // for CGFloat

NS_ASSUME_NONNULL_BEGIN


@interface __GENERICS(NSArray, ObjectType) (BlocksKit)

/**
     串行遍历容器中所有元素
 */
- (void)bk_each:(void (^)(ObjectType obj))block;

/**
     并发遍历容器中所有元素（不要求容器中元素顺次遍历的时候可以使用此种遍历方式来提高遍历速度）
 */
- (void)bk_apply:(void (^)(ObjectType obj))block;

/**
     返回第一个符合block条件（让block返回YES）的对象
 */
- (nullable id)bk_match:(BOOL (^)(ObjectType obj))block;

/**
     返回所有符合block条件（让block返回YES）的对象
 */
- (NSArray *)bk_select:(BOOL (^)(ObjectType obj))block;

/**
     返回所有！！！不符合block条件（让block返回YES）的对象
 */
- (NSArray *)bk_reject:(BOOL (^)(ObjectType obj))block;

/**
     返回对象的block映射数组
 */
- (NSArray *)bk_map:(id (^)(ObjectType obj))block;

/** Behaves like map, but doesn't add NSNull objects if you return nil in the block.

 @param block A single-argument, object-returning code block.
 @return Returns an array of the objects returned by the block.
 */
- (NSArray *)bk_compact:(id (^)(ObjectType obj))block;

/** Arbitrarily accumulate objects using a block.

 The concept of this selector is difficult to illustrate in words. The sum can
 be any NSObject, including (but not limited to) a string, number, or value.

 For example, you can concentate the strings in an array:
	 NSString *concentrated = [stringArray bk_reduce:@"" withBlock:^id(id sum, id obj) {
	   return [sum stringByAppendingString:obj];
	 }];

 You can also do something like summing the lengths of strings in an array:
	 NSUInteger value = [[[stringArray bk_reduce:nil withBlock:^id(id sum, id obj) {
	   return @([sum integerValue] + obj.length);
	 }]] unsignedIntegerValue];

 @param initial The value of the reduction at its start.
 @param block A block that takes the current sum and the next object to return the new sum.
 @return An accumulated value.
 */
- (nullable id)bk_reduce:(nullable id)initial withBlock:(__nullable id (^)(__nullable id sum, ObjectType obj))block;

/**
 Sometimes we just want to loop an objects list and reduce one property, where
 each result is a primitive type.

 For example, say we want to calculate the total age of a list of people.

 Code without using block will be something like:

	 NSArray *peoples = @[p1, p2, p3];
	 NSInteger totalAge = 0;
	 for (People *people in peoples) {
	     totalAge += [people age];
	 }

 We can use a block to make it simpler:

	 NSArray *peoples = @[p1, p2, p3];
	 NSInteger totalAge = [peoples reduceInteger:0 withBlock:^(NSInteger result, id obj, NSInteger index) {
	 	 return result + [obj age];
	 }];

 */
- (NSInteger)bk_reduceInteger:(NSInteger)initial withBlock:(NSInteger(^)(NSInteger result, ObjectType obj))block;

/**
 Sometimes we just want to loop an objects list and reduce one property, where
 each result is a primitive type.
 
 For instance, say we want to caculate the total balance from a list of people.
 
 Code without using a block will be something like:
 
	 NSArray *peoples = @[p1, p2, p3];
	 CGFloat totalBalance = 0;
	 for (People *people in peoples) {
	     totalBalance += [people balance];
	 }
 
 We can use a block to make it simpler:
 
	 NSArray *peoples = @[p1, p2, p3];
	 CGFloat totalBalance = [peoples reduceFloat:.0f WithBlock:^CGFloat(CGFloat result, id obj, NSInteger index) {
	 	 return result + [obj balance];
	 }];

 */

- (CGFloat)bk_reduceFloat:(CGFloat)inital withBlock:(CGFloat(^)(CGFloat result, ObjectType obj))block;

/**
     查看容器是否有符合block条件的对象 ，判断是否容器中至少有一个元素符合block条件
 */
- (BOOL)bk_any:(BOOL (^)(ObjectType obj))block;

/**
     判断是否容器中所有元素都！！！不符合block条件
 */
- (BOOL)bk_none:(BOOL (^)(ObjectType obj))block;

/**
     判断是否容器中所有元素都符合block条件
 */
- (BOOL)bk_all:(BOOL (^)(ObjectType obj))block;

/** Tests whether every element of this array relates to the corresponding element of another array according to match by block.

 For example, finding if a list of numbers corresponds to their sequenced string values;
 NSArray *numbers = @[ @(1), @(2), @(3) ];
 NSArray *letters = @[ @"1", @"2", @"3" ];
 BOOL doesCorrespond = [numbers bk_corresponds:letters withBlock:^(id number, id letter) {
	return [[number stringValue] isEqualToString:letter];
 }];

 @param list An array of objects to compare with.
 @param block A two-argument, BOOL-returning code block.
 @return Returns a BOOL, true if every element of array relates to corresponding element in another array.
 */
- (BOOL)bk_corresponds:(NSArray *)list withBlock:(BOOL (^)(ObjectType obj1, id obj2))block;

@end

NS_ASSUME_NONNULL_END
