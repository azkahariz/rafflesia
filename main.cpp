#include "variable.h"
#define PI 3.14159265

void OpenCamera(){
    // Gunakan file di dalam komputer
    cap.open("/media/azkahariz/Local Disk1/Misc/Bomb Scoring/Video/_TIR0614.MOV");
    // Cek apakah kamera terbuka
    if(!cap.isOpened()){
        cerr << "ERROR! Unable to open camera \n";
    }
}

void ReadReference()
{
    // Membaca gambar referensi
    cap >> imReference;
}

void onMouse(int event, int x, int y, int flags, void* userdata)
{

    if  ( event == EVENT_LBUTTONDOWN )
    {
        titik.push_back(Point2d(x,y));
        circle(imReference, Point(x,y), 5, 256, 1);
    }
}

void onMouse2(int event, int x, int y, int flags, void* userdata)
{

    if  ( event == EVENT_LBUTTONDOWN )
    {
        titik2.push_back(Point2d(x,y));
        circle(src, Point(x,y), 5, 256, 1);
    }
}

void pilihTitikReference()
{
    while(titik.size() < 5)
    {
        setMouseCallback("Template", onMouse, NULL);
        imshow("Template", imReference);
        waitKey(33);
    }
    titik.erase(titik.end());

}

void pilihTitikKamera()
{
    cap >> src;
    cvtColor(src, src, CV_BGR2GRAY);
    while(titik2.size() < 5)
    {
        setMouseCallback("Kamera", onMouse2, NULL);
        imshow("Kamera",src);
        waitKey(33);
    }
    titik2.erase(titik2.end());
}

void BackgroundSubtraction()
{
    GaussianBlur(src,frame,Size(11,11),0);
    pBackSub->apply(frame,fgMask);
    morphologyEx(fgMask,fgMask,MORPH_OPEN,element);
    dilate(fgMask, dilatasi, Mat::ones(20,20,CV_8U));
    findContours(dilatasi, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
    vector<Rect> boundRect( contours.size() );

}

int main()
{
    pBackSub = createBackgroundSubtractorKNN();
    OpenCamera();
    ReadReference();
    namedWindow("Template", WINDOW_KEEPRATIO);
    pilihTitikReference();
    cout << "Titik template: " << titik << endl;
    namedWindow("Process",WINDOW_KEEPRATIO);
    namedWindow("FG Mask",WINDOW_KEEPRATIO);

    for(;;)
    {

        cap >> src;
        cvtColor(src, imRegGray, CV_BGR2GRAY);
        medianBlur(imRegGray, imRegGray, 3);
        BackgroundSubtraction();
        cout << "Bomb terdeteksi : " << contours.size() << endl;
        vector<Rect> boundRect( contours.size() );
        if (contours.size() > 0)
        {
            for(int i = 0; i < contours.size(); i++)
            {
                double area = contourArea(contours[i]);
                cout << "area contours-" << i << ": " << area << endl;
                if(area > 2000)
                {
                    boundRect[i] = boundingRect(contours[i]);
                    rectangle( src, boundRect[i].tl(), boundRect[i].br(), (0,0,255),2 );
                }
            }
        }
        imshow("Process",src);
        imshow("FG Mask", fgMask);
        waitKey(33);
    }
    return 0;

}
