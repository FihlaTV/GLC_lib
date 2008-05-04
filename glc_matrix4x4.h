/****************************************************************************

 This file is part of the GLC-lib library.
 Copyright (C) 2005-2008 Laurent Ribon (laumaya@users.sourceforge.net)
 Version 0.9.9, packaged on May, 2008.

 http://glc-lib.sourceforge.net

 GLC-lib is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 GLC-lib is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with GLC-lib; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

*****************************************************************************/

//! \file glc_matrix4x4.h interface for the GLC_Matrix4x4 class.

#ifndef GLC_MATRIX4X4_H_
#define GLC_MATRIX4X4_H_

#include <QVector>
#include "glc_vector4d.h"

//! Number of element in the matrix
#define TAILLEMAT4X4 16


//! Matrix Size
#define DIMMAT4X4 4


//////////////////////////////////////////////////////////////////////
//! \class GLC_Matrix4x4
/*! \brief GLC_Matrix4x4 is a 4 dimensions Matrix*/

/*! GLC_Matrix4x4 is used to represent 3D homogeneous 3d transformation \n
 *  GLC_Matrix4x4 is a row first matrix compatible with OpenGL Matrix
 * */
//////////////////////////////////////////////////////////////////////
class GLC_Matrix4x4  
{	
	friend class GLC_Vector4d;

//////////////////////////////////////////////////////////////////////
// Constructor
//////////////////////////////////////////////////////////////////////
public:
//! @name Constructor
//@{
	//! Default Constructor
	/*! Create an indentity Matrix */
	GLC_Matrix4x4();

	//! Construct a Matrix by copy 
	GLC_Matrix4x4(const GLC_Matrix4x4 &Mat);

	//! Contruct a Matrix by an array of 16 elements.
	GLC_Matrix4x4(const double *Tableau);

	//! Construct rotation matrix by a vector and an angle
	GLC_Matrix4x4(const GLC_Vector4d &Vect, const double &dAngleRad)
	{
		setMatRot(Vect, dAngleRad);		
	}

	//! Construct rotation matrix by 2 vectors
	GLC_Matrix4x4(const GLC_Vector4d &Vect1, const GLC_Vector4d &Vect2)
	{
		setMatRot(Vect1, Vect2);		
	}
	
	//! Construct translation matrix by a vector
	GLC_Matrix4x4(const GLC_Vector4d &Vect)
	{
		setMatTranslate(Vect);
	}

	//! Construct translation matrix by 3 coordinates 
	GLC_Matrix4x4(double Tx, double Ty, double Tz)
	{
		setMatTranslate(Tx, Ty, Tz);
	}
//@}

//////////////////////////////////////////////////////////////////////
/*! @name Operator Overload */
//@{
//////////////////////////////////////////////////////////////////////
public:
	//! Matrix cross product
	GLC_Matrix4x4 operator * (const GLC_Matrix4x4 &Mat) const;

	//! Vector transformation
	GLC_Vector4d operator * (const GLC_Vector4d &Vect) const;

//@}

//////////////////////////////////////////////////////////////////////
/*! \name Get Function*/
//@{
//////////////////////////////////////////////////////////////////////
public:
	//! Compute matrix determinant
	const double getDeterminant(void) const;

	//! return a pointer to a row first array of 16 elements
	const double *return_dMat(void) const
	{
		return dMatrice;
	}
	//! Return a vector which contains radians Euler angle of the matrix
	QVector<double> toEuler(void) const;
//@}

//////////////////////////////////////////////////////////////////////
/*! \name Set Function*/
//@{
//////////////////////////////////////////////////////////////////////
public:
	//! Set matrix to a rotation matrix define by a vector and an angle in radians
	GLC_Matrix4x4& setMatRot(const GLC_Vector4d &Vect, const double &dAngleRad);

	//! Set matrix to a rotation matrix define by 2 vectors
	GLC_Matrix4x4& setMatRot(const GLC_Vector4d &Vect1, const GLC_Vector4d &Vect2);

	//! Set Matrix to a translation matrix by a vector
	GLC_Matrix4x4& setMatTranslate(const GLC_Vector4d &Vect);
	
	//! Set Matrix to a translation matrix by 3 coordinates
	GLC_Matrix4x4& setMatTranslate(double Tx, double Ty, double Tz);

	//! Set Matrix to a scaling matrix define by 3 double
	GLC_Matrix4x4& setMatScaling(const double &sX, const double &sY, const double sZ);

	//! Reverse the Matrix
	GLC_Matrix4x4& invert(void);

	//! Set the matrix to identify matrix
	GLC_Matrix4x4& setToIdentity();

	//! Set the matrix by its transpose
	GLC_Matrix4x4& transpose(void);
	
	//! Set the matrix with Euler angle
	GLC_Matrix4x4& fromEuler(double, double, double);
	

//@}

//////////////////////////////////////////////////////////////////////
//! Private services Functions
//////////////////////////////////////////////////////////////////////
private:
	
	//! Return true if the index (argument) is in the diagonal of the matrix
	const bool isDiagonal(const int index) const
	{
		if ((index == 0) || (index == 5) || (index == 10) || (index == 15))
			return true;
		else
			return false;
	}

	// Calcul du déterminant d'une céllule de la matrice 4x4
	const double getDeterminantLC(const int &Ligne, const int &Colonne) const;

	// Calcul d'une sous matrice 3x3
	void getSubMat(const int &Ligne, const int &Colonne, double *ResultMat) const;

	// Calcul du déterminant d'une matrice 3x3
	const double getDeterminant3x3(const double *Mat3x3) const;
	
	//! Return the transpose matrix
	const GLC_Matrix4x4 getTranspose(void) const;

	//! Return the co-matrix
	const GLC_Matrix4x4 getCoMat4x4(void) const;
	


//////////////////////////////////////////////////////////////////////
// Private members
//////////////////////////////////////////////////////////////////////
private:

	//! Matrix row first array
	double dMatrice[TAILLEMAT4X4];
/*
the matrix :
					a[00] a[04] a[08] a[12]

					a[01] a[05] a[09] a[13]

					a[02] a[06] a[10] a[14]

					a[03] a[07] a[11] a[15]
 */
//					Tx = 12,	Ty = 13,	Tz = 14
};
#endif /*GLC_MATRIX4X4_H_*/
