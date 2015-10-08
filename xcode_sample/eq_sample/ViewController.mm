//
//  ViewController.m
//  eq_sample
//
//  Created by sohn on 13-7-2.
//  Copyright (c) 2013年 Han.zhihong. All rights reserved.
//

#import "ViewController.h"
#include "CzhEaglUIView.h"
#include "CzhEaglUILabel.h"
#include "CzhEaglUILine.h"
#include "CzhEaglUICurve.h"
#include "CzhEaglUIButton.h"

@interface ViewController ()
{
    //C++变量
    CzhEaglUIView gl_img;
    CzhEaglUIView gl_img2;
    CzhEaglUIView*pppv;
    CzhEaglUIView*pppv2;
    
    CzhEaglFont font,font2;
    CzhEaglUILabel lb;
    
    CzhEaglUILine line;
    CzhEaglUICurve curve;

    CzhEaglUIButton btn;
}

@end

@implementation ViewController


- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    
   //--------------------------------------------------------
    
    
    v.delegate=self;
    [v startAnimation];
    v.eyeContex_z=5;
    
    NSString*p;
    p=[[NSBundle mainBundle] pathForResource:@"11.jpg" ofType:nil];
    gl_img.setBackgroundImageByJPG([p UTF8String]);
    gl_img.setLeft(400);
    
    p=[[NSBundle mainBundle] pathForResource:@"bluetex.png" ofType:nil];
    gl_img2.setBackgroundImageByPNG([p UTF8String]);
    gl_img2.setLeft(500);
    
    //加载字体
    p=[[NSBundle mainBundle] pathForResource:@"华文楷体.ttf" ofType:nil];
    font.init([p UTF8String], 30, 0);
    p=[[NSBundle mainBundle] pathForResource:@"简娃娃篆.ttf" ofType:nil];
    font2.init([p UTF8String], 30, 0);
    
    //设置标签
    wchar_t uuu[1024];
    lb.setFont(&font2);
    lb.setTop(230);
    lb.setLeft(400);
    lb.setFontColor(1, 1, 1);
    lb.setAlpha(0.9f);

    lb.setString(L"Yyeah~QWERTYuio唉.终于搞定啦kL;'ZXCM<>.");
    charToWchar(@"yeah~我是加载字体的例子-.-" , uuu);
    lb.setCharacters(uuu, wcslen(uuu));

    //font.destory();
    //font2.destory();
    
    line.setLine(-100, -100, 100, 100);
    line.setLineColor(1, 0,0);
    line.setLineSize(10);
    line.setAngle(0);
    line.setTop(500);
    line.setLeft(150);
    line.alpha=0.8f;
    
    curve.setTop(500);
    curve.setLeft(500);
    curve.setLineSize(2);
    curve.setLineColor(0, 1, 0);
    
    btn.setTop(600);
    btn.setTitle(L"我是按钮", ezhEaglBtnStateNor);
    btn.setTitleColor(1, 0, 0, ezhEaglBtnStateHight);
    btn.setTitlteSize(25, ezhEaglBtnStateHight);
}


-(void)dealloc
{
    [super dealloc];

}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return
    (interfaceOrientation == UIDeviceOrientationLandscapeLeft )||
    (interfaceOrientation == UIDeviceOrientationLandscapeRight );
}
-(BOOL)shouldAutorotate{
    return YES;
}
-(NSInteger)supportedInterfaceOrientations{
    NSInteger orientationMask = 0;
    if ([self shouldAutorotateToInterfaceOrientation: UIInterfaceOrientationLandscapeLeft])
        orientationMask |= UIInterfaceOrientationMaskLandscapeLeft;
    if ([self shouldAutorotateToInterfaceOrientation: UIInterfaceOrientationLandscapeRight])
        orientationMask |= UIInterfaceOrientationMaskLandscapeRight;
    if ([self shouldAutorotateToInterfaceOrientation: UIInterfaceOrientationPortrait])
        orientationMask |= UIInterfaceOrientationMaskPortrait;
    if ([self shouldAutorotateToInterfaceOrientation: UIInterfaceOrientationPortraitUpsideDown])
        orientationMask |= UIInterfaceOrientationMaskPortraitUpsideDown;
    return orientationMask;
}
- (void)willRotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration
{
    NSLog(@"to Rotate=%d",toInterfaceOrientation);
    switch (toInterfaceOrientation) {
        case UIInterfaceOrientationPortrait:
            break;
        case UIInterfaceOrientationPortraitUpsideDown:
            break;
        case UIInterfaceOrientationLandscapeLeft:
            break;
        case UIInterfaceOrientationLandscapeRight:
            break;
    }
}
- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation
{
    NSLog(@"From Rotate=%d",fromInterfaceOrientation);
    switch (fromInterfaceOrientation) {
        case UIInterfaceOrientationPortrait:
            break;
        case UIInterfaceOrientationPortraitUpsideDown:
            break;
        case UIInterfaceOrientationLandscapeLeft:
            break;
        case UIInterfaceOrientationLandscapeRight:
            break;
    }
}

-(IBAction)sideLine_change:(id)sender
{
    UISlider*s=(UISlider*)sender;
    switch (s.tag) {
        case 1:
            line.setAngle(s.value);
            break;
            
        case 2:
            line.setLineSize(s.value);
            break;
            
        case 3:
            line.setLineColor(s.value,0, 0);
            break;
        case 4:
            line.setX2(s.value);
            break;
        case 5:
            line.setY2(s.value);
            break;
        case 6:
            line.setLeft(s.value);
            break;
        case 7:
            line.setTop(s.value);
            break;

    }
}

