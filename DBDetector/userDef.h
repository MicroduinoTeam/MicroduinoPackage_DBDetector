#define voice 30	//噪声阈值
#define INTERVALOLED 50 	//刷新OLED的毫秒数
#define maxNoise 5		//在指定时间发上噪声的次数的阈值
#define micPin A0	//麦克风引脚
#define LEDPIN 6	//led灯引脚
#define buzzerPin 10	//蜂鸣器引脚
#define keyPin 8	//按键引脚


long timer;		//按键定时器
int numNoise=0;		//记录噪音频率
boolean isAlaram=false;		//标记是否开蜂鸣器
boolean add;		//标记蜂鸣器频率增加还是减少
int i = 200;		//蜂鸣器频率初始值
double recodeDB=0.0;	//显示在OLED上的最高分贝数