//
//  NSObject+BKAssociatedObjects.h
//  BlocksKit
//

#import "BKDefines.h"
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN


@interface NSObject (BKAssociatedObjects)

/** 以OBJC_ASSOCIATION_RETAIN_NONATOMIC方式绑定关联对象

 The associated value is retained as if it were a property
 synthesized with `nonatomic` and `retain`.

 Using retained association is strongly recommended for most
 Objective-C object derivative of NSObject, particularly
 when it is subject to being externally released or is in an
 `NSAutoreleasePool`.

 @param value Any object.
 @param key A unique key pointer.
 */
- (void)bk_associateValue:(nullable id)value withKey:(const void *)key;

/** 以OBJC_ASSOCIATION_RETAIN_NONATOMIC方式绑定关联对象

 @see associateValue:withKey:
 @param value Any object.
 @param key A unique key pointer.
 */
+ (void)bk_associateValue:(nullable id)value withKey:(const void *)key;

/** 以OBJC_ASSOCIATION_RETAIN方式绑定关联对象

 The associated value is retained as if it were a property
 synthesized with `atomic` and `retain`.

 Using retained association is strongly recommended for most
 Objective-C object derivative of NSObject, particularly
 when it is subject to being externally released or is in an
 `NSAutoreleasePool`.

 @see associateValue:withKey:
 @param value Any object.
 @param key A unique key pointer.
 */
- (void)bk_atomicallyAssociateValue:(nullable id)value withKey:(const void *)key;

/** 以OBJC_ASSOCIATION_RETAIN方式绑定关联对象

 @see associateValue:withKey:
 @param value Any object.
 @param key A unique key pointer.
 */
+ (void)bk_atomicallyAssociateValue:(nullable id)value withKey:(const void *)key;

/** 以OBJC_ASSOCIATION_COPY_NONATOMIC方式绑定关联对象

 The associated value is copied as if it were a property
 synthesized with `nonatomic` and `copy`.

 Using copied association is recommended for a block or
 otherwise `NSCopying`-compliant instances like NSString.

 @param value Any object, pointer, or value.
 @param key A unique key pointer.
 */
- (void)bk_associateCopyOfValue:(nullable id)value withKey:(const void *)key;

/** 以OBJC_ASSOCIATION_COPY_NONATOMIC方式绑定关联对象

 @see associateCopyOfValue:withKey:
 @param value Any object, pointer, or value.
 @param key A unique key pointer.
 */
+ (void)bk_associateCopyOfValue:(nullable id)value withKey:(const void *)key;

/** 以OBJC_ASSOCIATION_COPY方式绑定关联对象

 The associated value is copied as if it were a property
 synthesized with `atomic` and `copy`.

 Using copied association is recommended for a block or
 otherwise `NSCopying`-compliant instances like NSString.

 @see associateCopyOfValue:withKey:
 @param value Any object, pointer, or value.
 @param key A unique key pointer.
 */
- (void)bk_atomicallyAssociateCopyOfValue:(nullable id)value withKey:(const void *)key;

/** 以OBJC_ASSOCIATION_COPY方式绑定关联对象

 @see associateCopyOfValue:withKey:
 @param value Any object, pointer, or value.
 @param key A unique key pointer.
 */
+ (void)bk_atomicallyAssociateCopyOfValue:(nullable id)value withKey:(const void *)key;

/** 弱绑定

 A weak association will cause the pointer to be set to zero
 or nil upon the disappearance of what it references;
 in other words, the associated object is not kept alive.

 @param value Any object.
 @param key A unique key pointer.
 */
- (void)bk_weaklyAssociateValue:(nullable __autoreleasing id)value withKey:(const void *)key;

/** 弱绑定

 @see weaklyAssociateValue:withKey:
 @param value Any object.
 @param key A unique key pointer.
 */
+ (void)bk_weaklyAssociateValue:(nullable __autoreleasing id)value withKey:(const void *)key;

/** Returns the associated value for a key on the reciever.

 @param key A unique key pointer.
 @return The object associated with the key, or `nil` if not found.
 */
- (nullable id)bk_associatedValueForKey:(const void *)key;

/** Returns the associated value for a key on the receiving class.

 @see associatedValueForKey:
 @param key A unique key pointer.
 @return The object associated with the key, or `nil` if not found.
 */
+ (nullable id)bk_associatedValueForKey:(const void *)key;

/**
     删除所有绑定的关联对象
 */
- (void)bk_removeAllAssociatedObjects;

/**
     删除所有绑定的关联对象
 */
+ (void)bk_removeAllAssociatedObjects;

@end

NS_ASSUME_NONNULL_END
