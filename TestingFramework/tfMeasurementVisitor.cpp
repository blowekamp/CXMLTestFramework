//  $Id: MeasurementVisitor.cpp,v 1.5 2003-12-12 20:20:52 blowek1 Exp $
// ===========================================================================
//
//                            PUBLIC DOMAIN NOTICE
//            Office of High Performance Computing and Communications
//
//  This software/database is a "United States Government Work" under the
//  terms of the United States Copyright Act.  It was written as part of
//  the author's official duties as a United States Government employee and
//  thus cannot be copyrighted.  This software is freely available
//  to the public for use. The National Library of Medicine and the U.S.
//  Government have not placed any restriction on its use or reproduction.
//
//  Although all reasonable efforts have been taken to ensure the accuracy
//  and reliability of the software and data, the NLM and the U.S.
//  Government do not and cannot warrant the performance or results that
//  may be obtained by using this software or data. The NLM and the U.S.
//  Government disclaim all warranties, express or implied, including
//  warranties of performance, merchantability or fitness for any particular
//  purpose.
//
//  Please cite the author in any work or product based on this material.
//
// ===========================================================================
//

/// \file
/// \author  Bradley Lowekamp
/// \version $Revision: 1.5 $
/// \brief  
///
///

#include "tfMeasurementVisitor.h"
#include "tfMeasurement.h"
#include "tfDiff.h"
#include <sstream>

namespace testutil {


  MeasurementVisitor::~MeasurementVisitor(void) {}

  void MeasurementVisitor::VisitMeasurement(Measurement &m) {}

  void MeasurementVisitor::VisitMeasurementFile(MeasurementFile &m) {
    this->VisitMeasurement(m);
  }

  void MeasurementVisitor::VisitDataMeasurement(DataMeasurement &m) {
    this->VisitMeasurement(m);
  }   

  void MeasurementVisitor::VisitTextData(TextData &m) {
    this->VisitDataMeasurement(m);
  }

  void MeasurementVisitor::VisitPlainText(PlainText &m) {
    this->VisitTextData(m);
  }

  void MeasurementVisitor::VisitStringText(StringText &m) {
    this->VisitTextData(m);
  }
  
  void MeasurementVisitor::VisitNumericData(NumericData &m) {
    this->VisitDataMeasurement(m);
  }
  
  void MeasurementVisitor::VisitIntegerNumeric(IntegerNumeric &m) {
    this->VisitNumericData(m);
  }
  
  void MeasurementVisitor::VisitFloatNumeric(FloatNumeric &m)  {
    this->VisitNumericData(m);
  }

  void MeasurementVisitor::VisitDoubleNumeric(DoubleNumeric &m)  {
    this->VisitNumericData(m);
  }
  
  void MeasurementVisitor::VisitBooleanNumeric(BooleanNumeric &m)  {
    this->VisitNumericData(m);
  }

  DifferenceVisitor::~DifferenceVisitor(void) {}
  
  void DifferenceVisitor::SetInputMeasurement(Measurement *m) { this->_input = m;}
  
  void DifferenceVisitor::SetOutStream(std::ostream &_os) { this->os = &_os;}
    
  void DifferenceVisitor::VisitMeasurement(Measurement &m) {
    Measurement &input = *this->_input; 
    
    this->AddPrefixesToNames(m, input);
    
    this->GetOutStream() << m << std::endl;
    this->GetOutStream() << input << std::endl;
  }


  
  void DifferenceVisitor::VisitPlainText(PlainText &m) {
    Measurement &input = *this->_input; 
    
    std::ostringstream ostr;
    Diff(input.GetContent(), m.GetContent(), ostr);
    /////// THIS SHOULD BE PLAINTEXT, BUT DART DOES NOT SUPPORT IT YET!!
    PlainText diff;
    diff.SetAttributeName(std::string("Difference ")+m.GetAttributeName());
    diff.SetContent(ostr.str());
    
    this->GetOutStream() << diff << std::endl;
  }
  
  std::ostream &DifferenceVisitor::GetOutStream(void) const {
    return *this->os;
  }

  void DifferenceVisitor::AddPrefixesToNames(Measurement &test, Measurement &input) {
      
    input.SetAttributeName(std::string("Baseline ") + input.GetAttributeName());
    test.SetAttributeName(std::string("Test ") + test.GetAttributeName());
  }

}


//
// ===========================================================================
//
// $Log: not supported by cvs2svn $
// Revision 1.4  2003/12/12 19:09:46  blowek1
// added a work around for dart
//
// Revision 1.3  2003/12/05 20:46:57  blowek1
// added numeric classes
//
// Revision 1.2  2003/12/04 20:01:14  blowek1
// mostly added documentation
//
// Revision 1.1  2003/12/03 16:16:39  blowek1
// incremental check in
//
//
//
// ===========================================================================
//
