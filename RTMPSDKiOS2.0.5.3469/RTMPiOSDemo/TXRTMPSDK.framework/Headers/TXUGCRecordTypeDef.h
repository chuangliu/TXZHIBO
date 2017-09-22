#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/*
 * PlayRecord 录制类型定义
 */
typedef NS_ENUM(NSInteger, TXRecordType)
{
    RECORD_TYPE_STREAM_SOURCE                       = 1,            //视频源为正在播放的视频流
};

/*
 * CameraRecord 录制视频质量类型
 */
typedef NS_ENUM(NSInteger, TXVideoQuality)
{
    VIDEO_QUALITY_LOW                               = 0,            //resolution  360×640     fps 20   bitrate 600
    VIDEO_QUALITY_MEDIUM                            = 1,            //resolution  540×960     fps 20   bitrate 1200
    VIDEO_QUALITY_HIGH                              = 2,            //resolution  720×1280    fps 20   bitrate 2400
};

/*
 * CameraRecord 录制分辨率类型定义
 */
typedef NS_ENUM(NSInteger, TXVideoResolution)
{
    VIDEO_RESOLUTION_360_640                  = 0,
    VIDEO_RESOLUTION_540_960                  = 1,
    VIDEO_RESOLUTION_720_1280                 = 2,
};


/*
 * 录制参数定义
 */

@interface TXUGCSimpleConfig : NSObject
@property (nonatomic, assign) TXVideoQuality        videoQuality;        //录制视频质量
@property (nonatomic, retain) UIImage *             watermark;           //设置水印图片. 设为nil等同于关闭水印
@property (nonatomic, assign) CGPoint               watermarkPos;        //设置水印图片位置
@property (nonatomic, assign) BOOL                  frontCamera;         //是否是前置摄像头
@end

@interface TXUGCCustomConfig : NSObject
@property (nonatomic, assign) TXVideoResolution     videoResolution;     //自定义分辨率
@property (nonatomic, assign) int                   videoFPS;            //自定义fps   15~30
@property (nonatomic, assign) int                   videoBitratePIN;     //自定义码率   600~2400
@property (nonatomic, retain) UIImage *             watermark;           //设置水印图片. 设为nil等同于关闭水印
@property (nonatomic, assign) CGPoint               watermarkPos;        //设置水印图片位置
@property (nonatomic, assign) BOOL                  frontCamera;         //是否是前置摄像头
@end


/*
 * 录制结果错误码定义
 */
typedef NS_ENUM(NSInteger, TXRecordResultCode)
{
    RECORD_RESULT_OK                                = 0,    //录制成功（业务层主动结束录制）
    RECORD_RESULT_OK_INTERRUPT                      = 1,    //录制成功（sdk自动结束录制，可能原因：1，app进入后台，2，app被闹钟或电话打断，3，网络断连接）
    RECORD_RESULT_FAILED                            = 1001, //录制失败
};


/*
 * 录制结果
 */
@interface TXRecordResult : NSObject
@property (nonatomic, assign) TXRecordResultCode    retCode;        //错误码
@property (nonatomic, strong) NSString*             descMsg;        //错误描述信息
@property (nonatomic, strong) NSString*             videoPath;      //视频文件path
@property (nonatomic, strong) UIImage*              coverImage;     //视频封面
@end



////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * 短视频发布结果错误码定义，短视频发布流程分为三步
 *    step1: 请求上传文件
 *    step2: 上传文件
 *    step3: 请求发布短视频
 */
typedef NS_ENUM(NSInteger, TXPublishResultCode)
{
    PUBLISH_RESULT_OK                               = 0,            //发布成功
    PUBLISH_RESULT_UPLOAD_REQUEST_FAILED            = 1001,         //step1: “文件上传请求”发送失败
    PUBLISH_RESULT_UPLOAD_RESPONSE_ERROR            = 1002,         //step1: “文件上传请求”收到错误响应
    PUBLISH_RESULT_UPLOAD_VIDEO_FAILED              = 1003,         //step2: “视频文件”上传失败
    PUBLISH_RESULT_UPLOAD_COVER_FAILED              = 1004,         //step2: “封面文件”上传失败
    PUBLISH_RESULT_PUBLISH_REQUEST_FAILED           = 1005,         //step3: “短视频发布请求”发送失败
    PUBLISH_RESULT_PUBLISH_RESPONSE_ERROR           = 1006,         //step3: “短视频发布请求”收到错误响应
};

/*
 * 短视频发布参数
 */
