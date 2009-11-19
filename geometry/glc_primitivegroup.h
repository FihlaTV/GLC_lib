/****************************************************************************

 This file is part of the GLC-lib library.
 Copyright (C) 2005-2008 Laurent Ribon (laumaya@users.sourceforge.net)
 Version 1.2.0, packaged on September 2009.

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

//! \file glc_primitivegroup.h interface for the GLC_PrimitiveGroup class.

#ifndef GLC_PRIMITIVEGROUP_H_
#define GLC_PRIMITIVEGROUP_H_

#include "../glc_ext.h"
#include "../glc_enum.h"
#include "glc_geomengine.h"

#include "glc_config.h"

typedef QList<GLuint> IndexList;
typedef QVector<GLsizei> IndexSizes;
typedef QVector<GLvoid*> OffsetVector;
typedef QVector<GLuint> OffsetVectori;

//////////////////////////////////////////////////////////////////////
//! \class GLC_PrimitiveGroup
/*! \brief GLC_PrimitiveGroup : Triangles, Strip and fan index*/

/*! An GLC_PrimitiveGroup is used to stored Triangles, strips and fans index
 * Grouped by material*/
//////////////////////////////////////////////////////////////////////
class GLC_LIB_EXPORT GLC_PrimitiveGroup
{
	friend QDataStream &operator<<(QDataStream &, const GLC_PrimitiveGroup &);
	friend QDataStream &operator>>(QDataStream &, GLC_PrimitiveGroup &);

public:
//////////////////////////////////////////////////////////////////////
/*! @name Constructor / Destructor */
//@{
//////////////////////////////////////////////////////////////////////

	//! Default constructor
	GLC_PrimitiveGroup(GLC_uint id= 0);

	//! Copy constructor
	GLC_PrimitiveGroup(const GLC_PrimitiveGroup&);

	//! Copy constructor
	GLC_PrimitiveGroup(const GLC_PrimitiveGroup&, GLC_uint);

	//! = operator
	GLC_PrimitiveGroup& operator=(const GLC_PrimitiveGroup&);

	~GLC_PrimitiveGroup();

//@}

//////////////////////////////////////////////////////////////////////
/*! \name Get Functions*/
//@{
//////////////////////////////////////////////////////////////////////
public:

	//! Return true if the group is finished
	inline bool isFinished() const
	{return m_IsFinished;}

	//! Return the group id
	inline GLC_uint id() const
	{return m_ID;}

	//! Return true if the group contains triangles
	inline bool containsTriangles() const
	{return m_TrianglesIndexSize > 0;}

	//! Return the size of list of triangles index of the group
	inline const int trianglesIndexSize() const
	{return m_TrianglesIndexSize;}

	//! Return the list of triangles index of the group
	inline const IndexList& trianglesIndex() const
	{
		Q_ASSERT(!m_IsFinished);
		return m_TrianglesIndex;
	}

	//! Return the offset of triangles index
	inline const GLvoid* trianglesIndexOffset() const
	{return m_pBaseTrianglesOffset;}

	//! Return the offset of triangles index
	inline const int trianglesIndexOffseti() const
	{return m_BaseTrianglesOffseti;}

	//! Return true if the group contains strips
	inline bool containsStrip() const
	{return m_TrianglesStripSize > 0;}

	//! Return the size of index of strips
	inline const int stripsIndexSize() const
	{return m_TrianglesStripSize;}

	//! Return the list of index of strips
	inline const IndexList& stripsIndex() const
	{
		Q_ASSERT(!m_IsFinished);
		return m_StripsIndex;
	}

	//! Return the vector of strips sizes
	inline const IndexSizes& stripsSizes() const
	{return m_StripIndexSizes;}

	//! Return the vector of strip offset
	inline const OffsetVector& stripsOffset() const
	{return m_StripIndexOffset;}

	//! Return the vector of strip offset
	inline const OffsetVectori& stripsOffseti() const
	{return m_StripIndexOffseti;}

	//! Return true if the group contains fans
	inline bool containsFan() const
	{return m_TrianglesFanSize > 0;}

