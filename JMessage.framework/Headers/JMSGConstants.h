/*
 *	| |    | |  \ \  / /  | |    | |   / _______|
 *	| |____| |   \ \/ /   | |____| |  / /
 *	| |____| |    \  /    | |____| |  | |   _____
 * 	| |    | |    /  \    | |    | |  | |  |____ |
 *  | |    | |   / /\ \   | |    | |  \ \______| |
 *  | |    | |  /_/  \_\  | |    | |   \_________|
 *
 * Copyright (c) 2011 ~ 2015 Shenzhen HXHG. All rights reserved.
 */

#ifndef JMessage_JMSGConstants____FILEEXTENSION___
#define JMessage_JMSGConstants____FILEEXTENSION___

#import <Foundation/Foundation.h>


///----------------------------------------------------
/// @name type & define
///----------------------------------------------------

/*!
 * @abstract 异步回调 block
 *
 * @discussion 大多数异步 API 都会以过个 block 回调。
 *
 * - 如果调用出错，则 error 不为空，可根据 error.code 来获取错误码。该错误码 JMessage 相关文档里有详细的定义。
 * - 如果返回正常，则 error 为空。从 resultObject 去获取相应的返回。每个 API 的定义上都会有进一步的定义。
 *
 */
typedef void (^JMSGCompletionHandler)(id resultObject, NSError *error);

/*!
 * @abstract 空的 CompletionHandler.
 *
 * @discussion 用于不需要进行处理时.
 */
#define JMSG_NULL_COMPLETION_BLOCK ^(id resultObject, NSError *error){}

/*!
 * @abstract 数据返回的异步回调
 *
 * @discussion 专用于数据返回 API.
 *
 * - objectId 当前数据的ID标识.
 *   - 消息里返回 voice/image 的 media data 时, objectId 是 msgId;
 *   - 用户里返回 avatar 头像数据时, objectId 是 username.
 *
 */
typedef void (^JMSGAsyncDataHandler)(NSData *data, NSString *objectId, NSError *error);

/*!
 * @abstract 媒体上传进度 block
 *
 * @discussion 在发送消息时，可向 JMSGMessage 对象设置此 block，从而可以得到上传的进度
 */
typedef void (^JMSGMediaUploadProgressHandler)(float percent);

/*!
 * @abstract Generic 泛型
 */
#if __has_feature(objc_generics) || __has_extension(objc_generics)
#  define JMSG_GENERIC(...) <__VA_ARGS__>
#else
#  define JMSG_GENERIC(...)
#endif

/*!
 * @abstract nullable 用于定义某属性或者变量是否可允许为空
 */
#if __has_feature(nullability)
#  define JMSG_NONNULL __nonnull
#  define JMSG_NULLABLE __nullable
#else
#  define JMSG_NONNULL
#  define JMSG_NULLABLE
#endif

#if __has_feature(assume_nonnull)
#  ifdef NS_ASSUME_NONNULL_BEGIN
#    define JMSG_ASSUME_NONNULL_BEGIN NS_ASSUME_NONNULL_BEGIN
#  else
#    define JMSG_ASSUME_NONNULL_BEGIN _Pragma("clang assume_nonnull begin")
#  endif
#  ifdef NS_ASSUME_NONNULL_END
#    define JMSG_ASSUME_NONNULL_END NS_ASSUME_NONNULL_END
#  else
#    define JMSG_ASSUME_NONNULL_END _Pragma("clang assume_nonnull end")
#  endif
#else
#  define JMSG_ASSUME_NONNULL_BEGIN
#  define JMSG_ASSUME_NONNULL_END
#endif


///----------------------------------------------------
/// @name enums
///----------------------------------------------------

/*!
 * 会话类型 - 单聊、群聊
 */
typedef NS_ENUM(NSInteger, JMSGConversationType) {
  /// 单聊
  kJMSGConversationTypeSingle = 1,
  /// 群聊
  kJMSGConversationTypeGroup = 2,
};

//NSString *JMSGConversationTypeStr(JMSGConversationType type) {
//  if (type == kJMSGConversationTypeSingle) {
//    return @"conversationSingle";
//  } else {
//    return @"conversationGroup";
//  }
//}

/*!
 * 消息内容类型 - 文本、语音、图片等
 */
typedef NS_ENUM(NSInteger, JMSGContentType) {
  /// 不知道类型的消息
  kJMSGContentTypeUnknown = 0,
  /// 文本消息
  kJMSGContentTypeText = 1,
  /// 图片消息
  kJMSGContentTypeImage = 2,
  /// 语音消息
  kJMSGContentTypeVoice = 3,
  /// 自定义消息
  kJMSGContentTypeCustom = 4,
  /// 事件通知消息。服务器端下发的事件通知，本地展示为这个类型的消息展示出来
  kJMSGContentTypeEventNotification = 5,
};

