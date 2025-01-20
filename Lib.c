#define _CRT_SECURE_NO_WARNINGS

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#define WindowWidth 400;
#define WindowHeight 400
#define WindowTitle "OpenGL�������"

GLfloat xrot = 0.0f; // x����ת�Ƕ�
GLfloat yrot = 0.0f; // y����ת�Ƕ�
GLfloat zrot = 0.0f;
GLfloat scale = 1.0f;

int lastX = 0, lastY = 0, lastZ = 0;

#define BMP_Header_Length 54

GLuint texEarth; // �����������

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
    glRectf(-0.5f, -0.5f, 0.5f, 0.5f);  //���ƾ���

    glBegin(GL_LINES);

    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.05f, 0.0f);

    glEnd();

    //���Ϸ���������ִ��
    glFlush();

}

void drawCircleOutLine(void) {
    const int n = 20;

    //Բ�İ뾶
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

    //Բ�İ뾶
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

    //Բ�İ뾶
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

    // ��ʱ�����
    glFrontFace(GL_CCW);

    //glFrontFace(GL_CW); //�������
    // 
// ���ƶ����
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

    //ѡ����ɫ����ģʽ
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

    //Բ�İ뾶
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

    // ���ƺ�ɫ�ġ�̫����
    glColor3f(1.0f, 0.0f, 0.0f);
    glutSolidSphere(69600, 20, 20);
    // ������ɫ�ġ�����
    glColor3f(0.0f, 0.0f, 1.0f);
    glRotatef(day / 360.0 * 360.0, 0.0f, 0.0f, -1.0f);
    glTranslatef(150000, 0.0f, 0.0f);
    glutSolidSphere(15945, 20, 20);
    // ���ƻ�ɫ�ġ�������
    glColor3f(1.0f, 1.0f, 0.0f);
    glRotatef(day / 30.0 * 360.0 - day / 360.0 * 360.0, 0.0f, 0.0f, -1.0f);
    glTranslatef(38000, 0.0f, 0.0f);
    glutSolidSphere(4345, 20, 20);

    glFlush();

    glutSwapBuffers();


}

void myIdle(void)
{
    /* �µĺ������ڿ���ʱ���ã������ǰ����������ƶ�һ�첢���»��ƣ��ﵽ����Ч�� */
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

    // ���ƺ�ɫ�ġ�̫����
    glColor3f(0.0f, 0.0f, 1.0f);
    glutSolidSphere(69600, 50, 50);

    glFlush();

    glutSwapBuffers();
}
void Light(void) {


   
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // ����͸��Ч����ͼ
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0f, 1.0f, 1.0f, 20.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 5.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // ����̫����Դ������һ�ְ�ɫ�Ĺ�Դ
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

    // ����̫���Ĳ��ʲ�����̫��
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

    // �������Ĳ��ʲ����Ƶ���
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
// �����������ı��
GLuint texGround;
GLuint texWall;

// ����grab��ץȡ�����е����أ������浽�ļ���
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

    // �����������ݵ�ʵ�ʳ���
    i = 3 * WindowWidth; // �õ�ÿһ�е��������ݳ���
    while (i % 4 != 0)
        ++i; // �������ݣ�ֱ��i�ǵı���
    PixelDataLength = i * WindowHeight;

    // �����ڴ�ʹ��ļ�
    pPixelData = (GLubyte*)malloc(PixelDataLength);
    if (pPixelData == 0)
        exit(0);

    pDummyFile = fopen("E:\\acm\\OpenGL\\src\\mask.bmp", "rb");
    if (pDummyFile == 0)
        exit(0);

    pWritingFile = fopen("grab.bmp", "wb");
    if (pWritingFile == 0)
        exit(0);

    // �󶨵�������
    glBindTexture(GL_TEXTURE_2D, texEarth);

    // ��ȡ����
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glReadPixels(0, 0, 400, 400, GL_BGR_EXT, GL_UNSIGNED_BYTE, pPixelData);

    // ��dummy.bmp���ļ�ͷ����Ϊ���ļ����ļ�ͷ
    fread(BMP_Header, sizeof(BMP_Header), 1, pDummyFile);
    fwrite(BMP_Header, sizeof(BMP_Header), 1, pWritingFile);
    fseek(pWritingFile, 0x0012, SEEK_SET);
    i = WindowWidth;
    j = WindowHeight;
    fwrite(&i, sizeof(i), 1, pWritingFile);
    fwrite(&j, sizeof(j), 1, pWritingFile);

    // д����������
    fseek(pWritingFile, 0, SEEK_END);
    fwrite(pPixelData, PixelDataLength, 1, pWritingFile);

    // �ͷ��ڴ�͹ر��ļ�
    fclose(pDummyFile);
    fclose(pWritingFile);
    free(pPixelData);
}

