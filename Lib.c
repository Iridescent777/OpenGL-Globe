#define _CRT_SECURE_NO_WARNINGS

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#define WindowWidth 400;
#define WindowHeight 400
#define WindowTitle "OpenGL纹理测试"

GLfloat xrot = 0.0f; // x轴旋转角度
GLfloat yrot = 0.0f; // y轴旋转角度
GLfloat zrot = 0.0f;
GLfloat scale = 1.0f;

int lastX = 0, lastY = 0, lastZ = 0;

#define BMP_Header_Length 54

GLuint texEarth; // 地球纹理对象

static int day = 200;

static GLfloat angle = 0.0f;

const GLfloat PI = 3.1415926536f;


void drawSpecificSizePoint(void) {

    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(3.0f);

    glBegin(GL_POINTS);

    glVertex2f(0.0f, 0.0f);

    glEnd();

    glFlush();
}
void drawSine(void) {

    GLfloat x;

    GLfloat factor = 0.1f;

    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINES);

    glVertex2f(-1.0f, 0.0f);

    glVertex2f(1.0f, 0.0f);

    glEnd();

    glBegin(GL_LINE_STRIP);


    for (x = -1.0f / factor; x < 1.0f / factor; x += 0.01f) {
        glVertex2f(x * factor, sin(x) * factor);
    }

    glEnd();
    glFlush();
}
void drawStar(void) {

    glClear(GL_COLOR_BUFFER_BIT);

    GLfloat a = 1 / (2 - 2 * cos(72 * PI / 180));

    GLfloat bx = a * cos(18 * PI / 180);

    GLfloat by = a * sin(18 * PI / 180);

    GLfloat cy = -a * cos(18 * PI / 180);

    GLfloat PointA[2] = { 0, a };
    GLfloat PointB[2] = { bx, by };
    GLfloat PointC[2] = { 0.5, cy };
    GLfloat PointD[2] = { -0.5, cy };
    GLfloat PointE[2] = { -bx, by };

    glBegin(GL_LINE_LOOP);

    glVertex2fv(PointA);
    glVertex2fv(PointC);
    glVertex2fv(PointE);
    glVertex2fv(PointB);
    glVertex2fv(PointD);
    glEnd();
    glFlush();
}

void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glRectf(-0.5f, -0.5f, 0.5f, 0.5f);  //绘制矩形

    glBegin(GL_LINES);

    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.05f, 0.0f);

    glEnd();

    //让上方命令立即执行
    glFlush();

}

void drawCircleOutLine(void) {
    const int n = 20;

    //圆的半径
    const GLfloat R = 0.5f;


    int i;

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINE_LOOP);

    for (i = 0;i < n;++i)
        glVertex2f(R * cos(2 * PI / n * i), R * sin(2 * PI / n * i));
    glEnd();
    glFlush();
}

void drawCirclePoints(void) {
    const int n = 20;

    //圆的半径
    const GLfloat R = 0.5f;


    int i;

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);

    for (i = 0;i < n;++i)
        glVertex2f(R * cos(2 * PI / n * i), R * sin(2 * PI / n * i));
    glEnd();
    glFlush();
}

void drawCricleFilled(void) {

    const int n = 20;

    //圆的半径
    const GLfloat R = 0.5f;
    

    int i;

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);

    for (i = 0;i < n;++i)
        glVertex2f(R * cos(2 * PI / n * i), R * sin(2 * PI / n * i));
    glEnd();
    glFlush();
}


void drawPolygon(void) {

    glPolygonMode(GL_FRONT, GL_FILL);

    glPolygonMode(GL_BACK, GL_FILL);

    // 逆时针绘制
    glFrontFace(GL_CCW);

    //glFrontFace(GL_CW); //正面绘制
    // 
// 绘制多边形
    glBegin(GL_POLYGON);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.0f, -0.5f);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(-0.5f, 0.0f);
    glEnd();

    glFrontFace(GL_CW);
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(0.5f, 0.0f);
    glEnd();

    glFlush();
}

