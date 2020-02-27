#include "variable.h"
#define PI 3.14159265

void OpenCamera(){
    // Menyalakan kamera, 0 = Camera laptop, 1 = Camera USB
    //cap.open(0);
    // Gunakan file di dalam komputer
    cap.open("/media/azkahariz/Local Disk1/Proyek/Bomb Scoring/Video/dataset_bomb_datar.mp4");
    // Cek apakah kamera terbuka
    if(!cap.isOpened()){
        cerr << "ERROR! Unable to open camera \n";
    }
}

void ReadReference()
{
    // Membaca gambar referensi
    cap >> imReference;
    //string refFilename("/media/azkahariz/Local Disk1/Proyek/Bomb Scoring/Rose/gambar/Reference_2.jpg");
    //cout << "Reading reference image : " << refFilename << endl;
    //imReference = imread(refFilename);
    // Mengkonversi gambar referensi menjadi hitam putih
    //cvtColor(imReference, imReference, CV_BGR2GRAY);
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
    //GaussianBlur(imReg,frame,Size(11,11),0);
    GaussianBlur(src,frame,Size(11,11),0);
    pBackSub->apply(frame,fgMask);
    morphologyEx(fgMask,fgMask,MORPH_OPEN,element);
    dilate(fgMask, dilatasi, Mat::ones(20,20,CV_8U));
    findContours(dilatasi, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
    vector<Rect> boundRect( contours.size() );

}

int main()
{
    pBackSub = createBackgroundSubtractorMOG2();
    OpenCamera();
    ReadReference();
    namedWindow("Template", WINDOW_KEEPRATIO);
    pilihTitikReference();
    //namedWindow("Kamera", WINDOW_KEEPRATIO);
    //pilihTitikKamera();
    cout << "Titik template: " << titik << endl;
    //cout << "Titik kamera: "  << titik2 << endl;

    //h = findHomography(titik2,titik);
    //cout << "h :" << h << endl;

    //warpPerspective(src, imReg, h, imReference.size());

    //namedWindow("aligned image", WINDOW_KEEPRATIO);
    //imshow("aligned image",imReg);
    //waitKey(0);

    namedWindow("Process",WINDOW_KEEPRATIO);
    namedWindow("FG Mask",WINDOW_KEEPRATIO);

    for(;;)
    {

        cap >> src;
        //warpPerspective(src, imReg, h, imReference.size());

        //cvtColor(imReg, imRegGray,CV_BGR2GRAY);
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
                //boundRect[i] = boundingRect( Mat(contours[i]) )
                //cout << "area : " << area << endl;
            }
        }

        //        // Circles target
        //        HoughCircles(imRegGray,circlesTarget,HOUGH_GRADIENT, 1, imRegGray.rows/8, 20, 20, 280, 300);
        //        circlesTarget.resize(1);
        //        cout << "Size circlesTarget: " << circlesTarget.size() << endl;
        //        for(size_t i=0; i<circlesTarget.size(); i++) {
        //            Point centerTarget(cvRound(circlesTarget[i][0]), cvRound(circlesTarget[i][1]));
        //            radius = cvRound(circlesTarget[i][2]);
        //            circle(imReg, centerTarget, radius, Scalar(255, 255, 255), 2, 8, 0);
        //            circle(imReg, centerTarget, 1, Scalar(0, 0, 255), 3, 8, 0);
        //        }

        //        // Circles bomb
        //        HoughCircles(fgMask, circlesBomb, HOUGH_GRADIENT, 1, fgMask.rows/8, 20, 20, 10, 70);
        //        cout << "Size circlesBomb : " << circlesBomb.size() << endl;
        //        for(size_t i=0; i<circlesBomb.size(); i++) {
        //            Point centerBomb(cvRound(circlesBomb[i][0]), cvRound(circlesBomb[i][1]));
        //            jarakX = cvRound(circlesBomb[i][0]) - cvRound(circlesTarget[0][0]);
        //            jarakX = jarakX*jarakX;
        //            jarakY = cvRound(circlesBomb[i][1]) - cvRound(circlesTarget[0][1]);
        //            jarakY = jarakY*jarakY;
        //            jarak = sqrt(jarakX + jarakY);
        //            jarak = jarak * (double)(10/(double)radius);
        //            degree = atan((double)jarakY/(double)jarakX) * 180 / PI;
        //            int radiusBomb = cvRound(circlesBomb[i][2]);
        //            ss << "Radius: " << jarak << " m";
        //            JarakText = ss.str();
        //            ss.str("");
        //            ss << "Sudut: " << degree << "derajat";
        //            degreeText = ss.str();
        //            ss.str("");
        //            putText(imReg, JarakText.c_str(), Point(cvRound(circlesBomb[i][0]), cvRound(circlesBomb[i][1])),
        //                    FONT_HERSHEY_SIMPLEX, 0.5 , cv::Scalar(0,0,0));;
        //            putText(imReg, degreeText.c_str(), Point(cvRound(circlesBomb[i][0]), cvRound(circlesBomb[i][1])+15),
        //                    FONT_HERSHEY_SIMPLEX, 0.5 , cv::Scalar(0,0,0));;
        //            JarakText.clear();
        //            degreeText.clear();
        //            circle(imReg, centerBomb, radiusBomb, Scalar(255, 0, 0), 2, 8, 0);
        //        }

        //imshow("Process",imReg);
        imshow("Process",src);
        imshow("FG Mask", fgMask);
        waitKey(33);
    }
    return 0;

}
