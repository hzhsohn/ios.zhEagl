//
//  zhOpenglEs
//
//  Created by han on 13-7-2.
//  Copyright (c) 2013年 Han.zhihong. All rights reserved.
//
//  Blog
//  http://www.hanzhihong.cn
//

#import <UIKit/UIKit.h>
#import "MzhEaglFrame.h"

@interface ViewController : UIViewController<MzhEaglFrameDelegate>
{
    IBOutlet MzhEaglFrame* v;
    
    
    ///////////// 举例变量 /////////////
    
    //当前屏幕移动的X坐标,Y坐标,与OPENGL坐标体系一样
    float mXZ;
    
}

-(IBAction)segLine_change:(id)sender;
-(IBAction)sideLine_change:(id)sender;

-(IBAction)segCurve_change:(id)sender;

-(IBAction)btnFont_change:(id)sender;

-(void)drawScene;
-(void)drawUI;

@end