void drawStipplePolygon(const GLubyte *mask) {

    static GLubyte Mask[128];

    FILE* fp;

    fp = fopen("E:\\acm\\OpenGL\\src\\mask.bmp", "rb");

    if (!fp) {

        printf("Debug0");
        exit(0);
    }
    else if (fseek(fp, -(int)sizeof(Mask), SEEK_END)) {
        
        printf("Debug");
        
        exit(0);
    }
    else if(!fread(Mask, sizeof(Mask), 1, fp)){
        
        printf("Debug1");
        
        exit(0);
    }
    else {

        glClear(GL_COLOR_BUFFER_BIT);

        glEnable(GL_POLYGON_STIPPLE);

        glPolygonStipple(Mask);

        glColor3f(0.0f, 1.0f, 1.0f);

        glRectf(-0.5f, -0.5f, 0.0f, 0.0f);

        glDisable(GL_POLYGON_STIPPLE);

        glColor3f(0.0f, 1.0f, 1.0f);

        glRectf(0.0f, 0.0f, 0.5f, 0.5f);

        glFlush();

    }

}

void drawColorTransfer(void) {

    int i;

    glClear(GL_COLOR_BUFFER_BIT);

    //选择颜色过渡模式
    glShadeModel(GL_SMOOTH);

    glBegin(GL_TRIANGLE_FAN);

    glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(0.0f, 0.0f);

    for (i = 0;i <= 8; ++i) {

        glColor3f(i & 0x04, i & 0x02, i & 0x01);

        glVertex2f(cos(i * PI / 4), sin(i * PI / 4));
    }

    glEnd();

    glFlush();
}

void drawColorfulShape(void) {

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0f, 1.0f, 1.0f);

    glRectf(-0.8f, -0.8f, -0.6f, -0.6f);



    glColor3ub(0.0f, 255.0f, 0.0f);
    const int n = 20;

    //圆的半径
    const GLfloat R = 0.5f;


    int i;

    glBegin(GL_POLYGON);

    for (i = 0;i < n;++i)
        glVertex2f(R * cos(2 * PI / n * i), R * sin(2 * PI / n * i));
    glEnd();


    glFlush();

}

void drawSphere(void) {

    glClear(GL_COLOR_BUFFER_BIT);
    glutSolidSphere(1, 20, 20);
    glFlush();
}

void SunEarthMoon(void) {

    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 1, 400000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, -200000, 200000, 0, 0, 0, 0, 0, 1);

    // 绘制红色的“太阳”
    glColor3f(1.0f, 0.0f, 0.0f);
    glutSolidSphere(69600, 20, 20);
    // 绘制蓝色的“地球”
    glColor3f(0.0f, 0.0f, 1.0f);
    glRotatef(day / 360.0 * 360.0, 0.0f, 0.0f, -1.0f);
    glTranslatef(150000, 0.0f, 0.0f);
    glutSolidSphere(15945, 20, 20);
    // 绘制黄色的“月亮”
    glColor3f(1.0f, 1.0f, 0.0f);
    glRotatef(day / 30.0 * 360.0 - day / 360.0 * 360.0, 0.0f, 0.0f, -1.0f);
    glTranslatef(38000, 0.0f, 0.0f);
    glutSolidSphere(4345, 20, 20);

    glFlush();

    glutSwapBuffers();


}

void myIdle(void)
{
    /* 新的函数，在空闲时调用，作用是把日期往后移动一天并重新绘制，达到动画效果 */
    Sleep(20);
    angle += 0.1f;
    if (day >= 360.0f)
        day = 0.0f;

    glutPostOverlayRedisplay();
}


void mydisplay(void) {

    glClear(GL_COLOR_BUFFER_BIT);

    glRectf(-0.5f, -0.5f, 0.5f, 0.5f);

    glFlush();
}

