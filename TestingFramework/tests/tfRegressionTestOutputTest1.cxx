#include "tfRegressionTest.h"

#include "tfTestSupport.h"

class tfRegressionTestOutputTest1RegressionTest :
  public testutil::RegressionTest 
{
public:
  tfRegressionTestOutputTest1RegressionTest(void) {}
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
      this->MeasurementNumericBoolean( true, "NumericDouble" );
      }
      

    return EXIT_SUCCESS;
  }

};
  

int tfRegressionTestOutputTest1( int argc, char *argv[] )
{
  tfRegressionTestOutputTest1RegressionTest test; 
  if ( EXIT_FAILURE == test.Main( argc, argv ) ) 
    {
    return EXIT_SUCCESS;
    }
  else 
    {
    return EXIT_FAILURE;
    }
}
