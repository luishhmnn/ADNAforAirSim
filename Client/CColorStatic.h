// CColorStatic.h : header file
//

#pragma once

/**
 * CStatic unfortunately does not offer the possibility to change the color of 
 * the text. This class is a CStatic-dervived class which adds this functionality.
 * 
 * @brief CStatic with ability to change the color of the text.
*/
class CColorStatic : public CStatic
{
	COLORREF m_textColor;
	HBRUSH   m_brush;

	/**
	 * @brief handler function on ctlcolor
	*/
	HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);

public:
	/**
	 * @brief CColorStatic's constructor
	*/
	CColorStatic();

	/**
	 * Sets the color of the text. After you called SetTextColor(), you have
	 * to call SetWindowText() to apply the change of the color.
	 * 
	 * @brief Sets the color of the text.
	 * @param color The new color of the text.
	*/
	void SetTextColor(COLORREF color) { m_textColor = color; };

	/**
	 * @brief Returns the color of the text.
	 * @return The current text color.
	*/
	COLORREF GetTextColor() { return m_textColor; };

	// macro to declare a message map
	DECLARE_MESSAGE_MAP()
};