void ShowEarth(void) {

    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 1, 400000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, -200000, 200000, 0, 0, 0, 0, 0, 1);

    // 绘制红色的“太阳”
    glColor3f(0.0f, 0.0f, 1.0f);
    glutSolidSphere(69600, 50, 50);

    glFlush();

    glutSwapBuffers();
}
void Light(void) {


   
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 创建透视效果视图
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0f, 1.0f, 1.0f, 20.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 5.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // 定义太阳光源，它是一种白色的光源
    {
        GLfloat sun_light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        GLfloat sun_light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        GLfloat sun_light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        GLfloat sun_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        GLfloat spot_Direction[] = { 1.0f, 0.0f, 0.0f };
        GLfloat spot_exponent[] = { 1.0f };
        GLfloat spot_cutoff[] = { 60.0f };

        glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
        glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);
        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_Direction);
        glLightfv(GL_LIGHT0, GL_SPOT_EXPONENT, spot_exponent);
        glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff);

        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHTING);
        glEnable(GL_DEPTH_TEST);
    }

    // 定义太阳的材质并绘制太阳
    {
        GLfloat sun_mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        GLfloat sun_mat_diffuse[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        GLfloat sun_mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        GLfloat sun_mat_emission[] = { 0.5f, 0.0f, 0.0f, 1.0f };
        GLfloat sun_mat_shininess = 0.0f;

        glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular);
        glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
        glMaterialf(GL_FRONT, GL_SHININESS, sun_mat_shininess);

        glutSolidSphere(2.0, 40, 32);
    }

    // 定义地球的材质并绘制地球
    {
        GLfloat earth_mat_ambient[] = { 0.0f, 0.0f, 0.5f, 1.0f };
        GLfloat earth_mat_diffuse[] = { 0.0f, 0.0f, 0.5f, 1.0f };
        GLfloat earth_mat_specular[] = { 0.0f, 0.0f, 1.0f, 1.0f };
        GLfloat earth_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        GLfloat earth_mat_shininess = 30.0f;

        glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
        glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
        glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);

        glRotatef(angle, 0.0f, -1.0f, 0.0f);
        glTranslatef(5.0f, 0.0f, 0.0f);
        glutSolidSphere(2.0, 40, 32);
    }

    glutSwapBuffers();

}

void myIdleLight(void) {

    Sleep(5);
    angle += 1.0f;
    if (angle >= 360.0f)
        angle = 0.0f;
    Light();

}

/*oid bmp(void) {

    GLint width, height;

    FILE* pFile;

    fseek(pFile, 0x0012, SEEK_SET);

    fread(&width, sizeof(width), 1, pFile);

    fread(&height, sizeof(height), 1, pFile);

    int LineLength, TotalLength;




}*/
// 两个纹理对象的编号
GLuint texGround;
GLuint texWall;

// 函数grab将抓取窗口中的像素，并保存到文件中
void grab(void)
{
    glReadBuffer(GL_FRONT);
    FILE* pDummyFile;
    FILE* pWritingFile;
    GLubyte* pPixelData;
    GLubyte BMP_Header[54] = {
        0x42, 0x4d, 0, 0, 0, 0, 0, 0, 0, 0,
        54, 0, 0, 0, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0
    };
    GLint i, j;
    GLint PixelDataLength;

    // 计算像素数据的实际长度
    i = 3 * WindowWidth; // 得到每一行的像素数据长度
    while (i % 4 != 0)
        ++i; // 补充数据，直到i是的倍数
    PixelDataLength = i * WindowHeight;

    // 分配内存和打开文件
    pPixelData = (GLubyte*)malloc(PixelDataLength);
    if (pPixelData == 0)
        exit(0);

    pDummyFile = fopen("E:\\acm\\OpenGL\\src\\mask.bmp", "rb");
    if (pDummyFile == 0)
        exit(0);

    pWritingFile = fopen("grab.bmp", "wb");
    if (pWritingFile == 0)
        exit(0);

    // 绑定地球纹理
    glBindTexture(GL_TEXTURE_2D, texEarth);

    // 读取像素
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glReadPixels(0, 0, 400, 400, GL_BGR_EXT, GL_UNSIGNED_BYTE, pPixelData);

    // 把dummy.bmp的文件头复制为新文件的文件头
    fread(BMP_Header, sizeof(BMP_Header), 1, pDummyFile);
    fwrite(BMP_Header, sizeof(BMP_Header), 1, pWritingFile);
    fseek(pWritingFile, 0x0012, SEEK_SET);
    i = WindowWidth;
    j = WindowHeight;
    fwrite(&i, sizeof(i), 1, pWritingFile);
    fwrite(&j, sizeof(j), 1, pWritingFile);

    // 写入像素数据
    fseek(pWritingFile, 0, SEEK_END);
    fwrite(pPixelData, PixelDataLength, 1, pWritingFile);

    // 释放内存和关闭文件
    fclose(pDummyFile);
    fclose(pWritingFile);
    free(pPixelData);
}