//NSString *JMSGContentTypeStr(JMSGContentType type) {
//  switch (type) {
//    case kJMSGContentTypeUnknown:
//      return @"未知类型";
//    case kJMSGContentTypeText:
//      return @"文本消息";
//    case kJMSGContentTypeImage:
//      return @"图片消息";
//    case kJMSGContentTypeVoice:
//      return @"语音消息";
//    case kJMSGContentTypeCustom:
//      return @"自定义消息";
//    case kJMSGContentTypeEventNotification:
//      return @"事件通知消息";
//    default:
//      break;
//  }
//}


/*!
 * 消息状态
 */
typedef NS_ENUM(NSInteger, JMSGMessageStatus) {
  /// 发送息创建时的初始状态
  kJMSGMessageStatusSendDraft = 0,
  /// 消息正在发送过程中. UI 一般显示进度条
  kJMSGMessageStatusSending = 1,
  /// 媒体类消息文件上传失败
  kJMSGMessageStatusSendUploadFailed = 2,
  /// 媒体类消息文件上传成功
  kJMSGMessageStatusSendUploadSucceed = 3,
  /// 消息发送失败
  kJMSGMessageStatusSendFailed = 4,
  /// 消息发送成功
  kJMSGMessageStatusSendSucceed = 5,
  /// 接收中的消息(还在处理)
  kJMSGMessageStatusReceiving = 6,
  /// 接收消息时自动下载媒体失败
  kJMSGMessageStatusReceiveDownloadFailed = 7,
  /// 接收消息成功
  kJMSGMessageStatusReceiveSucceed = 8,
};


/*!
 * 上传文件的类型
 */
typedef NS_ENUM(NSInteger, JMSGFileType) {
  /// 未知的文件类型
  kJMSGFileTypeUnknown,
  /// 图片类型
  kJMSGFileTypeImage,
  /// 语音类型
  kJMSGFileTypeVoice,
};

//NSString *JMSGFileTypeStr(JMSGFileType type) {
//  if (type == kJMSGFileTypeUnknown) {
//    return @"未知文件类型";
//  } else if (type == kJMSGFileTypeImage){
//    return @"图片";
//  } else {
//    return @"语音";
//  }
//}

///----------------------------------------------------
/// @name errors
///----------------------------------------------------

/*!
 * @abstract JMessage SDK 的错误码汇总
 *
 * @discussion 错误码以 86 打头，都为 iOS SDK 内部的错误码
 */
typedef NS_ENUM(NSInteger, JMSGSDKErrorCode) {

  // --------------------- Server

  kJMSGErrorNetworkUserNotRegistered = 801003,
  
  // --------------------- Network (860xxx)

  JMSG_ERROR_NETWORK_REQUEST_INVALIDATE = 860010,
  /// 服务器返回超时
  JMSG_ERROR_NETWORK_REQUEST_TIMEOUT = 860011,
  /// 服务器请求失败
  JMSG_ERROR_NETWORK_REQUEST_FAIL = 860012,
  /// 服务端错误
  JMSG_ERROR_NETWORK_SERVER_FAIL = 860013,
  /// 地址错误
  JMSG_ERROR_NETWORK_HOST_UNKNOWN = 860014,
  /// 下载失败
  kJMSGErrorSDKNetworkDownloadFailed = 860015,
  /// 其他网络原因
  kJMSGNetworkOther = 860016,
  /// 服务器获取用户Token失败
  kJMSGErrorNetworkTokenFailed = 860017,
  /// 上传资源文件失败
  kJMSGErrorSDKNetworkUploadFailed = 860018,
  /// 上传资源文件Token验证失败
  kJMSGErrorSDKNetworkUploadTokenVerifyFailed = 860019,
  /// 获取服务器Token失败
  kJMSGErrorSDKNetworkUploadTokenGetFailed = 860020,
  /// 服务器返回数据错误（没有按约定返回）
  kJMSGErrorNetworkResultUnexpected = 860021,
  /// 服务器端返回数据格式错误
  kJMSGErrorNetworkDataFormatInvalid = 860030,

  // --------------------- DB & Global params (861xxx)

  /// 数据库删除失败 (预期应该成功)
  kJMSGErrorSDKDBDeleteFailed = 861000,
  /// 数据库更新失败 (预期应该成功)
  kJMSGErrorSDKDBUpdateFailed = 861001,
  /// 数据库查询失败 (预期应该成功)
  kJMSGErrorSDKDBSelectFailed = 861002,
  /// 数据库插入失败 (预期应该成功)
  kJMSGErrorSDKDBInsertFailed = 861003,
  /// Appkey 不合法
  kJMSGErrorSDKParamAppkeyInvalid = 861100,
  /// SDK 内部方法参数检查错误
  kJMSGErrorSDKParamInternalInvalid = 860040,

  // ------------------------ Third party (862xxx)

  /// 七牛相关未知错误
  kJMSGErrorPartyQiniuUnknown = 862010,

  // ------------------------ User (863xxx)

  /// 用户名不合法
  kJMSGErrorSDKParamUsernameInvalid = 863001,
  /// 用户密码不合法
  kJMSGErrorSDKParamPasswordInvalid = 863002,
  /// 用户头像属性为空
  kJMSGErrorSDKParamAvatarNil = 86303,
  /// 用户未登录
  kJMSGErrorSDKUserNotLogin = 86304,
  
  // ------------------------ Media Resource (864xxx)

  /// 这不是一条媒体消息
  kJMSGErrorSDKNotMediaMessage = 864001,
  /// 下载媒体资源路径或者数据意外丢失
  kJMSGErrorSDKMediaResourceMissing = 864002,
  /// 媒体CRC码无效
  kJMSGErrorSDKMediaCrcCodeIllegal = 864003,
  /// 媒体CRC校验失败
  kJMSGErrorSDKMediaCrcVerifyFailed = 864004,
  /// 上传媒体文件时, 发现文件不存在
  kJMSGErrorSDKMediaUploadEmptyFile = 864005,

  // ------------------------ Message (865xxx)

  /// 无效的消息内容
  kJMSGErrorSDKParamContentInvalid = 865001,
  /// 空消息
  kJMSGErrorSDKParamMessageNil = 865002,
  /// 消息不符合发送的基本条件检查
  kJMSGErrorSDKMessageNotPrepared = 865003,
  /// 你不是群组成员
  kJMSGErrorSDKMessageNotInGroup = 865004,

  // ------------------------ Conversation (866xxx)

  /// 未知的会话类型
  kJMSGErrorSDKParamConversationTypeUnknown = 866001,
  /// 会话 username 无效
  kJMSGErrorSDKParamConversationUsernameInvalid = 866002,
  /// 会话 groupId 无效
  kJMSGErrorSDKParamConversationGroupIdInvalid = 866003,

  // ------------------------ Group (867xxx)

  /// groupId 无效
  kJMSGErrorSDKParamGroupGroupIdInvalid = 867001,
  /// group 相关字段无效
  kJMSGErrorSDKParamGroupGroupInfoInvalid = 867002,

  // ------------------------ Media (868xxx)

  /// 媒体文件 crc 检查失败
  kJMSGErrorMediaCrcInvalid = 868001,
};

