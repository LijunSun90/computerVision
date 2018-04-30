/*
* Reading a chessboard's width and height,
* reading and collecting the requested number of views,
* and calibrating the camera.
*/

// Most codes are from the book "Learning OpenCV 3 with some modification."

// calib3_from_disk.cpp
// Calling conventin:
// calib board_w board_h number_of_views
//
// Hit 'p' to pause/unpause, ESC to quit
//

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

void help(char* argv[]){
printf("\n\n"
" Calling convention:\n"
"\n"
"   calib3_from_disk  board_w  board_h  image_list\n"
"\n"
"   or\n"
"\n"
"   calib3_from_disk  board_w  board_h  image_list image_sf\n"
"\n"
" WHERE:\n\n"
" board_w, board_h --the number of corners along the row and columns respectively\n"
" image_list       --space separated list of path/filename of checkerboard images\n"
" image_sf         --the scale factor of the input image used in image processing\n\n"
"\n"
" Hit ‘p’ to pause/unpause, ESC to quit\n\n");
}

int main(int argc, char* argv[]){
    int n_boards = 0; // Will be set by input list.
    float image_sf = 0.5f;
    float delay = 1.f;
    int board_w = 0;
    int board_h = 0;

    if (argc < 3 || argc > 5){
        cout << "\nERROR: Wrong number of input parameters";
        help(argv);
        return -1;
    }
    board_w = atoi(argv[1]);
    board_h = atoi(argv[2]);
    ifstream inImageNames(argv[3]);
    if(argc > 4) image_sf = atof(argv[4]);

    int board_n = board_w * board_h;
    cv::Size board_sz = cv::Size(board_w, board_h);

    string names;
    while(getline(inImageNames, names)) {
        n_boards ++;
        // cout << names << endl;
        // cout << n_boards << endl;
    }
    inImageNames.clear();
    inImageNames.seekg(ios::beg);

    // ALLOCATE STORAGE.
    //
    // The coordinates of image points p in the camera coordinate system 
    // centered on the camera.
    vector< vector<cv::Point2f> > image_points;
    // The coordinates of object points P in the coordiante system 
    // centered on the object.
    vector< vector<cv::Point3f> > object_points;
    // The point p is related to point P by applying a rotation matrix R
    // and a translation vector t to P.

    // Capture corner views: loop until we've got n_boards successful
    // captures (all corners on the board are found).
    //
    cv::Size image_size;
    int successes = 0;
    // n_boards
    for(int frame=0; frame < n_boards; frame++){
        cv::Mat image0, image;
        getline(inImageNames, names);
        image0 = cv::imread(names);
        image_size = image0.size();
        cv::resize(image0, image, cv::Size(), image_sf, image_sf, cv::INTER_LINEAR);
        // Find the board.
        // corners: Locations of the located corners in pixel coordiantes.
        vector<cv::Point2f> corners;
        bool found = cv::findChessboardCorners(image, board_sz, corners);

        // Draw it.
        //
        drawChessboardCorners(image, board_sz, corners, found);

        // If we got a good board, add it to our data.
        //
        if (found){
            // image ^= cv::Scalar::all(255);

            // scale the coordinates back.
            cv::Mat mcorners(corners); // do not copy the data.
            mcorners *= (1./image_sf); // scale the corner coordinates.
            
            image_points.push_back(corners);
            object_points.push_back(vector<cv::Point3f>());
            vector<cv::Point3f>& opts = object_points.back();
            opts.resize(board_n);
            for(int j=0; j<board_n; j++){
                opts[j] = cv::Point3f((float)(j/board_w), (float)(j%board_w), 0.f);
            }
            cout << "Collected our " << (int)image_points.size() <<
            " of " << n_boards << " needed chessboard images\n" << endl;
        }
        cv::imshow("Calibration", image);   // show in color f we did collect the image.
        // cv::imwrite("./chessboardsCorners2/chessboardCorners" + to_string(frame) + ".jpg", image);
        // if(cv::waitKey(0)){ 
        //     // SAVE THE CHESSBOARD.
        //     // cout << "\nStoring chessboardCorners" << frame << ".jpg file...\n\n" << endl;
        //     // cv::imwrite("./chessboardsCorners/chessboardCorners" + to_string(frame) + ".jpg", image);
        // }

        if((cv::waitKey(30) & 255) == 27) return -1;
    } // END COLLECTION FOR LOOP
    inImageNames.clear();
    inImageNames.seekg(ios::beg);

    cv::destroyWindow("Calibration");
    cout << "\n\n*** CALIBRATING THE CAMERA...\n" << endl;

    // CALIBRATING THE CAMERA!
    //
    cv::Mat intrinsic_matrix, distorition_coeffs;
    cv::Mat rvec, tvec;
    double err = cv::calibrateCamera(
        object_points,
        image_points,
        image_size,
        intrinsic_matrix,
        distorition_coeffs,
        rvec,
        tvec,
        cv::CALIB_ZERO_TANGENT_DIST | cv::CALIB_FIX_PRINCIPAL_POINT
    );

    cout << "rvec: \n" << rvec << "\n\n"
    << "tvec: \n" << tvec << "\n\n" << endl;
    
    // SAVE THE INTRINSICS AND DISTORITIONS.
    cout << "*** DONE!\n\nReprojection error is " << err <<
    "\nStoring intrinsics.xml file...\n\n";
    cv::FileStorage fs("intrinsics.xml", cv::FileStorage::WRITE);

    fs << "image_width" << image_size.width << "image_height" << image_size.height
    << "camera_matrix" << intrinsic_matrix << "distortion_coefficients"
    << distorition_coeffs;
    fs.release();

    // EXAMPLE OF LOADING THESE MATRICES BACK IN:
    fs.open("intrinsics.xml", cv::FileStorage::READ);
    cout << "\nimage width: " << (int)fs["image_width"];
    cout << "\nimage height: " << (int)fs["image_height"];

    cv::Mat intrinsic_matrix_loaded, distorition_coeffs_loaded;
    fs["camera_matrix"] >> intrinsic_matrix_loaded;
    fs["distortion_coefficients"] >> distorition_coeffs_loaded;
    cout << "\n\nintrinsic matrix: \n" << intrinsic_matrix_loaded;
    cout << "\n\ndistortion coefficients: \n" << distorition_coeffs_loaded << endl;

    // Build the undistort map which we will use for all
    // subsequent frames.
    //
    cv::Mat map1, map2;
    cv::initUndistortRectifyMap(
        intrinsic_matrix_loaded,
        distorition_coeffs_loaded,
        cv::Mat(),
        intrinsic_matrix_loaded,
        image_size,
        CV_16SC2,
        map1,
        map2
    );

    // cout << "image size: " << image_size << "\n";
    // cout << "map1 size: " << map1.size << "\n";
    // cout << "map2 size: " << map2.size << endl;

    // Just run the camera to the screen, now showing the raw and
    // the undistored image.
    // while(getline(inImageNames, names)) {
    //     cv::Mat image0, image;
    //     image0 = cv::imread(names);
    //     cv::remap(
    //         image0,
    //         image,
    //         map1,
    //         map2,
    //         cv::INTER_LINEAR,
    //         cv::BORDER_CONSTANT,
    //         cv::Scalar()
    //     );
    //     cv::imshow("Distored", image0);
    //     cv::imshow("Undistored", image);
    //     // cv::waitKey(0);
    //     // if((cv::waitKey(30) & 255) == 27) return -1;
    // }

    // cv::waitKey(0);
    // Close the file.
    inImageNames.close();
    return 0;
}
