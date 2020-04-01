#include "variable.h"
#define PI 3.14159265

void OpenCamera(){
    // Gunakan file di dalam komputer
    cap.open("/media/azkahariz/Local Disk1/Misc/Bomb Scoring/Video/dataset_bomb_datar.mp4");
    // Cek apakah kamera terbuka
    if(!cap.isOpened()){
        cerr << "ERROR! Unable to open camera \n";
    }
}

void ReadReference()
{
    // Membaca gambar referensi
    cap >> imReference;
    cvtColor(imReference,imReference, CV_BGR2GRAY);
    resize(imReference, imReference, Size(448,448));
    //GaussianBlur(imReference,imReference,Size(13,13),0);

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
    GaussianBlur(src,frame,Size(3,3),0);
    cvtColor(frame,frame,CV_BGR2GRAY);
    resize(frame, frame, Size(448,448));
    pBackSub->apply(frame,fgMask);
    //fgMask = frame - imReference;
    //fgMask = fgMask - 30;
    double min, max;
    minMaxIdx(fgMask, &min, &max);
    fgMask = fgMask*(255/max);

    cout <<  "max pixel: " << max << endl;
    cout <<  "min pixel: " << min << endl;
    morphologyEx(fgMask,fgMask,MORPH_OPEN,element);
    dilate(fgMask, dilatasi, Mat::ones(30,30,CV_8UC1));
    findContours(dilatasi, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
    //    vector<Rect> boundRect( contours.size() );

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
        BackgroundSubtraction();
        cout << "Bomb terdeteksi : " << contours.size() << endl;
        vector<Rect> boundRect( contours.size() );

        // Apabila ada contour yang ditemukan
        if (contours.size() > 0)
        {
            for(int i = 0; i < (int)contours.size(); i++)
            {
                double area = contourArea(contours[i]);
                if(area > 0)
                {
                    cout << "area contours-" << i+1 << ": " << area << endl;
                    boundRect[i] = boundingRect(contours[i]);
                    rectangle( src, boundRect[i].tl(), boundRect[i].br(), 0,0,255,2 );
                }
            }
        }
        imshow("Process",src);
        imshow("FG Mask", fgMask);
        waitKey(33);
    }
    return 0;

}
