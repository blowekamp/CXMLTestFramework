#ifndef __itktfRegression_h
#define __itktfRegression_h

#include "TestingFramework/tfRegressionTest.h"

#include "itktfRegressionSupport.h"
#include "itktfCompareVisitor.h"
#include "itktfDifferenceVisitor.h"
#include "itktfDifferenceImageFilter.h"

#include "itkExtractImageFilter.h"
#include "itkImageFileReader.h"

#include <sstream>

#include "itkSize.h"
#include "itkIndex.h"
#include "itkImageRegion.h"
#include "itkPoint.h"
#include "itkVector.h"
#include "itkMatrix.h"
#include "itkImageFileWriter.h"

namespace itk {


/// \brief a base class of implementing itk tests with the TestingFramework
class Regression 
  : public testutil::RegressionTest 
{
public:
  Regression(void); 

  virtual ~Regression(void);

  ///@{
  /// \brief setting the tolerance for comparing Insight image file
  /// measurements 
  /// 
  /// These values are passed to itk::DifferenceImageFilter. 
  /// \param intensityTolerance the difference between two value before the pixels are considered different
  /// \param numberOfPixelTolerance the number of different pixel before the images are considered different
  /// \param radiusTolerance a search radius to find a simular pixel
  ///
  /// \sa itk::DifferenceImageFilter
  /// 
  virtual void SetImageInsightToleranceOff( void );
  virtual void SetImageInsightTolerance( double intensityTolerance, 
                                         unsigned int numberOfPixelTolerance = 0,
                                         unsigned int radiusTolerance = 0 );
  ///@}

  
  int Main( int argc, char *argv[] );

  /// \brief Generates unique output filenames based on the command
  /// line arguments.
  ///
  /// The generated filename assumes that the arguments are unquie for
  /// each test. The return is of the following format: argv0_####_*.fileExtension
  /// Where argv0 is the first argument passed to the Main
  /// methods. The #### is a hash generated by the arguments to Main, and
  /// finally, the * is a sequential number incremented each time the
  /// methods is called.
  ///
  std::string GenerateFileName( std::string fileExtension, std::string rootPath = "" ) const;

protected:
    
  /// \brief Performs a measurement for an itk image file
  ///
  /// \param fileName the name of an image file for the measurement
  /// \param name gives this measuement a name
  int MeasurementInsightFileImage( const std::string &fileName, const std::string &name); 

  template < typename TImageType >
  int MeasurementInsightImage( const typename TImageType::Pointer image, const std::string &name )
  {
    // todo need to have a better output directory!
    typedef TImageType ImageType;
    std::string fileName = this->GenerateFileName( "mha" );
    typedef itk::ImageFileWriter<ImageType> WriterType;
    typename WriterType::Pointer writer = WriterType::New();
    writer->SetFileName( fileName );
    writer->SetInput( image );
    writer->Update();
    
    return this->MeasurementInsightFileImage( fileName, name );      
  }


  template <unsigned int Dimension>
  int MeasurementInsightSize( const Size<Dimension> &size, const std::string &name, bool tolerant = false ) 
  {
    int ret = 0;
    for (unsigned int i = 0; i < Dimension; ++i) 
      {
      std::ostringstream nameWithIndex;
      nameWithIndex << name << "_" << i;
      ret += this->MeasurementNumericInteger( size[i], nameWithIndex.str(), tolerant);
      }
    return ret;
  }

  template <unsigned int Dimension>
  int MeasurementInsightIndex( const Index<Dimension> &index, const std::string &name, bool tolerant = false ) 
  {
    
    int ret = 0;
    for (unsigned int i = 0; i < Dimension; ++i) 
      {
      std::ostringstream nameWithIndex;
      nameWithIndex << name << "_" << i;
      ret += this->MeasurementNumericInteger( index[i], nameWithIndex.str(), tolerant);
      }
    return ret;
  }

  template <unsigned int Dimension>
  int MeasurementInsightRegion( const ImageRegion<Dimension> &region, const std::string &name, bool tolerant = false )
  {
    int ret = 0;
    ret += this->MeasurementInsightIndex( region.GetIndex(), name + " Index", tolerant );
    ret += this->MeasurementInsightSize( region.GetSize(), name + " Size", tolerant );
    return ret;
  }

  template <typename T, unsigned int Dimension>
  int MeasurementInsightPoint( const Point<T, Dimension> &point, const std::string &name, bool tolerant = true ) 
  {    
    int ret = 0;
    for (unsigned int i = 0; i < Dimension; ++i) 
      {
      std::ostringstream nameWithIndex;
      nameWithIndex << name << "_" << i;
      ret += this->MeasurementNumericDouble( point[i], nameWithIndex.str(), tolerant);
      }
    return ret;
  }

  template <typename T, unsigned int Dimension>
  int MeasurementInsightVector( const Vector<T, Dimension> &vector, const std::string &name, bool tolerant = true ) 
  {    
    int ret = 0;
    for (unsigned int i = 0; i < Dimension; ++i) 
      {
      std::ostringstream nameWithIndex;
      nameWithIndex << name << "_" << i;
      ret += this->MeasurementNumericDouble( vector[i], nameWithIndex.str(), tolerant);
      }
    return ret;
  }

  template <typename T, unsigned int Dimension>
  int MeasurementInsightFixedArray( const FixedArray<T, Dimension> &array, const std::string &name, bool tolerant = true ) 
  {    
    int ret = 0;
    for (unsigned int i = 0; i < Dimension; ++i) 
      {
      std::ostringstream nameWithIndex;
      nameWithIndex << name << "_" << i;
      ret += this->MeasurementNumericDouble( array[i], nameWithIndex.str(), tolerant);
      }
    return ret;
  }

  template <typename T, unsigned int NRows, unsigned int NColumns>
  int MeasurementInsightMatrix( const Matrix<T, NRows, NColumns> &matrix, const std::string &name, bool tolerant = true ) 
  {    
    int ret = 0;
    for (unsigned int i = 0; i < NRows; ++i) 
      {
      for (unsigned int j = 0; j < NColumns; ++j) 
        {
        std::ostringstream nameWithIndex;
        nameWithIndex << name << "_" << i << "_" << j;
        ret += this->MeasurementNumericDouble( matrix[i][j], nameWithIndex.str(), tolerant);
        }
      }
    return ret;
  }

  /// overridden to return itk::DiferenceVisitor to allow differencing of "image/itk"
  testutil::DifferenceVisitor *CreateDifferenceVisitor(void) const;

  /// overridden to return itk::CompareVisitor to allow comparing of "image/itk"
  testutil::CompareVisitor *CreateCompareVisitor(void) const;

  // \brief overriden to parse insight specific arguemnts
  //
  // todo this is currently not implemented, arguments such as number
  // of threads, debug mode, and tollerance could be placed here
  // void ParseAndRemoveArguments(int &argc, char *argv[]);

public:

  /// \brief Computes the differences between two file images.
  ///
  template< typename ImageType >
  static unsigned long CompareImage( const fileutil::PathName testFileName, 
                                        const fileutil::PathName baselineFileName,
                                        double intensityTolerance = 0.0,
                                        unsigned int numberOfPixelsTolerance = 0, 
                                        unsigned int radiusTolerance = 0 ) 
  {
    typedef itk::ImageFileReader<ImageType> ReaderType;

    typename ReaderType::Pointer testReader = ReaderType::New();
    testReader->SetFileName( testFileName.GetPathName() );
    testReader->Update();

    typename ReaderType::Pointer baselineReader = ReaderType::New();
    baselineReader->SetFileName( baselineFileName.GetPathName() );
    baselineReader->Update();

    return CompareImage<ImageType>( testReader->GetOutput(),
                                    baselineReader->GetOutput(),
                                    intensityTolerance,
                                    numberOfPixelsTolerance,
                                    radiusTolerance );
  }

  ///@{
  /// \brief Computes the difference between two images. 
  /// 
  ///
  /// \param testImage an image which accuracy is in question
  /// \param baselineImage an image that is considered the ground truth and correct
  ///
  /// These values are passed to itk::tf:DifferenceImageFilter. 
  /// \param intensityTolerance the difference between two value before the pixels are considered different
  /// \param numberOfPixelTolerance the number of different pixel before the images are considered different
  /// \param radiusTolerance a search radius to find a simular pixel
  ///
  /// \return the number of pixels with a value outside the thresholds
  /// established by the parameters
  ///
  /// \sa itk::tf::DifferenceImageFilter
  /// 
  template< typename ImageType >
  static unsigned long CompareImage( typename ImageType::ConstPointer testImage, 
                                        typename ImageType::ConstPointer baselineImage,
                                        typename ImageType::RegionType region ) 
  { return CompareImage<ImageType>( testImage, baselineImage, 0.0, 0, 0, region ); }

  template< typename ImageType >
  static unsigned long CompareImage( typename ImageType::ConstPointer testImage, 
                                        typename ImageType::ConstPointer baselineImage,
                                        double intensityTolerance = 0.0,
                                        unsigned int numberOfPixelsTolerance = 0, 
                                        unsigned int radiusTolerance = 0,
                                        typename ImageType::RegionType region = typename ImageType::RegionType() ) 
  {
    unsigned long status = 0;
    
    
    if ( region != typename ImageType::RegionType() ) 
      {
      // verify that the requested compare region is contained in the
      // base line region

      // extract only the specified region
      typedef itk::ExtractImageFilter<ImageType, ImageType> ExtractImageFilter;
      typename ExtractImageFilter::Pointer extractor = ExtractImageFilter::New();
      extractor->SetExtractionRegion( testImage->GetLargestPossibleRegion() );
      extractor->SetInput( baselineImage );
    

      typedef itk::tf::DifferenceImageFilter<ImageType,ImageType> DiffType;
      typename DiffType::Pointer diff = DiffType::New();
      diff->SetValidInput( extractor->GetOutput() );
      diff->SetTestInput( testImage );
      diff->SetMagnitudeThreshold( intensityTolerance );
      diff->SetToleranceRadius( radiusTolerance );
      diff->UpdateLargestPossibleRegion();

      status = diff->GetNumberOfPixelsWithDifferences();
      }
    else 
      {      
      // verify that the sizes of the images are the same
      //
      // If the sizes don't match then we can't compare
      typename ImageType::SizeType baselineSize = baselineImage->GetLargestPossibleRegion().GetSize();
      typename ImageType::SizeType testSize = testImage->GetLargestPossibleRegion().GetSize();
  

      if (baselineSize != testSize)
        {
        return itk::NumericTraits<unsigned long>::max();
        }


      // compare the whole image
      typedef itk::tf::DifferenceImageFilter<ImageType,ImageType> DiffType;
      typename DiffType::Pointer diff = DiffType::New();
      diff->SetValidInput( baselineImage );
      diff->SetTestInput( testImage );
      diff->SetMagnitudeThreshold( intensityTolerance );
      diff->SetToleranceRadius( radiusTolerance );
      diff->UpdateLargestPossibleRegion();

      status = diff->GetNumberOfPixelsWithDifferences();
      }

      return ( status < numberOfPixelsTolerance ) ? 0 : status - numberOfPixelsTolerance ;
  }
  ///@}
                                          

private:
  double m_IntensityTolerance;
  unsigned int m_NumberOfPixelsTolerance;
  unsigned int m_RadiusTolerance;
  mutable unsigned int m_FileNameCount;

  std::list<std::string> m_ArgumentList;

};

}

#endif // __itktfRegression_h