// 从BMP文件中读取像素
// 参数filename为BMP文件名
// 参数width、height返回BMP图像的宽高
// 返回值为指向图像像素数据的指针
//GLubyte* load_texture_s(const char* filename, GLint* width, GLint* height)
//{
//    GLint i, j = 0; // 循环变量
//    GLint pixellength; // 像素数据长度
//    GLubyte* pixels = 0; // 像素数据指针
//    GLubyte* bmpFileHeader = 0; // BMP文件头指针
//    GLubyte* bmpInfoHeader = 0; // BMP信息头指针
//    FILE* pFile = 0; // 文件指针
//
//    // 打开文件
//    pFile = fopen(filename, "rb");
//    if (pFile == 0)
//        return 0;
//
//    // 读取文件头
//    bmpFileHeader = (GLubyte*)malloc(sizeof(GLubyte) * 14);
//    if (bmpFileHeader == 0)
//    {
//        fclose(pFile);
//        return 0;
//    }
//    fread(bmpFileHeader, sizeof(GLubyte) * 14, 1, pFile);
//
//    // 读取信息头
//    bmpInfoHeader = (GLubyte*)malloc(sizeof(GLubyte) * 40);
//    if (bmpInfoHeader == 0)
//    {
//        free(bmpFileHeader);
//        fclose(pFile);
//        return 0;
//    }
//    fread(bmpInfoHeader, sizeof(GLubyte) * 40, 1, pFile);
//
//    // 读取图像的宽高
//    *width = *(int*)&bmpInfoHeader[4];
//    *height = *(int*)&bmpInfoHeader[8];
//
//    // 计算像素数据长度
//    pixellength = (*width) * 3; // 得到每一行的像素数据长度
//    while (pixellength % 4 != 0)
//        ++pixellength; // 补充数据，直到pixellength是的倍数
//    pixellength *= (*height);
//
//    // 读取像素数据
//    pixels = (GLubyte*)malloc(sizeof(GLubyte) * pixellength);
//    if (pixels == 0)
//    {
//        free(bmpFileHeader);
//        free(bmpInfoHeader);
//        fclose(pFile);
//        return 0;
//    }
//    fread(pixels, sizeof(GLubyte) * pixellength, 1, pFile);
//
//    // 交换R和B的值，因为BMP文件中颜色的顺序是BGR
//    for (j = 0; j < (*height); ++j)
//    {
//        for (i = 0; i < (*width) * 3; i += 3)
//        {
//            GLubyte temp = pixels[j * pixellength + i];
//            pixels[j * pixellength + i] = pixels[j * pixellength + i + 2];
//            pixels[j * pixellength + i + 2] = temp;
//        }
//    }
//
//    // 关闭文件
//    fclose(pFile);
//
//    // 释放文件头和信息头的内存
//    free(bmpFileHeader);
//    free(bmpInfoHeader);
//
//    // 返回像素数据指针
//    return pixels;
//}

// 创建纹理对象，并载入纹理
// 参数filename为BMP文件名
// 返回值为纹理对象的编号
//GLuint load_texture(const char* filename)
//{
//    GLint width, height; // 纹理的宽高
//    GLubyte* pixels = 0; // 像素数据指针
//    GLuint texture_ID = 0; // 纹理对象编号
//
//    // 读取像素
//    pixels = load_texture_s(filename, &width, &height);
//    if (pixels == 0)
//        return 0;
//
//    // 创建纹理对象
//    glGenTextures(1, &texture_ID);
//    glBindTexture(GL_TEXTURE_2D, texture_ID);
//
//    // 设置纹理参数
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//
//    // 载入纹理
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
//
//    // 释放像素数据
//    free(pixels);
//
//    // 返回纹理对象编号
//    return texture_ID;
//}