// ��BMP�ļ��ж�ȡ����
// ����filenameΪBMP�ļ���
// ����width��height����BMPͼ��Ŀ��
// ����ֵΪָ��ͼ���������ݵ�ָ��
//GLubyte* load_texture_s(const char* filename, GLint* width, GLint* height)
//{
//    GLint i, j = 0; // ѭ������
//    GLint pixellength; // �������ݳ���
//    GLubyte* pixels = 0; // ��������ָ��
//    GLubyte* bmpFileHeader = 0; // BMP�ļ�ͷָ��
//    GLubyte* bmpInfoHeader = 0; // BMP��Ϣͷָ��
//    FILE* pFile = 0; // �ļ�ָ��
//
//    // ���ļ�
//    pFile = fopen(filename, "rb");
//    if (pFile == 0)
//        return 0;
//
//    // ��ȡ�ļ�ͷ
//    bmpFileHeader = (GLubyte*)malloc(sizeof(GLubyte) * 14);
//    if (bmpFileHeader == 0)
//    {
//        fclose(pFile);
//        return 0;
//    }
//    fread(bmpFileHeader, sizeof(GLubyte) * 14, 1, pFile);
//
//    // ��ȡ��Ϣͷ
//    bmpInfoHeader = (GLubyte*)malloc(sizeof(GLubyte) * 40);
//    if (bmpInfoHeader == 0)
//    {
//        free(bmpFileHeader);
//        fclose(pFile);
//        return 0;
//    }
//    fread(bmpInfoHeader, sizeof(GLubyte) * 40, 1, pFile);
//
//    // ��ȡͼ��Ŀ��
//    *width = *(int*)&bmpInfoHeader[4];
//    *height = *(int*)&bmpInfoHeader[8];
//
//    // �����������ݳ���
//    pixellength = (*width) * 3; // �õ�ÿһ�е��������ݳ���
//    while (pixellength % 4 != 0)
//        ++pixellength; // �������ݣ�ֱ��pixellength�ǵı���
//    pixellength *= (*height);
//
//    // ��ȡ��������
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
//    // ����R��B��ֵ����ΪBMP�ļ�����ɫ��˳����BGR
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
//    // �ر��ļ�
//    fclose(pFile);
//
//    // �ͷ��ļ�ͷ����Ϣͷ���ڴ�
//    free(bmpFileHeader);
//    free(bmpInfoHeader);
//
//    // ������������ָ��
//    return pixels;
//}

// ����������󣬲���������
// ����filenameΪBMP�ļ���
// ����ֵΪ�������ı��
//GLuint load_texture(const char* filename)
//{
//    GLint width, height; // ����Ŀ��
//    GLubyte* pixels = 0; // ��������ָ��
//    GLuint texture_ID = 0; // ���������
//
//    // ��ȡ����
//    pixels = load_texture_s(filename, &width, &height);
//    if (pixels == 0)
//        return 0;
//
//    // �����������
//    glGenTextures(1, &texture_ID);
//    glBindTexture(GL_TEXTURE_2D, texture_ID);
//
//    // �����������
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//
//    // ��������
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
//
//    // �ͷ���������
//    free(pixels);
//
//    // �������������
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
    glRotatef(xrot, 1.0f, 0.0f, 0.0f); // ��x����ת
    glRotatef(yrot, 0.0f, 1.0f, 0.0f); // ��y����ת
    glRotatef(zrot, 0.0f, 0.0f, 1.0f);

    GLUquadricObj* quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);
    gluSphere(quadric, scale, 50, 50); // ���ư뾶Ϊscale�����壬ϸ��20x20


    gluDeleteQuadric(quadric);

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glutSwapBuffers();
}

void reset(void)
{
    // ������ת�Ƕ�
    xrot = 0.0f;
    yrot = 0.0f;
    scale = 1.0f;

    // ��Ǵ�����Ҫ���»���
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
        // ����������ʱ��¼��ǰ���λ��
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
    // ��������ƶ���ƫ����
    int dx = x - lastX;
    int dy = y - lastY;

    // ������ת�Ƕ�
    xrot -= dy * 0.2f;
    yrot -= dx * 0.2f;

    // ������ת�Ƕ��ں���Χ��
    if (xrot > 90.0f) xrot = 90.0f;
    if (xrot < -90.0f) xrot = -90.0f;

    // ��Ǵ�����Ҫ���»���
    glutPostRedisplay();


}

GLuint load_texture(const char* filename)
{
    GLuint texture;
    int width, height;
    unsigned char* image;

    // ���ļ�
    FILE* file = fopen(filename, "rb");
    if (!file)
    {
        printf("Error opening file: %s\n", filename);
        exit(1);
    }

    // ��ȡ�ļ�ͷ
    unsigned char header[54];
    fread(header, 1, 54, file);

    // ����ļ���ʽ
    if (header[0] != 'B' || header[1] != 'M')
    {
        printf("Invalid BMP file: %s\n", filename);
        fclose(file);
        exit(1);
    }

    // ��ȡͼ��ߴ�
    width = *(int*)&header[18];
    height = *(int*)&header[22];

    // ����ͼ�����ݴ�С
    int image_size = width * height * 3;

    // �����ڴ沢��ȡͼ������
    image = (unsigned char*)malloc(image_size);
    fread(image, 1, image_size, file);
    fclose(file);

    // �����������
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // �����������
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // ������������
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, image);

    // �ͷ�ͼ������
    free(image);

    return texture;
}

