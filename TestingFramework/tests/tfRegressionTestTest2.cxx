#include "tfRegressionTest.h"

#include "tfTestSupport.h"

class tfRegressionTestTest2RegressionTest :
  public testutil::RegressionTest 
{
public:
  tfRegressionTestTest2RegressionTest(void) {}
protected:
  virtual int Test( int argc, char *argv[] )
  {
    this->MeasurementTextString( "string text value", "TextString" );
    this->MeasurementTextPlain( "this is\n some plain text\n", "TextPlain" );

    this->MeasurementNumericInteger( int(0), "NumericInteger" );
    this->MeasurementNumericFloat( float(1.1), "NumericFloat" );
    this->MeasurementNumericDouble( double(20.0/9.0), "NumericDouble" );
    this->MeasurementNumericBoolean( true, "NumericDouble" );
    

    return EXIT_SUCCESS;
  }

};
  

int tfRegressionTestTest2( int argc, char *argv[] )
{
  tfRegressionTestTest2RegressionTest test; 
  return  test.Main( argc, argv );
}
