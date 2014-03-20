#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MemDC.h : header file
//

//////////////////////////////////////////////////
// CMemDC - memory DC
//
// Author: Keith Rule
// Email:  keithr@europa.com
// Copyright 1996-1997, Keith Rule
//
// You may freely use or modify this code provided this
// Copyright is included in all derived versions.
//
// History - 10/3/97 Fixed scrolling bug.
//                   Added print support.
//           25 feb 98 - fixed minor assertion bug
//
// This class implements a memory Device Context

class CMyMemDC : public CDC
{
public:
	
    // constructor sets up the memory DC
    CMyMemDC(CDC* pDC,CRect *pRect) : CDC()
    {
        ASSERT(pDC != NULL);
		m_Rect = CRect(pRect);
        m_pDC = pDC;
        m_pOldBitmap = NULL;
        m_bMemDC = !pDC->IsPrinting();
		
        if (m_bMemDC)    // Create a Memory DC
        {
            //pDC->GetClipBox(&m_rect);
            CreateCompatibleDC(pDC);
            m_bitmap.CreateCompatibleBitmap(pDC, pRect->Width(), pRect->Height());
            m_pOldBitmap = SelectObject(&m_bitmap);
        }
        else        // Make a copy of the relevent parts of the current DC for printing
        {
            m_bPrinting = pDC->m_bPrinting;
            m_hDC       = pDC->m_hDC;
            m_hAttribDC = pDC->m_hAttribDC;
        }
    }
    
    // Destructor copies the contents of the mem DC to the original DC
    ~CMyMemDC()
    {
        if (m_bMemDC) 
        {    
            // Copy the offscreen bitmap onto the screen.
			//在对象销毁前将内容显示到屏幕上
            m_pDC->BitBlt(m_Rect.left, m_Rect.top, m_Rect.Width(), m_Rect.Height(),
				this, 0, 0, SRCCOPY);
			
            //Swap back the original bitmap.
            SelectObject(m_pOldBitmap);
        } else {
            // All we need to do is replace the DC with an illegal value,
            // this keeps us from accidently deleting the handles associated with
            // the CDC that was passed to the constructor.
            m_hDC = m_hAttribDC = NULL;
        }
    }
	
    // Allow usage as a pointer
    CMyMemDC* operator->() {return this;}
	
    // Allow usage as a pointer
    operator CMyMemDC*() {return this;}
	
private:
    CBitmap  m_bitmap;      // Offscreen bitmap
    CBitmap* m_pOldBitmap;  // bitmap originally found in CMemDC
    CDC*     m_pDC;         // Saves CDC passed in constructor
	CRect    m_Rect;
    BOOL     m_bMemDC;      // TRUE if CDC really is a Memory DC.
};
