//
//  NSInvocation+BlocksKit.h
//  BlocksKit
//

#import "BKDefines.h"
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN


@interface NSInvocation (BlocksKit)

/**

	NSInvocation *invocation = [NSInvocation invocationWithTarget:target block:^(id myObject) {
		[myObject someMethodWithArg:42.0];
	}];

 */
+ (NSInvocation *)bk_invocationWithTarget:(id)target block:(void (^)(id target))block;

@end

NS_ASSUME_NONNULL_END
