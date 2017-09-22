//
//  BeautySettingPanel.m
//  RTMPiOSDemo
//
//  Created by rushanting on 2017/5/5.
//  Copyright © 2017年 tencent. All rights reserved.
//

#import "BeautySettingPanel.h"
#import "V8HorizontalPickerView.h"
#import "TXUGCRecord.h"
#import "TXLivePush.h"



@interface BeautySettingPanel ()<V8HorizontalPickerViewDelegate, V8HorizontalPickerViewDataSource>
{
    float  _beauty_level;
    float  _whitening_level;
    float  _eye_level;
    float  _face_level;
    NSInteger    _filterType;
    NSInteger    _greenType;
    NSInteger    _motionType;
    NSMutableArray* _filterArray;
    V8HorizontalPickerView* _vhPickerView;
    V8HorizontalPickerView* _vhPickerGreenView;
    V8HorizontalPickerView* _vhMotionTmplView;
    
    UISlider*  _sdBeauty;
    UISlider* _sdWhitening;
    UISlider* _sdBigEye;
    UISlider* _sdSlimFace;
}


@end

@implementation BeautySettingPanel


- (id)initWithFrame:(CGRect)frame
{
    CGSize size = [UIScreen mainScreen].bounds.size;
    frame = CGRectMake(0, size.height-250, size.width, 250);
    if (self = [super initWithFrame:frame]) {
        [self initUI];
    }
    return self;
 
}