void SpinHumanly(void) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75, 1, 1, 21);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1, 2, 2, 0, 0, 0, 0, 0, 1);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texEarth);

    glPushMatrix();
    glRotatef(xrot, 1.0f, 0.0f, 0.0f); // 绕x轴旋转
    glRotatef(yrot, 0.0f, 1.0f, 0.0f); // 绕y轴旋转
    glRotatef(zrot, 0.0f, 0.0f, 1.0f);

    GLUquadricObj* quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);
    gluSphere(quadric, scale, 50, 50); // 绘制半径为scale的球体，细分20x20


    gluDeleteQuadric(quadric);

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glutSwapBuffers();
}

void reset(void)
{
    // 重置旋转角度
    xrot = 0.0f;
    yrot = 0.0f;
    scale = 1.0f;

    // 标记窗口需要重新绘制
    glutPostRedisplay();
}

void zoomIn(void) {

    scale *= 1.5f;

    if (scale > 10.0f)scale = 10.0f;

    glutPostRedisplay();
}

void zoomOut(void) {

    scale = 0.5 * scale;

    if (scale < 0.01f)scale = 0.01f;

    glutPostRedisplay();
}
void createMenu(void)
{

    glutCreateMenu(reset);
    glutAddMenuEntry("Reset", 1);
    glutAttachMenu(GLUT_RIGHT_BUTTON); 
}


void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        // 鼠标左键按下时记录当前鼠标位置
        lastX = x;
        lastY = y;
    }
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case '+':
        zoomIn();
        break;
    case '-':
        zoomOut();
        break;
    case 'r':
        reset();
        break;
    default:
        break;
    }
}


void motion(int x, int y)
{
    // 计算鼠标移动的偏移量
    int dx = x - lastX;
    int dy = y - lastY;

    // 更新旋转角度
    xrot -= dy * 0.2f;
    yrot -= dx * 0.2f;

    // 限制旋转角度在合理范围内
    if (xrot > 90.0f) xrot = 90.0f;
    if (xrot < -90.0f) xrot = -90.0f;

    // 标记窗口需要重新绘制
    glutPostRedisplay();


}

GLuint load_texture(const char* filename)
{
    GLuint texture;
    int width, height;
    unsigned char* image;

    // 打开文件
    FILE* file = fopen(filename, "rb");
    if (!file)
    {
        printf("Error opening file: %s\n", filename);
        exit(1);
    }

    // 读取文件头
    unsigned char header[54];
    fread(header, 1, 54, file);

    // 检查文件格式
    if (header[0] != 'B' || header[1] != 'M')
    {
        printf("Invalid BMP file: %s\n", filename);
        fclose(file);
        exit(1);
    }

    // 读取图像尺寸
    width = *(int*)&header[18];
    height = *(int*)&header[22];

    // 计算图像数据大小
    int image_size = width * height * 3;

    // 分配内存并读取图像数据
    image = (unsigned char*)malloc(image_size);
    fread(image, 1, image_size, file);
    fclose(file);

    // 生成纹理对象
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // 设置纹理参数
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // 加载纹理数据
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, image);

    // 释放图像数据
    free(image);

    return texture;
}

void init() {
    // 设置背景颜色
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    // 启用光照
    glEnable(GL_LIGHTING);

    // 启用第一个光源（环境光 + 漫反射 + 镜面反射）
    glEnable(GL_LIGHT0);
    GLfloat lightAmbient[] = { 0.1f, 0.1f, 0.1f, 1.0f }; // 环境光
    GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f }; // 漫反射光
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // 镜面反射光
    GLfloat lightPosition[] = { -5.0f, 5.0f, 5.0f, 1.0f }; // 左侧位置光源
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    // 启用第二个光源（聚光灯）
    glEnable(GL_LIGHT1);
    GLfloat spotDirection[] = { 1.0f, -1.0f, 0.0f }; // 聚光灯方向指向地球
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDirection);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0f); // 聚光角度
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0f); // 聚光衰减

    // 设置材质属性（地球）
    GLfloat earthMaterialAmbient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat earthMaterialDiffuse[] = { 0.6f, 0.6f, 0.6f, 1.0f };
    GLfloat earthMaterialSpecular[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    GLfloat earthMaterialShininess[] = { 50.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, earthMaterialAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, earthMaterialDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, earthMaterialSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, earthMaterialShininess);

    // 设置材质属性（支架）
    GLfloat standMaterialAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat standMaterialDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat standMaterialSpecular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat standMaterialShininess[] = { 10.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, standMaterialAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, standMaterialDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, standMaterialSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, standMaterialShininess);

    // 加载地球纹理
    texEarth = load_texture("E:\\acm\\OpenGL\\src\\Earth.bmp");
}

