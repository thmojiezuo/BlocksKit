//
//  UIBarButtonItem+BlocksKit.h
//  BlocksKit
//

#import "BKDefines.h"
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN


@interface UIBarButtonItem (BlocksKit)

/**
     初始化一个系统样式的 UIBarButtonItem
 */
- (instancetype)bk_initWithBarButtonSystemItem:(UIBarButtonSystemItem)systemItem handler:(void (^)(id sender))action BK_INITIALIZER;

/**
     初始化一个自定义图片的 UIBarButtonItem，图片大小为 20 * 20
 */
- (instancetype)bk_initWithImage:(UIImage *)image style:(UIBarButtonItemStyle)style handler:(void (^)(id sender))action BK_INITIALIZER;

/**
     The landscapeImagePhone to be used for the item in landscape bars in the UIUserInterfaceIdiomPhone idiom.
 */
- (instancetype)bk_initWithImage:(UIImage *)image landscapeImagePhone:(UIImage *)landscapeImagePhone style:(UIBarButtonItemStyle)style handler:(void (^)(id sender))action BK_INITIALIZER;

/**
     创建一个自定义 标题 的 UIBarButtonItem
 */
- (instancetype)bk_initWithTitle:(NSString *)title style:(UIBarButtonItemStyle)style handler:(void (^)(id sender))action BK_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
