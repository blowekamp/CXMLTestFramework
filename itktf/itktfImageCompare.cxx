
#include "itktf/itktfRegression.h"

class itktfImageCompareRegressionTest
  : public itk::Regression
{
public:
  
  int Test( int argc, char **argv )
  {
    if ( argc < 2 )
      {
      std::cerr << "Usage: "<< std::endl;
      std::cerr << "\t" << argv[0] << " ( filename | --intensityTolerance real | --numberOfPixelTolerance uint | --radiusTolerance uint )*" << std::endl;
      std::cerr << std::endl;
      std::cerr << "The primary argument is list of image files to compare to an input XML file via the \"-I filename.xml\" argument from the regression framework. Additainlly, the \"--\" arguments can applied during the processing, to affect the subsequent image files." << std::endl;
      
      }

    double intensityTolerance = 0;
    unsigned int numberOfPixelTolerance = 0;
    unsigned int radiusTolerance = 0;
    unsigned int imageNumber = 0;
    

    // process arguments
    for ( int i = 1; i < argc; ++i )
      {
      std::string argvi = argv[i];
      

      // if it begins with a dash then it will have a value that follows
      if ( argvi[0] == '-' )
        {
        if ( argvi == "--intensityTolerance" )
          {
          // increment i and check there is the double value;
          if ( ++i >= argc ) 
            {
            std::cerr << "Expected double to follow " << argvi << std::endl;
            return EXIT_FAILURE;
            }

          // try to convert argument to double
          std::istringstream iss( argv[i] );
          iss >> intensityTolerance;
          if ( iss.fail() )
            {
            std::cerr << "Expected double to follow " << argvi << " but got \"" << argv[i] << "\"" << std::endl;
            return EXIT_FAILURE;
            }
          }
        else if ( argvi == "--numberOfPixelTolerance" )
          {
          // increment i and check there is the unsigned int value;
          if ( ++i >= argc ) 
            {
            std::cerr << "Expected unsigned int to follow " << argvi << std::endl;
            return EXIT_FAILURE;
            }

          // try to convert argument to double
          std::istringstream iss( argv[i] );
          iss >> numberOfPixelTolerance;
          if ( iss.fail() )
            {
            std::cerr << "Expected unsigned int to follow " << argvi << " but got \"" << argv[i] << "\"" << std::endl;
            return EXIT_FAILURE;
            }
          }
        else if ( argvi == "--radiusTolerance" )
          {
          // increment i and check there is the unsigned int value;
          if ( ++i >= argc ) 
            {
            std::cerr << "Expected unsigned int to follow " << argvi << std::endl;
            return EXIT_FAILURE;
            }
          
          // try to convert argument to double
          std::istringstream iss( argv[i] );
          iss >> radiusTolerance;
          if ( iss.fail() )
            {
            std::cerr << "Expected unsigned int to follow " << argvi << " but got \"" << argv[i] << "\"" << std::endl;
            return EXIT_FAILURE;
            }
          }
        else
          {          
          std::cerr << "Unknown argument: \"" << argvi << "\"" << std::endl;
          return EXIT_FAILURE;
          }
        }
      else
        {
        // no dash we assume it will be a file
        std::string testImage = argvi;

        // create measurement name with sequential numbers
        std::ostringstream oss;
        oss << "ImageFile" << imageNumber++;
        
        this->SetImageInsightTolerance( intensityTolerance,
                                        numberOfPixelTolerance, 
                                        radiusTolerance );
        
        this->MeasurementInsightFileImage( testImage, oss.str() );
        }
      }
    return EXIT_SUCCESS;
  }
    
};

int main( int argc, char * argv[] )
{
  itktfImageCompareRegressionTest test;
  return test.Main( argc, argv );
}
