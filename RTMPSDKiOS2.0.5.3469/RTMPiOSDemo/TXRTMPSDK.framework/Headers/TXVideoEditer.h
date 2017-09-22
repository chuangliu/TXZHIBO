//
//  TXUGCEdit.h
//  TXRTMPSDK
//
//  Created by xiang zhang on 2017/4/10.
//
//

#import <Foundation/Foundation.h>
#import <CoreMedia/CoreMedia.h>
#import <UIKit/UIKit.h>
#import "TXUGCRecordListener.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////  UGC list /////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

@interface TXVideoInfoReader : NSObject
/*
 * number 当前采样的是第几张图片（number 从1开始）
 * image  当前采样图片
 */
typedef void(^sampleProcess)(int number , UIImage * image);

/* 获取视频文件信息
 * videoPath 视频文件路径
 */
+ (TXVideoInfo *)getVideoInfo:(NSString *)videoPath;

/*获取视频的采样图列表
 *count         获取的采样图数量（均匀采样）
 *videoPath     视频文件路径
 *sampleProcess 采样进度
 */
+ (void)getSampleImages:(int)count
              videoPath:(NSString *)videoPath
               progress:(sampleProcess)sampleProcess;
@end


////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////  Video Edit //////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

@interface TXVideoEditer : NSObject
@property (nonatomic ,weak) id<TXVideoGenerateListener> generateDelegate;
@property (nonatomic ,weak) id<TXVideoPreviewListener>  previewDelegate;

- (instancetype)initWithPreview:(TXPreviewParam *)param;

/*
 *videoPath:视频文件路径
 * 返回值：
 *       0 成功；
 *      -1 视频文件不存在；
 */
- (int)setVideoPath:(NSString *)videoPath;


/*渲染某一时刻的视频画面
 *time      预览帧时间(s)
 */
- (void)previewAtTime:(CGFloat)time;

/*播放某一时间段的视频
 *startTime     播放起始时间(s)
 *endTime       播放结束时间(s)
 */
- (void)startPlayFromTime:(CGFloat)startTime
                   toTime:(CGFloat)endTime;

/*
 *暂停播放
 */
- (void)pausePlay;


/*继续播放
 */
- (void)resumePlay;

/*停止播放
 */
- (void)stopPlay;

/*
 *设置美颜，美白级别
 */

- (void) setBeautyFilter:(float)beautyLevel setWhiteningLevel:(float)whiteningLevel;

/*
 *设置水印
 *waterMark            水印图片
 *normalizationFrame   相对于视频图像的归一化frame，x,y,width,height 取值范围 0~1
 */
- (void) setWaterMark:(UIImage *)waterMark  normalizationFrame:(CGRect)normalizationFrame;

/*
 *设置特效滤镜
 */
- (void) setFilter:(UIImage *)image;

/*
 *设置视频加速播级别
 *level  1.0 ~ 4.0  1.0表示原速，4.0表示4倍加速
 */
- (void) setSpeedLevel:(float)level;

/*
 *设置背景音乐，可以选取音乐的起始时间和结束时间
 *path      音乐文件路径
 *startTime 音乐起始时间
 *endTime   音乐结束时间
 *注意：背景音乐的音频采样率要和视频的音频采样率保持一致，否则可能造成背景音乐播放声音变质，这个我们会在后续版本做下优化，敬请期待。。。
 */
- (void) setBGM:(NSString *)path startTime:(float)startTime endTime:(float)endTime;

/*
 *设置视频声音大小
 *volume 0 ~ 1.0
 */
- (void) setVideoVolume:(float)volume;

/*
 *设置背景音乐声音大小  
 *volume 0 ~ 1.0
 */
- (void) setBGMVolume:(float)volume;

/*
 *设置字幕列表
 *subtitleList 字幕列表
 */
- (void) setSubtitleList:(NSArray<TXSubtitle *> *)subtitleList;


/*
 *设置视频剪裁
 *startTime 视频起始时间
 *endTime   视频结束时间
 */
- (void) setCutFromTime:(float)startTime toTime:(float)endTime;

/*
 *根据操作列表生成最终视频文件
 *videoCompressed 视频压缩质量
 *videoOutputPath 视频操作之后存储路径
 *generateVideo 之后在TXVideoGenerateListener里面监听结果回调
 */
- (void) generateVideo:(TXVideoCompressed)videoCompressed videoOutputPath:(NSString *)videoOutputPath;

/*
 *停止视频文件生成
 */
- (void) cancelGenerate;
@end

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////  UGC Joiner //////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

@interface TXVideoJoiner : NSObject
@property (nonatomic ,weak) id<TXVideoJoinerListener>  joinerDelegate;
@property (nonatomic ,weak) id<TXVideoPreviewListener> previewDelegate;

/*
 * param:参考 TXPreviewParam
 */
- (instancetype)initWithPreview:(TXPreviewParam *)param;

/*
 *videoPathList  :视频列表文件
 * 返回值：
 *       0 成功；
 *      -1 视频列表文件不存在；
 */
- (int)setVideoPathList:(NSArray *)videoPathList;

/* 开启视频播放，会从视频的起始位置开始播放 （需要在setVideoPathList之后调用）
 */
- (void)startPlay;

/*暂停播放
 */
- (void)pausePlay;

/*继续播放
 */
- (void)resumePlay;

/*停止播放
 */
- (void)stopPlay;

/*合成视频
 *videoCompressed 视频压缩质量
 *videoOutputPath 生成新的视频存储路径
 *joinVideo之后在TXVideoComposeListener里面监听结果回调
 *提醒：1，暂不支持不同分辨率的视频合成
 *     2，暂不支持不同音频采样率的视频合成
 *     3，需要合成的视频列表中，每个视频必须要有video data 和 audio data 数据
 */
- (void)joinVideo:(TXVideoCompressed)videoCompressed  videoOutputPath:(NSString *)videoOutputPath;

/*
 *停止视频文件合成
 */
- (void)cancelJoin;

@end