- (void)initUI
{

    //美颜拉杆浮层
    CGSize size = [UIScreen mainScreen].bounds.size;

    _filterArray = [NSMutableArray arrayWithObjects:@"无滤镜",@"美白", @"浪漫", @"清新", @"唯美", @"粉嫩", @"怀旧", @"蓝调", @"清凉", @"日系", nil];
    
    [self setBackgroundColor:[UIColor whiteColor]];
    
    UILabel* txtBeauty = [[UILabel alloc]init];
    txtBeauty.frame = CGRectMake(20, 15, 150, 150);
    [txtBeauty setText:@"美颜效果"];
    [txtBeauty setFont:[UIFont fontWithName:@"" size:14]];
    [txtBeauty sizeToFit];
    
    _sdBeauty = [[UISlider alloc] init];
    _sdBeauty.frame = CGRectMake(txtBeauty.frame.origin.x + txtBeauty.frame.size.width + 10, 0, size.width - txtBeauty.frame.origin.x - txtBeauty.frame.size.width - 40, 50);
    _sdBeauty.minimumValue = 0;
    _sdBeauty.maximumValue = 9;
    _sdBeauty.value = 6.3;
    _sdBeauty.center = CGPointMake(_sdBeauty.center.x, txtBeauty.center.y);
    
    [_sdBeauty setThumbImage:[UIImage imageNamed:@"circle"] forState:UIControlStateNormal];
    [_sdBeauty setMinimumTrackTintColor:[UIColor blackColor]];
    [_sdBeauty setMaximumTrackTintColor:[UIColor blackColor]];
    [_sdBeauty addTarget:self action:@selector(sliderValueChange:) forControlEvents:UIControlEventValueChanged];
    _sdBeauty.tag = 0;
    
    UILabel* txtWhitening = [[UILabel alloc] init];
    txtWhitening.frame = CGRectMake(20, txtBeauty.frame.origin.y + txtBeauty.frame.size.height + 15, 150, 150);
    [txtWhitening setText:@"美白效果"];
    [txtWhitening setFont:[UIFont fontWithName:@"" size:14]];
    [txtWhitening sizeToFit];
    
    _sdWhitening = [[UISlider alloc] init];
    _sdWhitening.frame = CGRectMake(txtWhitening.frame.origin.x + txtWhitening.frame.size.width + 10, 0, size.width - txtWhitening.frame.origin.x - txtWhitening.frame.size.width - 40, 50);
    _sdWhitening.minimumValue = 0;
    _sdWhitening.maximumValue = 9;
    _sdWhitening.value = 2.7;
    _sdWhitening.center = CGPointMake(_sdWhitening.center.x, txtWhitening.center.y);
    
    [_sdWhitening setThumbImage:[UIImage imageNamed:@"circle"] forState:UIControlStateNormal];
    [_sdWhitening setMinimumTrackTintColor:[UIColor blackColor]];
    [_sdWhitening setMaximumTrackTintColor:[UIColor blackColor]];
    [_sdWhitening addTarget:self action:@selector(sliderValueChange:) forControlEvents:UIControlEventValueChanged];
    _sdWhitening.tag = 1;
    
    UILabel* txtBigEye = [[UILabel alloc] init];
    txtBigEye.frame = CGRectMake(20, txtWhitening.frame.origin.y + txtWhitening.frame.size.height + 15, 150, 150);
    [txtBigEye setText:@"大眼效果"];
    [txtBigEye setFont:[UIFont fontWithName:@"" size:14]];
    [txtBigEye sizeToFit];
    
    _sdBigEye = [[UISlider alloc] init];
    _sdBigEye.frame = CGRectMake(txtBigEye.frame.origin.x + txtBigEye.frame.size.width + 10, 0, size.width - txtBigEye.frame.origin.x - txtBigEye.frame.size.width - 40, 50);
    _sdBigEye.minimumValue = 0;
    _sdBigEye.maximumValue = 9;
    _sdBigEye.center = CGPointMake(_sdBigEye.center.x, txtBigEye.center.y);
    
    [_sdBigEye setThumbImage:[UIImage imageNamed:@"circle"] forState:UIControlStateNormal];
    [_sdBigEye setMinimumTrackTintColor:[UIColor blackColor]];
    [_sdBigEye setMaximumTrackTintColor:[UIColor blackColor]];
    [_sdBigEye addTarget:self action:@selector(sliderValueChange:) forControlEvents:UIControlEventValueChanged];
    _sdBigEye.tag = 2;
    
    UILabel* txtSlimFace = [[UILabel alloc] init];
    txtSlimFace.frame = CGRectMake(20, txtBigEye.frame.origin.y + txtBigEye.frame.size.height + 15, 150, 150);
    [txtSlimFace setText:@"瘦脸效果"];
    [txtSlimFace setFont:[UIFont fontWithName:@"" size:14]];
    [txtSlimFace sizeToFit];
    
    _sdSlimFace = [[UISlider alloc] init];
    _sdSlimFace.frame = CGRectMake(txtSlimFace.frame.origin.x + txtSlimFace.frame.size.width + 10, 0, size.width - txtSlimFace.frame.origin.x - txtSlimFace.frame.size.width - 40, 50);
    _sdSlimFace.minimumValue = 0;
    _sdSlimFace.maximumValue = 9;
    _sdSlimFace.center = CGPointMake(_sdSlimFace.center.x, txtSlimFace.center.y);
    
    [_sdSlimFace setThumbImage:[UIImage imageNamed:@"circle"] forState:UIControlStateNormal];
    [_sdSlimFace setMinimumTrackTintColor:[UIColor blackColor]];
    [_sdSlimFace setMaximumTrackTintColor:[UIColor blackColor]];
    [_sdSlimFace addTarget:self action:@selector(sliderValueChange:) forControlEvents:UIControlEventValueChanged];
    _sdSlimFace.tag = 3;
    
    
    _vhPickerView = [[V8HorizontalPickerView alloc] initWithFrame:CGRectMake(50,  txtSlimFace.frame.origin.y + txtSlimFace.frame.size.height + 5, size.width - 40, 30)];
    _vhPickerView.selectedTextColor = [UIColor blackColor];
    _vhPickerView.textColor = [UIColor grayColor];
    _vhPickerView.elementFont = [UIFont fontWithName:@"" size:14];
    _vhPickerView.delegate = self;
    _vhPickerView.dataSource = self;
    
    _vhPickerGreenView = [[V8HorizontalPickerView alloc] initWithFrame:CGRectMake(50,  txtSlimFace.frame.origin.y + txtSlimFace.frame.size.height + _vhPickerView.frame.size.height + 5, size.width - 150, 30)];
    _vhPickerGreenView.selectedTextColor = [UIColor blackColor];
    _vhPickerGreenView.textColor = [UIColor grayColor];
    _vhPickerGreenView.elementFont = [UIFont fontWithName:@"" size:14];
    _vhPickerGreenView.delegate = self;
    _vhPickerGreenView.dataSource = self;
    
    _vhMotionTmplView = [[V8HorizontalPickerView alloc] initWithFrame:CGRectMake(50,  txtSlimFace.frame.origin.y + txtSlimFace.frame.size.height + _vhPickerView.frame.size.height + _vhPickerGreenView.frame.size.height + 5, size.width - 100, 30)];
    _vhMotionTmplView.selectedTextColor = [UIColor blackColor];
    _vhMotionTmplView.textColor = [UIColor grayColor];
    _vhMotionTmplView.elementFont = [UIFont fontWithName:@"" size:14];
    _vhMotionTmplView.delegate = self;
    _vhMotionTmplView.dataSource = self;
    
    [self addSubview:txtBeauty];
    [self addSubview:_sdBeauty];
    [self addSubview:txtWhitening];
    [self addSubview:_sdWhitening];
    [self addSubview:txtBigEye];
    [self addSubview:_sdBigEye];
    [self addSubview:txtSlimFace];
    [self addSubview:_sdSlimFace];
    [self addSubview:_vhPickerView];
    [self addSubview:_vhPickerGreenView];
    [self addSubview:_vhMotionTmplView];
    
}

- (void)layoutSubviews
{
    [super layoutSubviews];
    [self resetValues];
}


#pragma mark - HorizontalPickerView DataSource Methods
- (NSInteger)numberOfElementsInHorizontalPickerView:(V8HorizontalPickerView *)picker {
    if (picker == _vhPickerGreenView)
        return 2;
    if (picker == _vhMotionTmplView)
        return 3;
    return [_filterArray count];
}