-(IBAction)segLine_change:(id)sender
{
    UISegmentedControl*seg=(UISegmentedControl*)sender;
    switch (seg.tag) {
        case 1:
        {
            switch (seg.selectedSegmentIndex) {
                case 0:
                    line.setHidden(0);
                    break;
                case 1:
                    line.setHidden(1);
                    break;
            }
        }
            break;
    }
}

-(IBAction)btnSide_change:(id)sender
{
    UISlider*s=(UISlider*)sender;
    switch (s.tag) {
        case 2:
            lb.setAngle(s.value);
            break;
            
        case 3:
            lb.setFontSpacing(s.value);
            break;
        case 4:
            lb.setScaleSize(s.value);
            break;
        case 6:
            lb.setFontColor(s.value,s.value, s.value);
            break;
    }
}

-(IBAction)segCurve_change:(id)sender
{
    UISegmentedControl*seg=(UISegmentedControl*)sender;
    switch (seg.tag) {
        case 0:
        {
            switch (seg.selectedSegmentIndex) {
                case 0:
                {
                    curve.removeAllPoint();
                    for (int i=0; i<4*20; i++) {
                        int f;
                        f=i%4;
                        f*=90;
                        int x=sin(2*M_PI*f/360)*i*2;
                        int y=cos(2*M_PI*f/360)*i*2;
                        curve.addPoint(x, y);
                    }
                }
                    break;
                case 1:
                {
                    curve.removeAllPoint();
                    short buf[1024];
                    float n=0;
                    for (int i=0; i<sizeof(buf)/2; i+=2) {
                        buf[i]=sin(n)*n*3;
                        buf[i+1]=cos(n)*n*3;
                        n+=0.1f;
                    }
                    curve.setPointBuf(ezhEaglUICurveData_XY_4Byte,
                                      (char*)buf,
                                      sizeof(buf));
                }
                    break;
            }
        }
            break;
    }
}


-(IBAction)btnFont_change:(id)sender
{
    UISegmentedControl*seg=(UISegmentedControl*)sender;
    switch (seg.tag) {
        case 1:
        {
            switch (seg.selectedSegmentIndex) {
                case 0:
                    lb.setFont(&font);
                    break;
                case 1:
                    lb.setFont(&font2);
                    break;
            }
        }
            break;
    }
}

//---------------- 绘制场景 --
-(void)drawScene
{
    //平面顶点数组
    GLfloat vertex[] = {
        -0.5, 0.5, -1,       //top left
        -0.5, -0.5, -1,      //bottom left
        0.5,-0.5, -1,        //bottom right
        0.5, 0.5, -1         //top right
    };
    GLfloat texCoodr[]={
        0.0, 0.0,    //top left
        0.0, 1.0,    //bottom left of square
        1.0, 1.0,   //bottom right of square
        1.0, 0.0,    //top right of square
    };
    
    //先启用纹理功能,再录入图片里的坐标
    glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindTexture(GL_TEXTURE_2D, 1);
    glTexCoordPointer(2, GL_FLOAT, 0, &texCoodr);
    
    //平面
    glEnable(GL_BLEND);//启用融合效果
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);//设置融合方式
    
    glEnableClientState(GL_VERTEX_ARRAY);
    
    glColor4f(1, 1, 1, 1);//附加颜色
    glVertexPointer(3, GL_FLOAT, 0, vertex);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glColor4f(1, 1, 1, 1);//恢复透明度不影响别的模型
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_BLEND); //关闭融合效果
    
    //关闭纹理
    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    
}

//---------------- 绘制UI --

-(void)drawUI
{
    gl_img.reader();
    gl_img2.reader();
    
    lb.reader();
    line.reader();
    curve.reader();
    
    btn.reader();
}

//////////////////////////////// call back  //////////////////////

-(void)MzhEaglFrameDrawSence
{
    [self drawScene];
}
-(void)MzhEaglFrameDrawUI
{
    [self drawUI];
}

-(void)touchesBegan:(NSSet *)touches
           senceRay:(TzhEaglLine*)senceline
              uiRay:(TzhEaglLine*)uiline
          withEvent:(UIEvent *)event
{
    //NSLog(@"%p   %p    %d    %f",touches,event,[[touches allObjects] count],uiline->p1.x);
    pppv=gl_img.pickUp(uiline);
    if (pppv) {
        NSLog(@"选中....");
        lb.setHidden(!lb.hidden);
    }
    
    pppv2=gl_img2.pickUp(uiline);
    
    btn.eventDown(uiline);
    
}
-(void)touchesMove:(NSSet *)touches
          senceRay:(TzhEaglLine*)senceline
             uiRay:(TzhEaglLine*)uiline
         withEvent:(UIEvent *)event step:(CGPoint)point
{
    
    mXZ+=point.x;
    v.eyeContex_x=sin(mXZ*M_PI/180)*5;
    v.eyeContex_z=cos(mXZ*M_PI/180)*5;
    
    if (mXZ>=360) {
        mXZ=0;
    }
}
-(void)touchesEnd:(NSSet *)touches
         senceRay:(TzhEaglLine*)senceline
            uiRay:(TzhEaglLine*)uiline
        withEvent:(UIEvent *)event
{
    //NSLog(@"-%p   %p    %d    %f",touches,event,[[touches allObjects] count],uiline->p1.x);

    btn.eventUp(uiline);
}

@end
