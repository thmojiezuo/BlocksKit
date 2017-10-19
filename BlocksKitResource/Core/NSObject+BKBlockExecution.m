//
//  NSObject+BKBlockExecution.m
//  BlocksKit
//

#import "NSObject+BKBlockExecution.h"

#if (defined(__IPHONE_OS_VERSION_MAX_ALLOWED) && __IPHONE_OS_VERSION_MAX_ALLOWED >= 80000) || (defined(__MAC_OS_X_VERSION_MAX_ALLOWED) && __MAC_OS_X_VERSION_MAX_ALLOWED >= 1010)
#define DISPATCH_CANCELLATION_SUPPORTED 1
#else
#define DISPATCH_CANCELLATION_SUPPORTED 1
#endif

NS_INLINE dispatch_time_t BKTimeDelay(NSTimeInterval t) {
    return dispatch_time(DISPATCH_TIME_NOW, (uint64_t)(NSEC_PER_SEC * t));
}

NS_INLINE BOOL BKSupportsDispatchCancellation(void) {
#if DISPATCH_CANCELLATION_SUPPORTED
    return (&dispatch_block_cancel != NULL);
#else
    return NO;
#endif
}

NS_INLINE dispatch_queue_t BKGetBackgroundQueue(void) {
    return dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
}

static id <NSObject, NSCopying> BKDispatchCancellableBlock(dispatch_queue_t queue, NSTimeInterval delay, void(^block)(void)) {
    dispatch_time_t time = BKTimeDelay(delay);
    
#if DISPATCH_CANCELLATION_SUPPORTED
    if (BKSupportsDispatchCancellation()) {
        dispatch_block_t ret = dispatch_block_create(0, block);
        dispatch_after(time, queue, ret);
        return ret;
    }
#endif
    //cancelled是个__block变量，使得该block在加入queue后能够逻辑上取消。注意，仅仅是逻辑上取消，不能把block从queue中剔除。
    __block BOOL cancelled = NO;
    //在外部block之上加一层能够逻辑取消的代码，使其变为一个wrapper block
    //当调用wrapper(YES)的时候就让__block BOOL cancelled = YES,使得以后每次block主体都被跳过。
    void (^wrapper)(BOOL) = ^(BOOL cancel) {
        //cancel参数是为了在外部能够控制cancelled _block变量
        if (cancel) {
            cancelled = YES;
            return;
        }
        if (!cancelled) block();
    };
    //每个投入queue中的block实际上是wraper版的block
    dispatch_after(time, queue, ^{
        //把cancel设置为NO,block能够逻辑执行
        wrapper(NO);
    });
    //返回wraper block，以便bk_cancelBlock的时候使用
    return wrapper;
}

@implementation NSObject (BlocksKit)

- (id <NSObject, NSCopying>)bk_performAfterDelay:(NSTimeInterval)delay usingBlock:(void (^)(id obj))block
{
    return [self bk_performOnQueue:dispatch_get_main_queue() afterDelay:delay usingBlock:block];
}

+ (id <NSObject, NSCopying>)bk_performAfterDelay:(NSTimeInterval)delay usingBlock:(void (^)(void))block
{
    return [NSObject bk_performOnQueue:dispatch_get_main_queue() afterDelay:delay usingBlock:block];
}

- (id <NSObject, NSCopying>)bk_performInBackgroundAfterDelay:(NSTimeInterval)delay usingBlock:(void (^)(id obj))block
{
    return [self bk_performOnQueue:BKGetBackgroundQueue() afterDelay:delay usingBlock:block];
}

+ (id <NSObject, NSCopying>)bk_performInBackgroundAfterDelay:(NSTimeInterval)delay usingBlock:(void (^)(void))block
{
    return [NSObject bk_performOnQueue:BKGetBackgroundQueue() afterDelay:delay usingBlock:block];
}

- (id <NSObject, NSCopying>)bk_performOnQueue:(dispatch_queue_t)queue afterDelay:(NSTimeInterval)delay usingBlock:(void (^)(id obj))block
{
    NSParameterAssert(block != nil);
    
    return BKDispatchCancellableBlock(queue, delay, ^{
        block(self);
    });
}

+ (id <NSObject, NSCopying>)bk_performOnQueue:(dispatch_queue_t)queue afterDelay:(NSTimeInterval)delay usingBlock:(void (^)(void))block
{
    NSParameterAssert(block != nil);
    
    return BKDispatchCancellableBlock(queue, delay, block);
}

+ (void)bk_cancelBlock:(id <NSObject, NSCopying>)block
{
    NSParameterAssert(block != nil);
    
#if DISPATCH_CANCELLATION_SUPPORTED
    if (BKSupportsDispatchCancellation()) {
        dispatch_block_cancel((dispatch_block_t)block);
        return;
    }
#endif
    //把cancel设置为YES,修改block中_block cancelled变量，如果此时block未执行则，block在执行的时候其逻辑主体会被跳过
    void (^wrapper)(BOOL) = (void(^)(BOOL))block;
    wrapper(YES);
}

@end

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-implementations"

@implementation NSObject (BKBlockExecution_Deprecated)

#pragma mark - Legacy verions

- (id <NSObject, NSCopying>)bk_performBlock:(void (^)(id obj))block afterDelay:(NSTimeInterval)delay
{
    return [self bk_performAfterDelay:delay usingBlock:block];
}

+ (id <NSObject, NSCopying>)bk_performBlock:(void (^)(void))block afterDelay:(NSTimeInterval)delay
{
    return [self bk_performAfterDelay:delay usingBlock:block];
}

- (id <NSObject, NSCopying>)bk_performBlockInBackground:(void (^)(id obj))block afterDelay:(NSTimeInterval)delay
{
    return [self bk_performInBackgroundAfterDelay:delay usingBlock:block];
}

+ (id <NSObject, NSCopying>)bk_performBlockInBackground:(void (^)(void))block afterDelay:(NSTimeInterval)delay
{
    return [self bk_performInBackgroundAfterDelay:delay usingBlock:block];
}

- (id <NSObject, NSCopying>)bk_performBlock:(void (^)(id obj))block onQueue:(dispatch_queue_t)queue afterDelay:(NSTimeInterval)delay
{
    return [self bk_performOnQueue:queue afterDelay:delay usingBlock:block];
}

+ (id <NSObject, NSCopying>)bk_performBlock:(void (^)(void))block onQueue:(dispatch_queue_t)queue afterDelay:(NSTimeInterval)delay
{
    return [self bk_performOnQueue:queue afterDelay:delay usingBlock:block];
}

@end

#pragma clang diagnostic pop