/*!
 * @abstract SDK依赖的内部 HTTP 服务返回的错误码。
 *
 * @discussion 这些错误码也会直接通过 SDK API 返回给应用层。
 */
typedef NS_ENUM(NSUInteger, JMSGHttpErrorCode) {
  /// 服务器端内部错误
  kJMSGErrorHttpServerInternal = 898000,
  /// 用户已经存在
  kJMSGErrorHttpUserExist = 898001,
  /// 用户不存在
  kJMSGErrorHttpUserNotExist = 898002,
  /// 参数无效
  kJMSGErrorHttpPrameterInvalid = 898003,
  /// 密码错误
  kJMSGErrorHttpPasswordError = 898004,
  /// 内部UID 无效
  kJMSGErrorHttpUidInvalid = 898005,
  /// 内部Gid 无效
  kJMSGErrorHttpGidInvalid = 898006,
  /// Http 请求没有验证信息
  kJMSGErrorHttpMissingAuthenInfo = 898007,
  /// Http 请求验证失败
  kJMSGErrorHttpAuthenticationFailed = 898008,
  /// Appkey 不存在
  kJMSGErrorHttpAppkeyNotExist = 898009,
  /// Http 请求 token 过期
  kJMSGErrorHttpTokenExpired = 898010,
  /// 用户未登录
  kJMSGErrorHttpUserNotLoggedIn = 800012,
  /// 服务器端响应超时
  kJMSGErrorHttpServerResponseTimeout = 898030,
  //// 用户不存在
};

/*!
 * @abstract SDK依赖的内部 TCP 服务返回的错误码
 *
 * @discussion 这些错误码也会直接通过 SDK API 返回给应用层。
 */
typedef NS_ENUM(NSUInteger, JMSGTcpErrorCode) {
  kJMSGErrorTcpAppkeyNotRegistered = 800003,
  kJMSGErrorTcpUserIDEmpty = 800004,
  kJMSGErrorTcpUserIDNotRegistered = 800005,
  kJMSGErrorTcpServerInternalError = 800009,
  kJMSGErrorTcpUserLogoutState = 800012,
  kJMSGErrorTcpUserOfflineState = 800013,
};


///----------------------------------------------------
/// @name Global keys 全局静态变量定义
///----------------------------------------------------

// General key

static NSString *const KEY_APP_KEY = @"appkey";


// User

static NSString *const KEY_USERNAME = @"username";
static NSString *const KEY_PASSWORD = @"password";

static NSString *const KEY_NEW_PASSWORD = @"new_password";
static NSString *const KEY_OLD_PASSWORD = @"old_password";

static NSString *const KEY_NICKNAME = @"nickname";
static NSString *const KEY_AVATAR = @"avatar";
static NSString *const KEY_GENDER = @"gender";
static NSString *const KEY_BIRTHDAY = @"birthday";
static NSString *const KEY_REGION = @"region";
static NSString *const KEY_SIGNATURE = @"signature";
static NSString *const KEY_STAR = @"star";
static NSString *const KEY_UID = @"uid";
static NSString *const KEY_ADDRESS = @"address";


#endif

