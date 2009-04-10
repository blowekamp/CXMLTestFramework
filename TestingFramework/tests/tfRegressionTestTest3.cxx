#include "tfRegressionTest.h"

#include "tfTestSupport.h"

class tfRegressionTestTest3RegressionTest :
  public testutil::RegressionTest 
{
public:
  tfRegressionTestTest3RegressionTest(void) {}
protected:
  virtual int Test( int argc, char *argv[] )
  {
    if (this->GetCompareMode())
      {
      this->MeasurementTextString( "string text value", "TextString" );
      this->MeasurementTextPlain( "this is\n some plain text\n", "TextPlain" );
      
      this->MeasurementNumericInteger( int(0), "NumericInteger" );
      this->MeasurementNumericFloat( float(1.1), "NumericFloat" );
      this->MeasurementNumericDouble( double(30.0/9.0), "NumericDouble" );
      this->MeasurementNumericBoolean( true, "NumericDouble" );

      }
    else 
      {
      this->MeasurementTextString( "difference string text value", "TextString" );
      this->MeasurementTextPlain( "this is different\n some plain text\n", "TextPlain" );
      
      this->MeasurementNumericInteger( int(1), "NumericInteger" );
      this->MeasurementNumericFloat( float(2.2), "NumericFloat" );
      this->MeasurementNumericDouble( double(40.0/9.0), "NumericDouble" );
      this->MeasurementNumericBoolean( false, "NumericDouble" );
      }

    return EXIT_SUCCESS;
  }

};
  

int tfRegressionTestTest3( int argc, char *argv[] )
{
  tfRegressionTestTest3RegressionTest test; 
  int ret = test.Main( argc, argv );

  if ( EXIT_SUCCESS != ret  ) 
    {
    return EXIT_SUCCESS;
    }
  else 
    {
    return EXIT_FAILURE;
    }
  
}