@interface TXPublishParam : NSObject
@property (nonatomic, strong) NSString*             secretId;             //secretId，废弃的参数，不用填
@property (nonatomic, strong) NSString*             signature;            //signatuer
@property (nonatomic, strong) UIImage *             coverImage;           //封面图，如果为nil，SDK会自动截取封面图
@property (nonatomic, strong) NSString*             videoPath;            //videoPath
@property (nonatomic, assign) BOOL                  enableHTTPS;          //开启HTTPS，默认开启
@end


/*
 * 短视频发布结果
 */
@interface TXPublishResult : NSObject
@property (nonatomic, assign) int                   retCode;        //错误码
@property (nonatomic, strong) NSString*             descMsg;        //错误描述信息
@property (nonatomic, strong) NSString*             videoId;        //视频文件id
@property (nonatomic, strong) NSString*             videoURL;       //视频播放地址
@property (nonatomic, strong) NSString*             coverURL;       //封面存储地址
@end


/*
 * 视频信息
 */
@interface TXVideoInfo : NSObject
@property (nonatomic, strong) UIImage*              coverImage;     //视频首帧图片
@property (nonatomic, assign) CGFloat               duration;       //视频时长(s)
@property (nonatomic, assign) unsigned long long    fileSize;       //视频大小(byte)
@property (nonatomic, assign) int                   fps;            //视频fps
@property (nonatomic, assign) int                   bitrate;        //视频码率 (kbps)
@property (nonatomic, assign) int                   audioSampleRate;//音频采样率
@property (nonatomic, assign) int                   width;          //视频宽度
@property (nonatomic, assign) int                   height;         //视频高度
@end


/*
 * 短视频预览参数
 */
typedef NS_ENUM(NSInteger, TXPreviewRenderMode)
{
    PREVIEW_RENDER_MODE_FILL_SCREEN                 = 0,            //填充模式，尽可能充满屏幕不留黑边，所以可能会裁剪掉一部分画面
    PREVIEW_RENDER_MODE_FILL_EDGE                   = 1,            //黑边模式，尽可能保持画面完整，但当宽高比不合适时会有黑边出现
};

/*
 * 短视频预览参数
 */
@interface TXPreviewParam : NSObject
@property (nonatomic, strong) UIView*               videoView;      //视频预览View
@property (nonatomic, assign) TXPreviewRenderMode   renderMode;     //填充模式

@end


///////////////////////////////////////////////////////////////////////////////////
/*
 * 字幕
 */
@interface TXSubtitle: NSObject
@property (nonatomic, strong) UIImage*              titleImage;     //字幕图片   （这里需要客户把承载文字的控件转成image图片）
@property (nonatomic, assign) CGRect                frame;          //字幕的frame（注意这里的frame坐标是相对于渲染view的坐标）
@property (nonatomic, assign) CGFloat               startTime;      //字幕起始时间(s)
@property (nonatomic, assign) CGFloat               endTime;        //字幕结束时间(s)
@end

//////////////////////////////////////////////////////////////////////////////////////

/*
 * 生成视频结果错误码定义
 */
typedef NS_ENUM(NSInteger, TXGenerateResultCode)
{
    GENERATE_RESULT_OK                                   = 0,       //生成视频成功
    GENERATE_RESULT_FAILED                               = -1,      //生成视频失败
};

/*
 * 生成视频结果
 */
@interface TXGenerateResult : NSObject
@property (nonatomic, assign) TXGenerateResultCode  retCode;        //错误码
@property (nonatomic, strong) NSString*             descMsg;        //错误描述信息
@end

/*
 * 视频合成结果错误码定义
 */
typedef NS_ENUM(NSInteger, TXJoinerResultCode)
{
    JOINER_RESULT_OK                                = 0,            //合成成功
    JOINER_RESULT_FAILED                            = -1,           //合成失败
};
/*
 * 短视频合成结果
 */
@interface TXJoinerResult : NSObject
@property (nonatomic, assign) TXJoinerResultCode    retCode;         //错误码
@property (nonatomic, strong) NSString*             descMsg;         //错误描述信息

/*
 * 短视频压缩质量
 * 注意如果视频的分辨率小于压缩到的目标分辨率，视频不会被压缩，会保留原画
 */
typedef NS_ENUM(NSInteger, TXVideoCompressed)
{
    VIDEO_COMPRESSED_480P                              = 0,  //压缩至480P分辨率
    VIDEO_COMPRESSED_540P                              = 1,  //压缩至540P分辨率
    VIDEO_COMPRESSED_720P                              = 2,  //压缩至720P分辨率
};


@end