	//! Return the size of index of fans
	inline const int fansIndexSize() const
	{return m_TrianglesFanSize;}

	//! Return the list of index of fans
	inline const IndexList& fansIndex() const
	{
		Q_ASSERT(!m_IsFinished);
		return m_FansIndex;
	}

	//! Return the vector of fans sizes
	inline const IndexSizes& fansSizes() const
	{return m_FansIndexSizes;}

	//! Return the vector of strip offset
	inline const OffsetVector& fansOffset() const
	{return m_FanIndexOffset;}

	//! Return the vector of strip offset
	inline const OffsetVectori& fansOffseti() const
	{return m_FanIndexOffseti;}

	//! Return the strip ID
	inline GLC_uint stripId(int index)
	{return m_StripsId.at(index);}

//@}

//////////////////////////////////////////////////////////////////////
/*! \name Set Functions*/
//@{
//////////////////////////////////////////////////////////////////////
public:
	//! Set the group id
	inline void setId(GLC_uint id)
	{m_ID= id;}

	//! Add triangles to the group
	void addTriangles(const IndexList& input, GLC_uint id= 0);

	//! Set the triangle index offset
	inline void setTrianglesOffset(GLvoid* pOffset)
	{m_pBaseTrianglesOffset= pOffset;}

	//! Set the triangle index offset
	inline void setTrianglesOffseti(int offset)
	{m_BaseTrianglesOffseti= offset;}

	//! Add triangle strip to the group
	void addTrianglesStrip(const IndexList&, GLC_uint id= 0);

	//! Set base triangle strip offset
	void setBaseTrianglesStripOffset(GLvoid*);

	//! Set base triangle strip offset
	void setBaseTrianglesStripOffseti(int);

	//! Add triangle fan to the group
	void addTrianglesFan(const IndexList&, GLC_uint id= 0);

	//! Set base triangle fan offset
	void setBaseTrianglesFanOffset(GLvoid*);

	//! Set base triangle fan offset
	void setBaseTrianglesFanOffseti(int);

	//! Change index to VBO mode
	void changeToVboMode();

	//! The mesh wich use this group is finished
	inline void finish()
	{
		m_TrianglesIndex.clear();
		m_StripsIndex.clear();
		m_FansIndex.clear();
		m_IsFinished= true;
	}

	//! Clear the group
	void clear();

//@}

//////////////////////////////////////////////////////////////////////
// Private members
//////////////////////////////////////////////////////////////////////
private:
	//! Grouped material id
	GLC_uint m_ID;

	//! Triangles index list
	IndexList m_TrianglesIndex;

	//! The base triangle index offset
	GLvoid* m_pBaseTrianglesOffset;
	GLuint m_BaseTrianglesOffseti;

	//! Triangles groups index size
	IndexSizes m_TrianglesGroupsSizes;

	//! Triangles groups id
	QList<GLC_uint> m_TrianglesId;

	//! Strips index list
	IndexList m_StripsIndex;

	//! Strips index size
	IndexSizes m_StripIndexSizes;

	//! Vector of strips offset
	OffsetVector m_StripIndexOffset;
	OffsetVectori m_StripIndexOffseti;

	//! Strips id
	QList<GLC_uint> m_StripsId;

	//! Fans index list
	IndexList m_FansIndex;

	//! Fans index size
	IndexSizes m_FansIndexSizes;

	//! Vector of fan Offset
	OffsetVector m_FanIndexOffset;
	OffsetVectori m_FanIndexOffseti;

	//! Fans id
	QList<GLC_uint> m_FansId;

	//! Flag to know if the group is finish
	int m_IsFinished;

	//! Flag to know if there is triangles
	int m_TrianglesIndexSize;

	//! Flag to know if there is triangles strip
	int m_TrianglesStripSize;

	//! Flag to know if there is triangles fan
	int m_TrianglesFanSize;

};

//! Non-member stream operator
QDataStream &operator<<(QDataStream &, const GLC_PrimitiveGroup &);
QDataStream &operator>>(QDataStream &, GLC_PrimitiveGroup &);

#endif /* GLC_PRIMITIVEGROUP_H_ */
