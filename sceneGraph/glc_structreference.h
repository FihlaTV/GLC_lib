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

//! \file glc_structreference.h interface for the GLC_StructReference class.

#ifndef GLC_STRUCTREFERENCE_H_
#define GLC_STRUCTREFERENCE_H_

#include <QString>
#include <QSet>

#include "../geometry/glc_3drep.h"
#include "glc_3dviewinstance.h"
#include "glc_attributes.h"
#include "glc_structinstance.h"

#include "../glc_config.h"

//////////////////////////////////////////////////////////////////////
//! \class GLC_StructReference
/*! \brief GLC_StructReference : A scene graph reference node */
//////////////////////////////////////////////////////////////////////
class GLC_LIB_EXPORT GLC_StructReference
{
//////////////////////////////////////////////////////////////////////
/*! @name Constructor / Destructor */
//@{
//////////////////////////////////////////////////////////////////////
public:
	//! Default Constructor
	GLC_StructReference(const QString& name= QString());

	//! Create reference with representation
	GLC_StructReference(GLC_Rep*);

	//! Destructor
	virtual ~GLC_StructReference();
//@}
//////////////////////////////////////////////////////////////////////
/*! \name Get Functions*/
//@{
//////////////////////////////////////////////////////////////////////
public:
	//! Return true if this reference has instance
	inline bool hasStructInstance() const
	{ return !m_SetOfInstance.isEmpty();}

	//! Return first instance handle
	inline GLC_StructInstance* firstInstanceHandle() const
	{ return *(m_SetOfInstance.begin());}

	//! Create a Struct instance of this reference
	GLC_StructInstance* createStructInstance();

	//! Return the list of instance of this reference
	inline QList<GLC_StructInstance*> listOfStructInstances() const
	{ return m_SetOfInstance.toList();}

	//! Return the list of occurence of this reference
	QList<GLC_StructOccurence*> listOfStructOccurence() const;

	//! Return true if this reference has a representation
	inline bool hasRepresentation() const
	{return NULL != m_pRepresentation;}

	//! Return an handle on the representation
	inline GLC_Rep* representationHandle() const
	{
		return m_pRepresentation;
	}

	//! Return the name
	inline QString name() const
	{return m_Name;}

	//! Get number of faces
	inline unsigned int numberOfFaces() const
	{
		Q_ASSERT(NULL != m_pRepresentation);
		GLC_3DRep* pRep= dynamic_cast<GLC_3DRep*>(m_pRepresentation);
		if (NULL != pRep) return pRep->numberOfFaces();
		else return 0;
	}

	//! Get number of vertex
	inline unsigned int numberOfVertex() const
	{
		Q_ASSERT(NULL != m_pRepresentation);
		GLC_3DRep* pRep= dynamic_cast<GLC_3DRep*>(m_pRepresentation);
		if (NULL != pRep) return pRep->numberOfVertex();
		else return 0;
	}

	//! Get number of materials
	inline unsigned int numberOfMaterials() const
	{
		Q_ASSERT(NULL != m_pRepresentation);
		GLC_3DRep* pRep= dynamic_cast<GLC_3DRep*>(m_pRepresentation);
		if (NULL != pRep) return pRep->numberOfMaterials();
		else return 0;
	}

	//! Return the number of body
	inline unsigned int numberOfBody() const
	{
		if(NULL != m_pRepresentation)
		{
			GLC_3DRep* pRep= dynamic_cast<GLC_3DRep*>(m_pRepresentation);
			if (NULL != pRep) return pRep->numberOfBody();
			else return 0;
		}
		else return 0;
	}

	//! Get materials List
	inline QSet<GLC_Material*> materialSet() const
	{
		Q_ASSERT(NULL != m_pRepresentation);
		GLC_3DRep* pRep= dynamic_cast<GLC_3DRep*>(m_pRepresentation);
		if (NULL != pRep) return pRep->materialSet();
		else return QSet<GLC_Material*>();
	}

	//! Return true if the reference contains User attributes
	inline bool containsAttributes() const
	{ return ((NULL != m_pAttributes) && !m_pAttributes->isEmpty());}

	//! Return handle to the reference attributes
	inline GLC_Attributes* attributesHandle() const
	{return m_pAttributes;}

//@}

//////////////////////////////////////////////////////////////////////
/*! \name Set Functions*/
//@{
//////////////////////////////////////////////////////////////////////
public:
	//! An Instance of this reference have been created
	inline void structInstanceCreated(GLC_StructInstance* pInstance)
	{
		Q_ASSERT(!m_SetOfInstance.contains(pInstance));
		m_SetOfInstance << pInstance;
	}

	//! An Instance of this reference have been deleted
	inline void structInstanceDeleted(GLC_StructInstance* pInstance)
	{m_SetOfInstance.remove(pInstance);}

	//! Set the reference name
	inline void setName(const QString& name)
	{m_Name= name;}

	//! Set the reference representation
	/*! Representation must not exist*/
	void setRepresentation(const GLC_3DRep& rep);

	//! Set the reference attributes
	void setAttributes(const GLC_Attributes& attr)
	{
		delete m_pAttributes;
		m_pAttributes= new GLC_Attributes(attr);
	}

//@}

//////////////////////////////////////////////////////////////////////
// Private members
//////////////////////////////////////////////////////////////////////
private:
	//! The Set of reference's instances
	QSet<GLC_StructInstance*> m_SetOfInstance;

	//! The representation of reference
	GLC_Rep* m_pRepresentation;

	//! The Reference Name
	QString m_Name;

	//! The Reference attributes
	GLC_Attributes* m_pAttributes;
	
};

#endif /* GLC_STRUCTREFERENCE_H_ */
