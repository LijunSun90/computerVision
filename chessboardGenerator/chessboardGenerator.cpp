#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

// chessboardGenerator.cpp
// Function: generate a chessboard.
// Calling conventin:
// chessboardGenerator blockSize board_w board_h
//

void help(char* argv[]){
    printf("\n\n"
    " Calling convention:\n"
    "   chessboardGenerator blockSize board_w board_h  \n"
    "\n"
    " WHERE:\n\n"
    " blockSize        --the number of pixels per square side.\n\n"
    " board_w, board_h --the number of interior corners along the\n"
    "                    row and columns respectively.\n"
    "\n"
    " Tip: \n"
    "   In practice, using an even-odd asymmetry chessboard, for example, (7, 8),\n"
    "   is convenient, since it has only ne symmetry axis, so the chessboard\n"
    "   orientation can always be defined.\n"
    "\n"
    "   In practice, for high-quality results, it needs at least 10 images\n"
    "   of a 7 x 8 or larger chesobard.\n"
    "\n"
    " For example, \n"
    "   chessboardGenerator 80 7 8\n"
    "\n"
    " Hit ESC to quit\n\n");
}

int main(int argc, char* argv[]){
    int blockSize = 80;
    int board_w = 5 + 1;
    int board_h = 6 + 1;

    if (argc < 3){
        cout << "\nERROR: Wrong number of input parameters";
        help(argv);
        return -1;
    }
    help(argv);

    blockSize = atoi(argv[1]);
    board_w = atoi(argv[2]) + 1;
    board_h = atoi(argv[3]) + 1;

    cv::Size image_sz = cv::Size(board_w * blockSize, board_h * blockSize);

    cv::Mat chessboard(image_sz.width, image_sz.height, CV_8UC3, cv::Scalar::all(0));
    unsigned char color = ~0;


    for(int col = 0; col < image_sz.height; col = col + blockSize){
        if (col != 0 && board_w % 2 == 0) color = ~color;  

        for(int row = 0; row < image_sz.width; row = row + blockSize){
            cv::Mat ROI = chessboard(cv::Rect(col, row, blockSize, blockSize));
            ROI.setTo(cv::Scalar::all(color));
            // cv::imshow("chessboard", chessboard);
            // cv::waitKey(0);
            color = ~color;
        }
    }

    cv::imshow("chessboard", chessboard);
    if((cv::waitKey(0) & 255) == 27){ // ASCII of ESC is 27.
        // SAVE THE CHESSBOARD.
        cout << "\n\n*** DONE! ***\n" <<
        "\nStoring chessboard.jpg file...\n\n";

        cv::imwrite("chessboard.jpg", chessboard);
    }


    return 0;
}