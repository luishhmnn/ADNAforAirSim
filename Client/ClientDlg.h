
// ClientDlg.h : header file
//

#pragma once

#include "CColorStatic.h"

// CClientDlg dialog
class CClientDlg : public CDialogEx
{
// Construction
public:
	CClientDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// Steering slider
	CSliderCtrl m_sliderSteering;
	int m_sliderSteeringVal;
	float GetSteering();
	void SetSteering(float value);
	// Throttle slider
	CSliderCtrl m_sliderThrottle;
	int m_sliderThrottleVal;
	float GetThrottle();
	// Brake slider
	CSliderCtrl m_sliderBrake;
	int m_sliderBrakeVal;
	float GetBrake();


	/**
	* @brief Sets the value of the DNA indicator.
	* @param value 0.0f for inactive, 1.0f for active.
	*/
	void SetDnaIndicator(float value);

	// DNA checker icon
	CColorStatic m_staticDNA;
	BOOL m_DNAactive;
	// Speed indicator
	CStatic m_staticSpeed;
	void SetSpeedIndicator(float value);


	// ACC button
	CButton m_btnACC;                ///< ACC button which works as a switch.
	BOOL m_ACCactive;                ///< Status of the ACC button's icon (bright/dark).
	BOOL m_ACCactivate;              ///< Status of the ACC button/ Users activation request.
	time_t m_ACCactivateTimestamp;   ///< Timestamp in s when LCA button was clicked.

	/**Returns the status of the ACC button, which works as switch.
	 * If the button was clicked to activate ACC (status `closed`),
	 * the function returns 1.0f. If the button was clicked to
	 * deactivate ACC (status `open`), the function returns 0.0f.
	 *
	 * @brief Returns the status of the ACC button.
	 * @return 1.0f if button's status is closed, 0.0f otherwise.
	*/
	float GetAcc();

	/**Sets the icon of the ACC button to bright or dark. If 0.0f is received,
	 * the switch (m_ACCactivate) is also set to FALSE. This is necessary so
	 * that ACC does not reactivate until the user presses the button.
	 * @brief Sets the icon of the button to bright or dark.
	 * @param value 0.0f to set icon to dark, 1.0f for bright.
	*/
	void SetAcc(float value);

	/**
	 * @brief Inverts the status of the LCA switch (m_LCAactivate).
	*/
	afx_msg void OnBnClickedButtonAcc();

	// LCA Button
	CButton m_btnLCA;                ///< LCA button which works as a switch.
	BOOL m_LCAactive;                ///< Status of the LCA button's icon (dark/bright).
	BOOL m_LCAactivate;              ///< Status of the LCA button/ Users activation request.
	time_t m_LCAactivateTimestamp;   ///< Timestamp in s when LCA button was clicked.

	/**Returns the status of the LCA button, which works as switch. 
	 * If the button was clicked to activate LCA (status `closed`),
	 * the function returns 1.0f. If the button was clicked to 
	 * deactivate LCA (status `open`), the function returns 0.0f.
	 * 
	 * @brief Returns the status of the LCA button.
	 * @return 1.0f if button's status is closed, 0.0f otherwise.
	*/
	float GetLca();

	/**Sets the icon of the LCA button to bright or dark. If 0.0f is received,
	 * the switch (m_LCAactivate) is also set to FALSE. This is necessary so
	 * that LCA does not reactivate until the user presses the button.
	 * @brief Sets the icon of the button to bright or dark.
	 * @param value 0.0f to set icon to dark, 1.0f for bright.
	*/
	void SetLca(float value);

	/**
	 * @brief Inverts the status of the LCA switch (m_LCAactivate).
	*/
	afx_msg void OnBnClickedButtonLca();

	// About modal
	/**
	 * @brief Shows a modal with information about the application.
	*/
	afx_msg void OnAppAbout();
};
