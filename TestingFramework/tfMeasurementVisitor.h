#ifndef MEASUREMENTVISITOR_H 	/* -*- c++ -*- */
#define MEASUREMENTVISITOR_H


//  $Id: MeasurementVisitor.h,v 1.3 2003-12-05 20:46:58 blowek1 Exp $
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
/// \version $Revision: 1.3 $
/// \brief  
///
///

#include <iostream>

namespace testutil {
  

  // foward decalarions so we don't have to include Measurement.h
  class Measurement;
  class MeasurementFile;
  class DataMeasurement;
  class TextData;
  class PlainText;
  class StringText;
  class NumericData;
  class IntegerNumeric;
  class FloatNumeric;
  class DoubleNumeric;
  class BooleanNumeric;
  

  /// \brief class for the visitor design pattern for Measurements
  ///
  /// The default versions of the functions do nothing. The childern
  /// visitor function alls the parent's visitor function.
  class MeasurementVisitor {
  public:
    virtual ~MeasurementVisitor(void) = 0;

    virtual void VisitMeasurement(Measurement &m);

    virtual void VisitMeasurementFile(MeasurementFile &m);

    virtual void VisitDataMeasurement(DataMeasurement &m);

    virtual void VisitTextData(TextData &m);

    virtual void VisitPlainText(PlainText &m);

    virtual void VisitStringText(StringText &m);

    virtual void VisitNumericData(NumericData &m);

    virtual void VisitIntegerNumeric(IntegerNumeric &m);

    virtual void VisitFloatNumeric(FloatNumeric &m);

    virtual void VisitDoubleNumeric(DoubleNumeric &m);

    virtual void VisitBooleanNumeric(BooleanNumeric &m);

  };


  /// \brief Visitor to print out the differences between measurements
  ///
  /// This visitor will be called from the generated test data and
  /// compared with the ground truth input data.
  ///
  /// \note This may modifiy both Measurement objects.
  class DifferenceVisitor 
    : public MeasurementVisitor {
  public:

    virtual ~DifferenceVisitor(void);

    /// \brief sets the input measurement
    ///
    /// This function does not free the measurement. And the
    /// measurement object must be valid when the visitation takes place.
    virtual void SetInputMeasurement(Measurement *m);

    /// \brief set the output stream
    virtual void SetOutStream(std::ostream &_os);

    /// \brief prints out the input and the test measurements
    ///
    /// by default this will be called for all types of measurements
    /// unless overridden
    virtual void VisitMeasurement(Measurement &m);

    /// \brief performs a "diff" on the two texticies and prints
    virtual void VisitPlainText(PlainText &m);

  protected:
    Measurement *_input; // not freed
    
    /// \brief get the out put stream
    virtual std::ostream &GetOutStream(void) const;

    /// \brief modifies the Measuremnt objects to add
    virtual void AddPrefixesToNames(Measurement &test, Measurement &input);

  private:
    
    std::ostream *os; 
    
  };

}


//
// ===========================================================================
//
// $Log: not supported by cvs2svn $
// Revision 1.2  2003/12/03 20:30:39  blowek1
// added documenttation
//
// Revision 1.1  2003/12/03 16:17:01  blowek1
// incremental check in
//
//
//
// ===========================================================================
//

#endif // MEASUREMENTVISITOR_H
    
