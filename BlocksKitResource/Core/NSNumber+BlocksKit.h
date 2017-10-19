//
//  NSNumber+BlocksKit.h
//  BlocksKit
//

#import <Foundation/Foundation.h>


@interface NSNumber (BlocksKit)

/** Performs a block `self` number of times

 @param block A void-returning code block that accepts no arguments.
 */
- (void)bk_times:(void (^)(void))block;

@end
