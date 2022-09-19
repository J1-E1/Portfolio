#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
#include <time.h>
#include <iostream>
#include <string>
#include <chrono>

using namespace std;
using namespace cv;
using namespace chrono;
// test timer
class Timer
{
public:
    Timer()
    {
        m_StartTimepoint = high_resolution_clock::now();
    }
    ~Timer()
    {
        Stop();
    }
    void Stop()
    {
        auto endTimepoint = chrono::high_resolution_clock::now();
        auto start = chrono::time_point_cast<chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
        auto end = chrono::time_point_cast<chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();

        auto duration = end - start;
        double ms = duration * 0.001;

        std::cout << duration << "us (" << ms << "ms)\n";
    }

private:
    chrono::time_point<chrono::high_resolution_clock> m_StartTimepoint;
};

cv::Mat EnergyImg(Mat &img)
{
    // energy function
    Mat energy_img;
    Mat sobel_x, sobel_y;

    Sobel(img, sobel_x, CV_64F, 1, 0);
    convertScaleAbs(sobel_x, sobel_x);

    Sobel(img, sobel_y, CV_64F, 0, 1);
    convertScaleAbs(sobel_y, sobel_y);
    addWeighted(sobel_x, 0.5, sobel_y, 0.5, 0, energy_img);
    energy_img.convertTo(energy_img, CV_64F);

    return energy_img;
}

/*For completeness, note that (i,j) refers to (row,column),
or in cartesian coordinates: (y,x).
This is the math/matrix notation,
 not the typical image processing
 notation which usually uses (x,y) - or (column, row).*/
vector<int> FindSeam(Mat &energy_map)
{
    //(y,x)  , mat.at(row, col)
    Point min_point, max_point;
    double min_val, max_val;

    int y_size = energy_map.rows;
    int x_size = energy_map.cols;
    double left_val, mid_val, right_val;

    vector<int> seam;

    // find the lowest point
    Mat row = energy_map.row(y_size - 1);
    minMaxLoc(row, &min_val, &max_val, &min_point, &max_point);

    seam.resize(y_size);
    // first node of the seam
    seam[y_size - 1] = min_point.x;
    int x = min_point.x;
    // same y, find one way back to the top,0<=x<=x_size-1
    for (int i = y_size - 2; i >= 0; i--)
    {
        left_val = energy_map.at<double>(i, max(x - 1, 0));           // left one,left edge
        mid_val = energy_map.at<double>(i, x);                        // same cols but
        right_val = energy_map.at<double>(i, min(x + 1, x_size - 1)); // right one

        if (min(left_val, mid_val) > right_val) // move to right x +1
        {
            x++;
        }
        else if (min(left_val, right_val) > mid_val) // stay in this x+0
        {
            x += 0;
        }
        else if (min(mid_val, right_val) > left_val) // move to left x-1
        {
            x--;
        }
        x = min(max(x, 0), x_size - 1); // reach left edge(>=0) and right edge(<=col-1).
        seam[i] = x;                    // record the index of all min node.
    }
    return seam;
}
void RemoveSeam(Mat &img, Mat &img_carved, vector<int> seam)
{
    int rows = img.rows;
    int cols = img.cols;
    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            if (col <= seam[row])
                img_carved.at<Vec3b>(row, col) = img.at<Vec3b>(row, col);
            else
                img_carved.at<Vec3b>(row, col) = img.at<Vec3b>(row, col + 1); // x+1
        }
    }
}
void SeamCarving(Mat &img, int times)
{
    int rows = img.rows;
    int cols = img.cols;
    Mat img_carved(rows, cols - 1, CV_16F);
    for (int i = 0; i < times; i++)
    {
        Mat energy_img = EnergyImg(img);
        vector<int> seam = FindSeam(energy_img);
        RemoveSeam(img, img_carved, seam);
    }
    img = img_carved;
}

// cd to build file, then
//./Seam_carving in.png Out.png 100
int main(int argc, char **argv)
{
    String file_base = "./Img/";
    String Input = file_base + argv[1];
    String Output = file_base + argv[2];
    String times = argv[3];

    cv::Mat img = imread(Input);
    if (img.empty()) // Check for invalid input
    {
        cout << "Can not find this image" << std::endl;
        return -1;
    }

    cout << " processing....." << endl;
    // cout << "whole prossing cost: ";
    {
        // Timer timer;
        SeamCarving(img, stoi(times));
        // Write result to the file
        imwrite(Output, img);
    }
    return 0;
}
