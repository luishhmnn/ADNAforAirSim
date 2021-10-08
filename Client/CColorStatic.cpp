
// CColorStatic.cpp : implementation file.
//

#include "pch.h"
#include "CColorStatic.h"


HBRUSH CColorStatic::CtlColor(CDC* pDC, UINT nCtlColor)
{
    // set the desired textcolor
    pDC->SetTextColor(m_textColor);
    // set background color
    pDC->SetBkColor(GetSysColor(COLOR_3DFACE));
    return m_brush;
}


CColorStatic::CColorStatic()
{
    // call default constructor
    CStatic::CStatic();

    // init color and brush
    m_textColor = RGB(0, 0, 0);
    m_brush = CreateSolidBrush(GetSysColor(COLOR_3DFACE));
}


BEGIN_MESSAGE_MAP(CColorStatic, CStatic)
    ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()

