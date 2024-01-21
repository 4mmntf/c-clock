#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <opencv/highgui.h>
struct tm tm;

// 文字書き込み用のフォントの作成
void initFont(CvFont* font) {
	cvInitFont(font, CV_FONT_HERSHEY_TRIPLEX, 3.0, 3.0);
}

int main(void) {
	IplImage* img = cvCreateImage(cvSize(800, 800), IPL_DEPTH_8U, 3); // 800x800 サイズのカラー画像を生成
	
	while (1) /*毎秒更新する*/{
		//時刻を取得
		time_t t = time(NULL);
		if (localtime_s(&tm, &t) != 0) {
			perror("Error getting local time");
			return 0;
		}

		int h = tm.tm_hour;
		int m = tm.tm_min;
		int s = tm.tm_sec;

		//時計の針の角度を計算
		double hx = 400 + 150 * sin(h * CV_PI / 6 + m * CV_PI / 360);
		double hy = 400 - 150 * cos(h * CV_PI / 6 + m * CV_PI / 360);
		double mx = 400 + 300 * sin(m * CV_PI / 30 + s * CV_PI / 1800);
		double my = 400 - 300 * cos(m * CV_PI / 30 + s * CV_PI / 1800);
		double sx = 400 + 300 * sin(s * CV_PI / 30);
		double sy = 400 - 300 * cos(s * CV_PI / 30);

		cvSet(img, cvScalar(255, 255, 255)); // 真っ白に塗りつぶす

		CvFont font; //以下文字盤
		initFont(&font);
		cvPutText(img, "12", cvPoint(350, 150), &font, cvScalar(0, 0, 0));
		cvPutText(img, "3", cvPoint(650, 430), &font, cvScalar(0, 0, 0));
		cvPutText(img, "6", cvPoint(370, 720), &font, cvScalar(0, 0, 0));
		cvPutText(img, "9", cvPoint(100, 430), &font, cvScalar(0, 0, 0));

		cvCircle(img, cvPoint(400, 400), 350, cvScalar(0, 0, 0), 2); // 円
		cvLine(img, cvPoint(400, 400), cvPoint(hx, hy), cvScalar(0, 0, 0), 15, 1); // 短針
		cvLine(img, cvPoint(400, 400), cvPoint(mx, my), cvScalar(0, 0, 0), 10, 1); // 長針
		cvLine(img, cvPoint(400, 400), cvPoint(sx, sy), cvScalar(0, 0, 0), 3, 1); // 秒針
		cvNamedWindow("Output"); // 画像表示用のウインドウを開く
		cvShowImage("Output", img); // 画像をウインドウ内に表示

		char c = cvWaitKey(1);
		if (c == 27)  // ESCキーが押されたら終了
			break;
	}
	cvReleaseImage(&img); // 画像 img を破棄
	cvDestroyAllWindows(); // 全てのWindowを破棄
	return 0;
}