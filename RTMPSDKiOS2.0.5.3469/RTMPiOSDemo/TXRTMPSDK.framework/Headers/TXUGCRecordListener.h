#import "TXUGCRecordTypeDef.h"


/**********************************************
 **************  短视频录制回调定义  **************
 **********************************************/
@protocol TXVideoRecordListener <NSObject>

/**
 * 短视频录制进度
 */
@optional
-(void) onRecordProgress:(NSInteger)milliSecond;

/**
 * 短视频录制完成
 */
@optional
-(void) onRecordComplete:(TXRecordResult*)result;

/**
 * 短视频录制事件通知
 */
@optional
-(void) onRecordEvent:(NSDictionary*)evt;

@end


/**********************************************
 **************  短视频发布回调定义  **************
 **********************************************/
@protocol TXVideoPublishListener <NSObject>
/**
 * 短视频发布进度
 */
@optional
-(void) onPublishProgress:(NSInteger)uploadBytes totalBytes: (NSInteger)totalBytes;

/**
 * 短视频发布完成
 */
@optional
-(void) onPublishComplete:(TXPublishResult*)result;

/**
 * 短视频发布事件通知
 */
@optional
-(void) onPublishEvent:(NSDictionary*)evt;

@end

/**********************************************
 **************  视频预览回调  **************
 **********************************************/
@protocol TXVideoPreviewListener <NSObject>

/**
 * 短视频预览进度
 * time 视频预览的当前时间 (s)
 */
@optional
-(void) onPreviewProgress:(CGFloat)time;

/**
 * 短视频预览结束回调
 */
@optional
-(void) onPreviewFinished;

@end


/**********************************************
 **************  视频生成回调  **************
 **********************************************/
@protocol TXVideoGenerateListener<NSObject>
/**
 * 短视频生成完成
 * progress 生成视频进度百分比
 */
@optional
-(void) onGenerateProgress:(float)progress;

/**
 * 短视频生成完成
 */
@optional
-(void) onGenerateComplete:(TXGenerateResult *)result;

@end


/**********************************************
 **************  视频合成回调  **************
 **********************************************/
@protocol TXVideoJoinerListener<NSObject>
/**
 * 短视频合成完成
 * progress 合成视频进度百分比
 */
@optional
-(void) onJoinProgress:(float)progress;

/**
 * 短视频合成完成
 */
@optional
-(void) onJoinComplete:(TXJoinerResult *)result;


@end
