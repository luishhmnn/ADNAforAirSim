
// ClientDlg.cpp : implementation file
//

#include "pch.h"
//#include "framework.h"
#include "Client.h"
#include "ClientDlg.h"
#include "afxdialogex.h"
#include <ctime>

extern "C" {
#include <AHS.h>
#include <AHSUtilities.h>
#include <DNASensorActorInterfaceSimulator.h>
}


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// constants
#define DNACOMPLETE_STATIC_TEXT "ADNA"
#define DNACOMPLETE_OFF_COLOR RGB(180, 180, 180) // color if DNA is incomplete
#define DNACOMPLETE_ON_COLOR RGB(0, 150, 0) // color if DNA is complete


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ABOUTBOX };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CClientDlg dialog



CClientDlg::CClientDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_CLIENT_DIALOG, pParent)
    , m_sliderSteeringVal(0)
    , m_sliderThrottleVal(0)
    , m_sliderBrakeVal(0)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_SLIDER_STEERING, m_sliderSteering);
    DDX_Slider(pDX, IDC_SLIDER_STEERING, m_sliderSteeringVal);
    DDX_Control(pDX, IDC_SLIDER_THROTTLE, m_sliderThrottle);
    DDX_Slider(pDX, IDC_SLIDER_THROTTLE, m_sliderThrottleVal);
    DDX_Control(pDX, IDC_SLIDER_BRAKE, m_sliderBrake);
    DDX_Slider(pDX, IDC_SLIDER_BRAKE, m_sliderBrakeVal);
    DDX_Control(pDX, IDC_STATIC_TXT_DNA_INDICATOR, m_staticDNA);
    DDX_Control(pDX, IDC_BUTTON_ACC, m_btnACC);
    DDX_Control(pDX, IDC_BUTTON_LCA, m_btnLCA);
    DDX_Control(pDX, IDC_STATIC_TXT_SPEED_INDICATOR, m_staticSpeed);
    DDX_Control(pDX, IDC_STATIC_TXT_REFERENCE_SPEED_INDICATOR, m_staticReferenceSpeed);
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_COMMAND(ID_APP_ABOUT, &CClientDlg::OnAppAbout)
    ON_BN_CLICKED(IDC_BUTTON_ACC, &CClientDlg::OnBnClickedButtonAcc)
    ON_BN_CLICKED(IDC_BUTTON_LCA, &CClientDlg::OnBnClickedButtonLca)
END_MESSAGE_MAP()


// CClientDlg message handlers

BOOL CClientDlg::OnInitDialog()
{
    // Call the parent's standard constructor.
    CDialogEx::OnInitDialog();

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);			// Set big icon
    SetIcon(m_hIcon, FALSE);		// Set small icon

    // Init steering slider
    m_sliderSteering.SetRange(-100, 100, TRUE);
    m_sliderSteering.SetTicFreq(100);

    // Init throttle slider
    m_sliderThrottle.SetTicFreq(100);

    // Init brake slider
    m_sliderBrake.SetTicFreq(100);

    // Init DNA checker icon
    m_DNAactive = FALSE;
    m_staticDNA.SetTextColor(DNACOMPLETE_OFF_COLOR);
    m_staticDNA.SetWindowText(_T(DNACOMPLETE_STATIC_TEXT));

    // Init buttons
    m_btnACC.SetBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_ACC_INACTIVE)));
    m_btnLCA.SetBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_LCA_INACTIVE)));

    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialogEx::OnSysCommand(nID, lParam);
    }
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
void CClientDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CClientDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}


float CClientDlg::GetSteering()
{
    float val = 0.0f;

    // return slider position in range 1..3
    val = ((float)m_sliderSteering.GetPos() / 100)+2;
    if (val < 1)
        val = 1;
    else if (val > 3)
        val = 3;
    return val;
}


void CClientDlg::SetSteering(float value)
{
    float pos;

    //  Valid steering position range is from:
    //  1 (left) ... 2 (middle) ... 3 (right)
    if ((value < 1) || (value > 3)) return;

    // Transform steering value to a slider
    // position in [-100, 100]
    pos = int((value - 2) * 100);

    // Move the slider to the new position.
    m_sliderSteering.SetPos(pos);
}



float CClientDlg::GetThrottle()
{
    float val = 0.0f;

    // return slider position in range 0..1
    val = (float)m_sliderThrottle.GetPos() / 100;
    if (val < 0)
        val = 0;
    else if (val > 1)
        val = 1;
    return val;
}


