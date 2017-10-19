//
//  NSObject+BKBlockExecution.h
//  BlocksKit
//

#import "BKDefines.h"
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef __nonnull id <NSObject, NSCopying> BKCancellationToken;


@interface NSObject (BKBlockExecution)

/**
     主线程执行block方法，延迟时间可选
 */
- (BKCancellationToken)bk_performAfterDelay:(NSTimeInterval)delay usingBlock:(void (^)(id obj))block;

/**
     主线程执行block方法，延迟时间可选
 */
+ (BKCancellationToken)bk_performAfterDelay:(NSTimeInterval)delay usingBlock:(void (^)(void))block;


/** 后台线程执行block方法，延迟时间可选
 
 This method is functionally identical to @c -bk_performAfterDelay:usingBlock:
 except the block will be performed on a background queue.
 
 @warning *Important:* Use of the **self** reference in a block is discouraged.
 The block argument @c obj should be used instead.
 
 @see bk_performAfterDelay:usingBlock:
 @param delay A measure in seconds.
 @param block A single-argument code block, where @c obj is the reciever.
 @return An opaque, temporary token that may be used to cancel execution.
 */
- (BKCancellationToken)bk_performInBackgroundAfterDelay:(NSTimeInterval)delay usingBlock:(void (^)(id obj))block;

/** 后台线程执行block方法，延迟时间可选
 
 This method is functionally identical to @c +bk_performAfterDelay:usingBlock:
 except the block will be performed on a background queue.
 
 @see bk_performAfterDelay:usingBlock:
 @param delay A measure in seconds.
 @param block A code block.
 @return An opaque, temporary token that may be used to cancel execution.
 */
+ (BKCancellationToken)bk_performInBackgroundAfterDelay:(NSTimeInterval)delay usingBlock:(void (^)(void))block;

/** 所有执行block相关的方法都是此方法的简化版，该函数在指定的block队列上以指定的时间延迟执行block
 
 This method is functionally identical to @c -bk_performAfterDelay:usingBlock:
 except the block will be performed on a background queue.
 
 @warning *Important:* Use of the **self** reference in a block is discouraged.
 The block argument @c obj should be used instead.
 
 @see bk_performAfterDelay:usingBlock:
 @param queue A background queue.
 @param delay A measure in seconds.
 @param block A single-argument code block, where @c obj is the reciever.
 @return An opaque, temporary token that may be used to cancel execution.
 */
- (BKCancellationToken)bk_performOnQueue:(dispatch_queue_t)queue afterDelay:(NSTimeInterval)delay usingBlock:(void (^)(id obj))block;

/** 所有执行block相关的方法都是此方法的简化版，该函数在指定的block队列上以指定的时间延迟执行block
 
 This method is functionally identical to @c +bk_performAfterDelay:usingBlock:
 except the block will be performed on a background queue.
 
 @see bk_performAfterDelay:usingBlock:
 @param queue A background queue.
 @param delay A measure in seconds.
 @param block A code block.
 @return An opaque, temporary token that may be used to cancel execution.
 */
+ (BKCancellationToken)bk_performOnQueue:(dispatch_queue_t)queue afterDelay:(NSTimeInterval)delay usingBlock:(void (^)(void))block;

/** 取消block，非常牛逼！！！一般来说一个block加到block queue上是没法取消的，此方法实现了block的取消操作（必须是用BlocksKit投放的block）
 
 @warning *Important:* It is not recommended to cancel a block executed
 with a delay of @c 0.
 
 @param token A cancellation token, as returned from one of the `bk_perform`
 methods.
 */
+ (void)bk_cancelBlock:(BKCancellationToken)token;

@end

@interface NSObject (BKBlockExecution_Deprecated)

- (BKCancellationToken)bk_performBlock:(void (^)(id obj))block afterDelay:(NSTimeInterval)delay DEPRECATED_MSG_ATTRIBUTE("Replaced with -bk_performAfterDelay:usingBlock:");
+ (BKCancellationToken)bk_performBlock:(void (^)(void))block afterDelay:(NSTimeInterval)delay DEPRECATED_MSG_ATTRIBUTE("Replaced with +bk_performAfterDelay:usingBlock:");
- (BKCancellationToken)bk_performBlockInBackground:(void (^)(id obj))block afterDelay:(NSTimeInterval)delay DEPRECATED_MSG_ATTRIBUTE("Replaced with -bk_performInBackgroundAfterDelay:usingBlock:");
+ (BKCancellationToken)bk_performBlockInBackground:(void (^)(void))block afterDelay:(NSTimeInterval)delay DEPRECATED_MSG_ATTRIBUTE("Replaced with +bk_performInBackgroundAfterDelay:usingBlock:");
+ (BKCancellationToken)bk_performBlock:(void (^)(void))block onQueue:(dispatch_queue_t)queue afterDelay:(NSTimeInterval)delay DEPRECATED_MSG_ATTRIBUTE("Replaced with -bk_performOnQueue:afterDelay:usingBlock:");
- (BKCancellationToken)bk_performBlock:(void (^)(id obj))block onQueue:(dispatch_queue_t)queue afterDelay:(NSTimeInterval)delay DEPRECATED_MSG_ATTRIBUTE("Replaced with -bk_performOnQueue:afterDelay:usingBlock:");

@end

NS_ASSUME_NONNULL_END