#pragma mark - HorizontalPickerView Delegate Methods
- (NSString *)horizontalPickerView:(V8HorizontalPickerView *)picker titleForElementAtIndex:(NSInteger)index {
    if (picker == _vhPickerGreenView)
        return @[@"无绿幕",@"绿幕1"][index];
    if (picker == _vhMotionTmplView)
        return @[@"无动效",@"动效1",@"动效2"][index];
    
    return [_filterArray objectAtIndex:index];
}

- (NSInteger) horizontalPickerView:(V8HorizontalPickerView *)picker widthForElementAtIndex:(NSInteger)index {
    CGSize constrainedSize = CGSizeMake(MAXFLOAT, MAXFLOAT);
    NSString *text = [_filterArray objectAtIndex:index];
    CGSize textSize = [text sizeWithFont:[UIFont boldSystemFontOfSize:14.0f]
                       constrainedToSize:constrainedSize
                           lineBreakMode:NSLineBreakByWordWrapping];
    return textSize.width + 40.0f; // 20px padding on each side
}

- (void)horizontalPickerView:(V8HorizontalPickerView *)picker didSelectElementAtIndex:(NSInteger)index {
    if (picker == _vhPickerGreenView) {
        if (index == 0) {
            [self.delegate onSetGreenScreenFile:nil];
        }
        if (index == 1) {
            [self.delegate onSetGreenScreenFile:[[NSBundle mainBundle] URLForResource:@"goodluck" withExtension:@"mp4"]];
            
        }
        _greenType = index;
        return;
    }
    if (picker == _vhMotionTmplView) {
        NSString *localPackageDir = [[[NSBundle mainBundle] bundlePath] stringByAppendingPathComponent:@"Resource"];
        if (index == 0)
        {
            [self.delegate onSelectMotionTmpl:nil inDir:localPackageDir];

        }
        if (index == 1)
        {
            [self.delegate onSelectMotionTmpl:@"video_rabbit" inDir:localPackageDir];
            
        }
        if (index == 2)
        {
            [self.delegate onSelectMotionTmpl:@"video_snow_white" inDir:localPackageDir];
        }
        _motionType = index;
        return;
    }
    _filterType = index;
    [self setFilter:index];
    
    
}

- (void)setFilter:(NSInteger) index
{
    NSString* lookupFileName = @"";
    
    switch (index) {
        case FilterType_None:
            break;
        case FilterType_white:
            lookupFileName = @"white.png";
            break;
        case FilterType_langman:
            lookupFileName = @"langman.png";
            break;
        case FilterType_qingxin:
            lookupFileName = @"qingxin.png";
            break;
        case FilterType_weimei:
            lookupFileName = @"weimei.png";
            break;
        case FilterType_fennen:
            lookupFileName = @"fennen.png";
            break;
        case FilterType_huaijiu:
            lookupFileName = @"huaijiu.png";
            break;
        case FilterType_landiao:
            lookupFileName = @"landiao.png";
            break;
        case FilterType_qingliang:
            lookupFileName = @"qingliang.png";
            break;
        case FilterType_rixi:
            lookupFileName = @"rixi.png";
            break;
        default:
            break;
    }
    NSString * path = [[NSBundle mainBundle] pathForResource:@"FilterResource" ofType:@"bundle"];
    if (path != nil && index != FilterType_None) {
        path = [path stringByAppendingPathComponent:lookupFileName];
        UIImage *image = [UIImage imageWithContentsOfFile:path];
        [self.delegate onSetFilter:image];
        
    } else {
        [self.delegate onSetFilter:nil];
    }
}

-(void) sliderValueChange:(UISlider*) obj
{
    // todo
    if (obj.tag == 0) { //美颜
        _beauty_level = obj.value;
        
        [self.delegate onSetBeautyDepth:_beauty_level WhiteningDepth:_whitening_level];
        
    } else if (obj.tag == 1) { //美白
        _whitening_level = obj.value;
        [self.delegate onSetBeautyDepth:_beauty_level WhiteningDepth:_whitening_level];
        
    }else if (obj.tag == 2) { //大眼
        _eye_level = obj.value;
        [self.delegate onSetEyeScaleLevel:_eye_level];
        
    }else if (obj.tag == 3) { //瘦脸
        _face_level = obj.value;
        [self.delegate onSetFaceScaleLevel:_face_level];
        
    }
}

- (void)resetValues
{
    _beauty_level = 6.3;
    _whitening_level = 2.7;
    _eye_level = 0;
    _face_level = 0;
    _filterType = 1;
    _greenType = 0;
    _motionType = 0;
    
    [self setSliderValue:_sdBeauty value:_beauty_level];
    [self setSliderValue:_sdWhitening value:_whitening_level];
    [self setSliderValue:_sdBigEye value:_eye_level];
    [self setSliderValue:_sdSlimFace value:_face_level];
    
    [_vhPickerView scrollToElement:_filterType animated:NO];
    [_vhPickerGreenView scrollToElement:_greenType animated:NO];
    [_vhMotionTmplView scrollToElement:_motionType animated:NO];
}

- (void)setSliderValue:(UISlider*)slider value:(float)value
{
//    if (slider.value - value < 0.000001)
//        return;
    
    slider.value = value;
    [self sliderValueChange:slider];
}

@end