float CClientDlg::GetBrake()
{
    float val = 0.0f;

    // return slider position in range 0..1
    val = (float)m_sliderBrake.GetPos() / 100;

    if (val < 0)
        val = 0;
    else if (val > 1)
        val = 1;
    return val;
}


float CClientDlg::GetAcc()
{
    // Does the user want to activate ACC?
    if (m_ACCactivate)
        return 1.0f;
    else
        return 0.0f;
}


float CClientDlg::GetLca()
{
    // Does the user want to activate LCA?
    if (m_LCAactivate)
        return 1.0f;
    else
        return 0.0f;
}


void CClientDlg::OnAppAbout()
{
    // Create the about dialog and show it.
    CAboutDlg aboutDlg;
    aboutDlg.DoModal();
}


void CClientDlg::SetDnaIndicator(float value)
{
    if ((value == 0.0f) && m_DNAactive)
    {
        m_DNAactive = FALSE;
        m_staticDNA.SetTextColor(DNACOMPLETE_OFF_COLOR);
        m_staticDNA.SetWindowText(_T(DNACOMPLETE_STATIC_TEXT));
    }
    else if ((value != 0.0f) && !m_DNAactive)
    {
        m_DNAactive = TRUE;
        OutputDebugString(_T("Aktiviere DNA Indicator\n"));
        m_staticDNA.SetTextColor(DNACOMPLETE_ON_COLOR);
        m_staticDNA.SetWindowText(_T(DNACOMPLETE_STATIC_TEXT));
    }
}


void CClientDlg::SetSpeedIndicator(float value)
{
    // Convert float to string.
    CString floatString;
    floatString.Format(_T("%.1f"), abs(value));

    // Change the text of the text control.
    m_staticSpeed.SetWindowTextW(floatString);
}


void CClientDlg::SetReferenceSpeedIndicator(float value)
{
    CString floatString;

    if (value == -1.0f)
    {
        // Reset indicator.
        floatString.Format(_T("-"));
    }
    else
    {
        // Convert float to string.
        floatString.Format(_T("%.1f"), abs(value));
    }

    // Change the text of the text control.
    m_staticReferenceSpeed.SetWindowTextW(floatString);
}


void CClientDlg::SetAcc(float value)
{
    if ((value == 0) && (m_ACCactive))
    {
        // Deactivate ACC
        m_ACCactivate = FALSE;
        m_ACCactive = FALSE;
        m_btnACC.SetBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_ACC_INACTIVE)));
    }
    else if ((value == 1) && (!m_ACCactive))
    {
        // Activate ACC
        m_ACCactive = TRUE;
        m_btnACC.SetBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_ACC_ACTIVE)));
    }
    else if ((value == 0) && (!m_ACCactive) && m_ACCactivate)
    {
        // Reset the activation request of the user, if ACC returns, 
        // that it cannot be activated. Note: To reset, the button
        // must have been pressed at least one second ago.
        if ((std::time(0) - m_ACCactivateTimestamp) > 1)
            m_ACCactivate = FALSE;
    }
}


void CClientDlg::SetLca(float value)
{
    if ((value == 0) && (m_LCAactive))
    {
        // Deactivate LCA
        m_LCAactivate = FALSE;
        m_LCAactive = FALSE;
        m_btnLCA.SetBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_LCA_INACTIVE)));
    } 
    else if ((value == 1) && (!m_LCAactive))
    {
        // Activate LCA
        m_LCAactive = TRUE;
        m_btnLCA.SetBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_LCA_ACTIVE)));
    } 
    else if ((value == 0) && (!m_LCAactive) && m_LCAactivate)
    {
        // Reset the activation request of the user, if LCA returns, 
        // that it cannot be activated. Note: To reset, the button
        // must have been pressed at least one second ago.
        if ((std::time(0) - m_LCAactivateTimestamp) > 1)
            m_LCAactivate = FALSE;       
    }
}


void CClientDlg::OnBnClickedButtonAcc()
{
    m_ACCactivate = !m_ACCactivate;

    if (m_ACCactivate)
        m_ACCactivateTimestamp = std::time(0);
}


void CClientDlg::OnBnClickedButtonLca()
{
    m_LCAactivate = !m_LCAactivate;
    
    if (m_LCAactivate)
        m_LCAactivateTimestamp = std::time(0);
}
