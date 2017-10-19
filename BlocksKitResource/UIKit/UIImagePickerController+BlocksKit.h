//
//  UIImagePickerController+BlocksKit.h
//  BlocksKit
//
//  Contributed by Yas Kuraishi.
//

#import "BKDefines.h"
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN


@interface UIImagePickerController (BlocksKit)

/**
 *	The block that fires after the receiver finished picking up an image
 */
@property (nonatomic, copy, nullable) void(^bk_didFinishPickingMediaBlock)(UIImagePickerController *, NSDictionary *);

/**
 *	The block that fires after the user cancels out of picker
 */
@property (nonatomic, copy, nullable) void(^bk_didCancelBlock)(UIImagePickerController *);

@end

NS_ASSUME_NONNULL_END
