/****************************************************************************
*                                                                           *
*  OpenNI 1.x Alpha                                                         *
*  Copyright (C) 2011 PrimeSense Ltd.                                       *
*                                                                           *
*  This file is part of OpenNI.                                             *
*                                                                           *
*  OpenNI is free software: you can redistribute it and/or modify           *
*  it under the terms of the GNU Lesser General Public License as published *
*  by the Free Software Foundation, either version 3 of the License, or     *
*  (at your option) any later version.                                      *
*                                                                           *
*  OpenNI is distributed in the hope that it will be useful,                *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of           *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the             *
*  GNU Lesser General Public License for more details.                      *
*                                                                           *
*  You should have received a copy of the GNU Lesser General Public License *
*  along with OpenNI. If not, see <http://www.gnu.org/licenses/>.           *
*                                                                           *
****************************************************************************/
#ifndef NI_HAND_TRACKER_H__
#define NI_HAND_TRACKER_H__

#include <QImage>

#include <XnCppWrapper.h>
#include <XnCyclicStackT.h>
#include <XnHashT.h>

typedef XnHashT<XnUserID, XnPoint3D> TrailHistory;

class HandTracker
{
public:
    HandTracker(xn::Context&);
	~HandTracker();

	XnStatus Init();
	XnStatus Run();
	XnStatus Update();

    QImage getCamera();



    const TrailHistory&	GetHistory()	const	{return m_History;}

private:
	// OpenNI Gesture and Hands Generator callbacks
    static void Gesture_Recognized(xn::GestureGenerator&	generator,
                                const XnChar*			strGesture,
                                const XnPoint3D*		pIDPosition,
                                const XnPoint3D*		pEndPosition,
                                void*					pCookie);
    static void Gesture_Process(xn::GestureGenerator&	/*generator*/,
                                const XnChar*			/*strGesture*/,
                                const XnPoint3D*		/*pPosition*/,
                                XnFloat					/*fProgress*/,
                                void*					/*pCookie*/)	{}
    static void Hand_Create(	xn::HandsGenerator& generator,
                                XnUserID			nId,
                                const XnPoint3D*	pPosition,
                                XnFloat				fTime,
                                void*				pCookie);
    static void Hand_Update(    xn::HandsGenerator& generator,
                                XnUserID			nId,
                                const XnPoint3D*	pPosition,
                                XnFloat             fTime,
                                void*				pCookie);
    static void Hand_Destroy(	xn::HandsGenerator& generator,
                                XnUserID			nId,
                                XnFloat				fTime,
                                void*				pCookie);

    xn::Context				m_rContext;
    xn::ScriptNode 			m_scriptNode;
    TrailHistory			m_History;
    xn::GestureGenerator	m_GestureGenerator;
	xn::HandsGenerator		m_HandsGenerator;
    xn::ImageGenerator      m_ImageGenerator;
    xn::DepthGenerator      m_DepthGenerator;
    xn::ImageMetaData       m_ImageMD;
    xn::DepthMetaData       m_DepthMD;

    QImage*                 m_imagecamera;
    QImage*                 m_imagedepth;

    static XnListT<HandTracker*>	sm_Instances;	// Living instances of the class

private:
	XN_DISABLE_COPY_AND_ASSIGN(HandTracker);
};

#endif //NI_HAND_TRACKER_H__
