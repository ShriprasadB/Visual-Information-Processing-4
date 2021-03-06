#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main(int argc, char **argv) {
 
  
  string filename;
  cout << "Enter image name with full path " << endl;
  cin >> filename;
  

  
  Mat I = imread(filename, CV_LOAD_IMAGE_GRAYSCALE);
  Mat F = I.clone();
  Mat K = I.clone();
  Mat L = I.clone();
  Mat M = I.clone();
  Mat Result = I.clone();
  
  //pointer creation
  Mat *image = &I;

  //to check if images get loaded
  if(!I.data || !F.data) {
    cout << "ERROR: Could not load image data." << endl;
    return -1;
  }
  
 

//In order to get binary image put F at Result

  for(int i = 0; i < I.rows; i++)
  {

    for(int j = 0; j < I.cols; j++)
    {
      if(I.at<uchar>(i,j)>185)
        F.at<uchar>(i,j)=255;
      else
        F.at<uchar>(i,j)=0;
    }
  }
  for(int i = 0; i < K.rows; i++)
  {

    for(int j = 0; j < K.cols; j++)
    {
      K.at<uchar>(i,j)=0;
      Result.at<uchar>(i,j)=0;
      M.at<uchar>(i,j)=0;

    }
  }

  
    
  // for binary image opening result put K
   
  int sum=9;
  int count=0;

  // erosion

  for (int i=0; i<F.rows; i++){
    for (int j=0; j<F.cols; j++) {
      if ((int)F.at<uchar>(i,j)==255) {     // foreground pixel ==  1
        count = 0;

        for (int m=0; m<3; m++){
          for (int n=0; n<3; n++) {
            if ((i-2+m) >= 0 && (j-2+n) >=0 && (i-2+m) < F.rows && (j-2+n) < F.cols){
              if((int)F.at<uchar>(i-2+m,j-2+n)==255){
                count ++;
              }
            }
          }
        }
        // set 255 a pixel in erosion
        if (sum == count){
          
          K.at<uchar>(i,j) = 255;
        }
        

      }
    }
  }

  // dilation


  for (int i=0; i<K.rows; i++){
    for (int j=0; j<K.cols; j++) {
      if ((int)K.at<uchar>(i,j)==255) {       
        // if the foreground pixel != zero, then fill in the pixel
        for (int m=0; m<3; m++){
          for (int n=0; n<3; n++) {
            if ((i-2+m) >= 0 && (j-2+n) >=0 && (i-2+m) < K.rows && (j-2+n) < K.cols)
              if ((int)K.at<uchar>(i-2+m, j-2+n)!=255)
                K.at<uchar>(i-2+m, j-2+n) = 255;
          }
        }
      }
    }
  }

  for(int a=2; a<K.rows;a++){
        for( int b=2 ;b<K.cols; b++){
            if((int)(K.at<uchar>(a,b))==255){
              Result.at<uchar>(a,b)=I.at<uchar>(a,b);
            }
        }
    }

   //put M for grayscale opening result
  // grayscale erosion
  int p[9];
  int x[9];
  int l=0;
   for (int i=0; i<I.rows; i++)
    for (int j=0; j<I.cols; j++) {
      l = 0;
      for (int m=0; m<3; m++){
        for (int n=0; n<3; n++) {
          if ((i-1+m) >= 0 && (j-1+n) >=0 && (i-1+m) < I.rows && (j-1+n) < I.cols){
            p[l] = I.at<uchar>(i-1+m, j-1+n) - 50;
            l++;
          }
        }
      }


        
        for (int i = 0; i < l; i++) {
                for (int j = 0; j < i; j++) {
                        int tmp = p[i];
                        p[i] = p[j];
                        p[j] = tmp;
                }
        }


      L.at<uchar>(i,j) = p[0];
    }

//grayscale dilation    
  for (int i=0; i<I.rows; i++){
    for (int j=0; j<I.cols; j++) {
      l = 0;
      for (int m=0; m<3; m++){
        for (int n=0; n<3; n++) {
          if ((i-1+m) >= 0 && (j-1+n) >=0 && (i-1+m) < I.rows && (j-1+n) < I.cols){
            x[l] =L.at<uchar>(i-1+m, j-1+n) + 120;
            l++;
          }
        }
      }


        for (int i = 0; i < l; i++) {
                for (int j = 0; j < i; j++) {
                        int tmp = x[i];
                        x[i] = x[j];
                        x[j] = tmp;
                }
        }

      M.at<uchar>(i,j) = x[l-1];
    }
  }
   
  namedWindow("Unix Sample Skeleton");
   
  bool loop = true;
  while(loop) {
    imshow("Unix Sample Skeleton", *image);
    
    switch(cvWaitKey(15)) {
      case 27:  //press ESC to exit
        loop = false;
        break;
      case 32:  //press spacebar to swap images
        if(image == &I) image = &K;
        else image = &I;
        break;
      default:
	break;
    }
  }
}
