//
//  BeautySettingPanel.h
//  RTMPiOSDemo
//
//  Created by rushanting on 2017/5/5.
//  Copyright © 2017年 tencent. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "TXLivePush.h"

typedef NS_ENUM(NSInteger,DemoFilterType) {
    FilterType_None 		= 0,
    FilterType_white        ,   //美白滤镜
    FilterType_langman 		,   //浪漫滤镜
    FilterType_qingxin 		,   //清新滤镜
    FilterType_weimei 		,   //唯美滤镜
    FilterType_fennen 		,   //粉嫩滤镜
    FilterType_huaijiu 		,   //怀旧滤镜
    FilterType_landiao 		,   //蓝调滤镜
    FilterType_qingliang    ,   //清凉滤镜
    FilterType_rixi 		,   //日系滤镜
};

@protocol BeautySettingPanelDelegate <NSObject>

- (void)onSetBeautyDepth:(float)beautyDepth WhiteningDepth:(float)whiteningDepth;
- (void)onSetEyeScaleLevel:(float)eyeScaleLevel;
- (void)onSetFaceScaleLevel:(float)faceScaleLevel;
- (void)onSetFilter:(UIImage*)filterImage;
- (void)onSetGreenScreenFile:(NSURL *)file;
- (void)onSelectMotionTmpl:(NSString *)tmplName inDir:(NSString *)tmplDir;

@end

@interface BeautySettingPanel : UIView

@property (nonatomic, weak) id<BeautySettingPanelDelegate> delegate;

- (void)resetValues;

@end
