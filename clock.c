#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <opencv/highgui.h>
struct tm tm;

// �����������ݗp�̃t�H���g�̍쐬
void initFont(CvFont* font) {
	cvInitFont(font, CV_FONT_HERSHEY_TRIPLEX, 3.0, 3.0);
}

int main(void) {
	IplImage* img = cvCreateImage(cvSize(800, 800), IPL_DEPTH_8U, 3); // 800x800 �T�C�Y�̃J���[�摜�𐶐�
	
	while (1) /*���b�X�V����*/{
		//�������擾
		time_t t = time(NULL);
		if (localtime_s(&tm, &t) != 0) {
			perror("Error getting local time");
			return 0;
		}

		int h = tm.tm_hour;
		int m = tm.tm_min;
		int s = tm.tm_sec;

		//���v�̐j�̊p�x���v�Z
		double hx = 400 + 150 * sin(h * CV_PI / 6 + m * CV_PI / 360);
		double hy = 400 - 150 * cos(h * CV_PI / 6 + m * CV_PI / 360);
		double mx = 400 + 300 * sin(m * CV_PI / 30 + s * CV_PI / 1800);
		double my = 400 - 300 * cos(m * CV_PI / 30 + s * CV_PI / 1800);
		double sx = 400 + 300 * sin(s * CV_PI / 30);
		double sy = 400 - 300 * cos(s * CV_PI / 30);

		cvSet(img, cvScalar(255, 255, 255)); // �^�����ɓh��Ԃ�

		CvFont font; //�ȉ�������
		initFont(&font);
		cvPutText(img, "12", cvPoint(350, 150), &font, cvScalar(0, 0, 0));
		cvPutText(img, "3", cvPoint(650, 430), &font, cvScalar(0, 0, 0));
		cvPutText(img, "6", cvPoint(370, 720), &font, cvScalar(0, 0, 0));
		cvPutText(img, "9", cvPoint(100, 430), &font, cvScalar(0, 0, 0));

		cvCircle(img, cvPoint(400, 400), 350, cvScalar(0, 0, 0), 2); // �~
		cvLine(img, cvPoint(400, 400), cvPoint(hx, hy), cvScalar(0, 0, 0), 15, 1); // �Z�j
		cvLine(img, cvPoint(400, 400), cvPoint(mx, my), cvScalar(0, 0, 0), 10, 1); // ���j
		cvLine(img, cvPoint(400, 400), cvPoint(sx, sy), cvScalar(0, 0, 0), 3, 1); // �b�j
		cvNamedWindow("Output"); // �摜�\���p�̃E�C���h�E���J��
		cvShowImage("Output", img); // �摜���E�C���h�E���ɕ\��

		char c = cvWaitKey(1);
		if (c == 27)  // ESC�L�[�������ꂽ��I��
			break;
	}
	cvReleaseImage(&img); // �摜 img ��j��
	cvDestroyAllWindows(); // �S�Ă�Window��j��
	return 0;
}