void init() {
    // ���ñ�����ɫ
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    // ���ù���
    glEnable(GL_LIGHTING);

    // ���õ�һ����Դ�������� + ������ + ���淴�䣩
    glEnable(GL_LIGHT0);
    GLfloat lightAmbient[] = { 0.1f, 0.1f, 0.1f, 1.0f }; // ������
    GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f }; // �������
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // ���淴���
    GLfloat lightPosition[] = { -5.0f, 5.0f, 5.0f, 1.0f }; // ���λ�ù�Դ
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    // ���õڶ�����Դ���۹�ƣ�
    glEnable(GL_LIGHT1);
    GLfloat spotDirection[] = { 1.0f, -1.0f, 0.0f }; // �۹�Ʒ���ָ�����
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDirection);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0f); // �۹�Ƕ�
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0f); // �۹�˥��

    // ���ò������ԣ�����
    GLfloat earthMaterialAmbient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat earthMaterialDiffuse[] = { 0.6f, 0.6f, 0.6f, 1.0f };
    GLfloat earthMaterialSpecular[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    GLfloat earthMaterialShininess[] = { 50.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, earthMaterialAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, earthMaterialDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, earthMaterialSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, earthMaterialShininess);

    // ���ò������ԣ�֧�ܣ�
    GLfloat standMaterialAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat standMaterialDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat standMaterialSpecular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat standMaterialShininess[] = { 10.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, standMaterialAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, standMaterialDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, standMaterialSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, standMaterialShininess);

    // ���ص�������
    texEarth = load_texture("E:\\acm\\OpenGL\\src\\Earth.bmp");
}

void display(void)
{
    // �����ɫ����Ȼ�����
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // �����ӽ�
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75, 1, 1, 21);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1, 2, 2, 0, 0, 0, 0, 0, 1);

    // ��������ӳ��
    glEnable(GL_TEXTURE_2D);

    // �󶨵�������
    glBindTexture(GL_TEXTURE_2D, texEarth);

    glPushMatrix();

    glScalef(scale, scale, scale);  // Ӧ������
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    // ������������
    GLUquadricObj* quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);
    gluSphere(quadric, 1, 50, 50); // ���ư뾶Ϊ1�����壬ϸ��20x20
    gluDeleteQuadric(quadric);

    glPopMatrix();
    // ��������ӳ��
    glDisable(GL_TEXTURE_2D);

    //// ����֧��
    //glColor3f(0.8f, 0.8f, 0.8f); // ֧����ɫ

    //// �����ķ�֮һԲ��
    //glPushMatrix();
    //glTranslatef(1.0, 0.0, 0); // �ƶ��������Ҳ�
    //glRotatef(-90.0, 0.0, 1.0, 0.0); // ��ת90�ȣ�ʹ�䴹ֱ�ڵ���
    //glBegin(GL_LINE_LOOP);
    //for (int i = 0; i <= 90; ++i) {
    //    float angle = PI * i / 180.0;
    //    glVertex3f(cos(angle), sin(angle), 0);
    //}
    //glEnd();
    //glPopMatrix();

    //// ����Բ�����²�Բ��
    //glPushMatrix();
    //glTranslatef(0, -2.0, 0); // �ƶ���Բ���²�
    //GLUquadricObj* cylinder = gluNewQuadric();
    //gluQuadricDrawStyle(cylinder, GLU_FILL); // ʵ�Ļ���
    //gluQuadricNormals(cylinder, GLU_SMOOTH); // ƽ������
    //gluCylinder(cylinder, 0.1, 0.1, 1.0, 20, 20); // ����Բ����
    //gluDeleteQuadric(cylinder);

    //// ����Բ����ײ���Բ�ε���
    //glBegin(GL_POLYGON);
    //for (int i = 0; i < 20; ++i) {
    //    float angle = 2 * PI * i / 20;
    //    glVertex3f(0.1 * cos(angle), -2.0, 0.1 * sin(angle));
    //}
    //glEnd();

    //glPopMatrix();

    // ����������
    glutSwapBuffers();
}



// argc->�����в����ܸ���
// argv[0]->��ִ�г�����  argv[i]->��i������

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

    
    
    // ע��ص�����
    
    //�Զ���ת

     // ��ʼ�� OpenGL �͹���
    init();

    glutDisplayFunc(&display);
    //glutKeyboardFunc(&grab);
    glutIdleFunc(&idle);

    //�ֶ���ת
    // ע��ص�����
    /*glutDisplayFunc(&SpinHumanly);
    glutMouseFunc(&mouse);
    glutMotionFunc(&motion);
    glutIdleFunc(&idle);*/
    createMenu();
    glutKeyboardFunc(keyboard);  // ע������¼�������



    // ��ʼ�� OpenGL
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);


    // ���ص�������
   /* texEarth = load_texture("E:\\acm\\OpenGL\\src\\Earth.bmp");*/


    // ���� GLUT ��ѭ��
    glutMainLoop();



    return 0;

    

}