void display(void)
{
    // 清除颜色和深度缓冲区
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 设置视角
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75, 1, 1, 21);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1, 2, 2, 0, 0, 0, 0, 0, 1);

    // 启用纹理映射
    glEnable(GL_TEXTURE_2D);

    // 绑定地球纹理
    glBindTexture(GL_TEXTURE_2D, texEarth);

    glPushMatrix();

    glScalef(scale, scale, scale);  // 应用缩放
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    // 设置纹理坐标
    GLUquadricObj* quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);
    gluSphere(quadric, 1, 50, 50); // 绘制半径为1的球体，细分20x20
    gluDeleteQuadric(quadric);

    glPopMatrix();
    // 禁用纹理映射
    glDisable(GL_TEXTURE_2D);

    //// 绘制支架
    //glColor3f(0.8f, 0.8f, 0.8f); // 支架颜色

    //// 绘制四分之一圆环
    //glPushMatrix();
    //glTranslatef(1.0, 0.0, 0); // 移动到地球右侧
    //glRotatef(-90.0, 0.0, 1.0, 0.0); // 旋转90度，使其垂直于地球
    //glBegin(GL_LINE_LOOP);
    //for (int i = 0; i <= 90; ++i) {
    //    float angle = PI * i / 180.0;
    //    glVertex3f(cos(angle), sin(angle), 0);
    //}
    //glEnd();
    //glPopMatrix();

    //// 绘制圆环的下侧圆柱
    //glPushMatrix();
    //glTranslatef(0, -2.0, 0); // 移动到圆环下侧
    //GLUquadricObj* cylinder = gluNewQuadric();
    //gluQuadricDrawStyle(cylinder, GLU_FILL); // 实心绘制
    //gluQuadricNormals(cylinder, GLU_SMOOTH); // 平滑法线
    //gluCylinder(cylinder, 0.1, 0.1, 1.0, 20, 20); // 绘制圆柱体
    //gluDeleteQuadric(cylinder);

    //// 绘制圆柱体底部的圆形底座
    //glBegin(GL_POLYGON);
    //for (int i = 0; i < 20; ++i) {
    //    float angle = 2 * PI * i / 20;
    //    glVertex3f(0.1 * cos(angle), -2.0, 0.1 * sin(angle));
    //}
    //glEnd();

    //glPopMatrix();

    // 交换缓冲区
    glutSwapBuffers();
}



// argc->命令行参数总个数
// argv[0]->可执行程序名  argv[i]->第i个参数

void idle(void)
{
    Sleep(5);
    angle += 0.1f;
    if (angle > 360.0f)
        angle -= 360.0f;

    glutPostRedisplay();

}

int main(int argc, char* argv[]){



    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL Earth Texture");

    
    
    // 注册回调函数
    
    //自动旋转

     // 初始化 OpenGL 和光照
    init();

    glutDisplayFunc(&display);
    //glutKeyboardFunc(&grab);
    glutIdleFunc(&idle);

    //手动旋转
    // 注册回调函数
    /*glutDisplayFunc(&SpinHumanly);
    glutMouseFunc(&mouse);
    glutMotionFunc(&motion);
    glutIdleFunc(&idle);*/
    createMenu();
    glutKeyboardFunc(keyboard);  // 注册键盘事件处理函数



    // 初始化 OpenGL
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);


    // 加载地球纹理
   /* texEarth = load_texture("E:\\acm\\OpenGL\\src\\Earth.bmp");*/


    // 进入 GLUT 主循环
    glutMainLoop();



    return 0;

    

}

