
// ComDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Com.h"
#include "ComDlg.h"
#include "afxdialogex.h"

#include "mscomm.h" // comEvReceive

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CComDlg 对话框




CComDlg::CComDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CComDlg::IDD, pParent)
	, m_strSend(_T(""))
	, m_strReceive(_T(""))
	, m_strPort(_T(""))
	, m_strDataBit(_T(""))
	, m_strStopBit(_T(""))
	, m_strCheck(_T(""))
	, m_strBaudRate(_T(""))
	, m_uiSecs(1000)
{
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_EARTH); // 图标改成地球的那个图标
	m_ulSendNum = 0;
	m_ulReceiveNum = 0;
	m_strSend = "LiaoYang Studio!";
}

void CComDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_MSCOMM, m_mscomm);
	DDX_Control(pDX, IDC_EDIT_SEND, m_editSend);
	DDX_Control(pDX, IDC_EDIT_RECEIVE, m_editReceive);
	DDX_Text(pDX, IDC_EDIT_SEND, m_strSend);
	DDX_Text(pDX, IDC_EDIT_RECEIVE, m_strReceive);

	DDX_CBString(pDX, IDC_PORT_COMBO, m_strPort);
	DDX_CBString(pDX, IDC_BAUDRATE_COMBO, m_strBaudRate);
	DDX_CBString(pDX, IDC_DATABIT_COMBO, m_strDataBit);
	DDX_CBString(pDX, IDC_CHECK_COMBO, m_strCheck);
	DDX_CBString(pDX, IDC_STOPBIT_COMBO, m_strStopBit);

	DDX_Control(pDX, IDC_PIC_INDICATOR, m_picIndicator);

	DDX_Control(pDX, IDC_PORT_COMBO, m_cboPort);
	DDX_Control(pDX, IDC_BAUDRATE_COMBO, m_cboBaudRate);
	DDX_Control(pDX, IDC_CHECK_COMBO, m_cboCheck);
	DDX_Control(pDX, IDC_DATABIT_COMBO, m_cboDataBit);
	DDX_Control(pDX, IDC_STOPBIT_COMBO, m_cboStopBit);
	DDX_Control(pDX, IDC_CHECK_SEND_HEX, m_chkHexSend);
	DDX_Control(pDX, IDC_CHECK_RECEIVE_HEX, m_chkHexReceive);
	DDX_Control(pDX, IDC_CHECK_TIMER, m_chkTimer);
	DDX_Text(pDX, IDC_EDIT_TIME, m_uiSecs);
	DDX_Control(pDX, IDC_BUTTON_SAVE_FILE, m_btnSaveFile);
	DDX_Control(pDX, IDC_BUTTON_LOAD_FILE, m_btnLoadFile);
	DDX_Control(pDX, IDC_BUTTON_CLEAR_SEND, m_btnClearSend);
	DDX_Control(pDX, IDC_EDIT_TIME, m_editTime);
	DDX_Control(pDX, IDC_BUTTON_OPEN, m_btnOpen);
}

BEGIN_MESSAGE_MAP(CComDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CComDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CComDlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_RECEIVE, &CComDlg::OnBnClickedButtonClearReceive)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_SEND, &CComDlg::OnBnClickedButtonClearSend)

	//ON_CBN_SELCHANGE(IDC_BAUD_COMBO, &CComDlg::OnCbnSelchangeBaudCombo)
	//ON_CBN_SELCHANGE(IDC_CHECK_COMBO, &CComDlg::OnCbnSelchangeCheckCombo)
	//ON_CBN_SELCHANGE(IDC_DATABIT_COMBO, &CComDlg::OnCbnSelchangeDatabitCombo)
	//ON_CBN_SELCHANGE(IDC_STOPBIT_COMBO, &CComDlg::OnCbnSelchangeStopbitCombo)
	ON_CBN_SELCHANGE(IDC_BAUDRATE_COMBO, &CComDlg::OnCbnSelchangeCombo)
	ON_CBN_SELCHANGE(IDC_CHECK_COMBO, &CComDlg::OnCbnSelchangeCombo)
	ON_CBN_SELCHANGE(IDC_DATABIT_COMBO, &CComDlg::OnCbnSelchangeCombo)
	ON_CBN_SELCHANGE(IDC_STOPBIT_COMBO, &CComDlg::OnCbnSelchangeCombo)

	ON_CBN_SELCHANGE(IDC_PORT_COMBO, &CComDlg::OnCbnSelchangeCombo)
	ON_BN_CLICKED(IDC_BUTTON_LOAD_FILE, &CComDlg::OnBnClickedButtonLoadFile)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_FILE, &CComDlg::OnBnClickedButtonSaveFile)
	ON_BN_CLICKED(IDC_BUTTON_RESET_CNT, &CComDlg::OnBnClickedButtonResetCnt)
	ON_BN_CLICKED(IDC_CHECK_SEND_HEX, &CComDlg::OnBnClickedCheckSendHex)
	ON_WM_TIMER()
	ON_WM_CHAR()
	ON_WM_CHAR()
END_MESSAGE_MAP()


// CComDlg 消息处理程序

BOOL CComDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	ComboAddString();
	
	/* //在设计阶段已经初始化了图片了，所以这里不用了
	CBitmap bitmap;  // CBitmap对象，用于加载位图    
    HBITMAP hBmp;    // 保存CBitmap加载的位图的句柄   
  
    bitmap.LoadBitmap(IDB_BITMAP_RED);  // 将位图IDB_BITMAP1加载到bitmap   
    hBmp = (HBITMAP)bitmap.GetSafeHandle();  // 获取bitmap加载位图的句柄   
    m_picIndicator.SetBitmap(hBmp);    // 设置图片控件m_picIndicator的位图图片为IDB_BITMAP_RED   

	*/

	m_StatusBar.Create(WS_CHILD|WS_VISIBLE|SBT_OWNERDRAW, /*CRect(0,0,0,0),*/ CRect(500,550,0,660),this, 0);
	int strPartDim[3]= {400, 550,-1}; //分割数量
	m_StatusBar.SetParts(3, strPartDim);// Sets the number of parts in a status bar control and 
										// the coordinate of the right edge of each part.

	//m_StatusBar.SetMinHeight(300);

	//设置状态栏文本
	m_StatusBar.SetText("待填充", 0, 0);//SBT_POPOUT, SBT_NOBORDERS
	m_StatusBar.SetText("发送：0", 1, 0);
	m_StatusBar.SetText("接收：0", 2, 0);

	//CRect rect;
	//m_StatusBar.GetClientRect(&rect);
	//CRect rectPane1;
	//m_StatusBar.GetRect(3, &rectPane1); 

/********************************************* 设置“按钮”的字体 *************************************/
	CFont font;
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));       // zero out structure
	lf.lfHeight = 12;                      // request a 12-pixel-height font
	_tcscpy_s(lf.lfFaceName, LF_FACESIZE, _T("宋体"));              // request a face name "Arial"
	font.CreateFontIndirect(&lf);  // create the font
	GetDlgItem(IDC_BUTTON_SEND)->SetFont(&font);// 获取按钮IDC_BUTTON_SEND的CWnd指针，并设置其字体
/*****************************************************************************************************/

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CComDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CComDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//m_picIndicator.SetRedraw(TRUE);  
		//m_picIndicator.Invalidate();  
		//m_picIndicator.UpdateWindow();
/************** 每次最小化再显示出来，或者被其他窗口遮挡再显示，指示灯就不会显示了，这里实现重绘指示灯 ****************/
		CString strOpen;
		GetDlgItemText(IDC_BUTTON_OPEN, strOpen);
		if(strOpen == "打开")
		{
			CBitmap bitmap;  // CBitmap对象，用于加载位图    
			HBITMAP hBmp;    // 保存CBitmap加载的位图的句柄   

			bitmap.LoadBitmap(IDB_BITMAP_RED);  // 将位图IDB_BITMAP1加载到bitmap   
			hBmp = (HBITMAP)bitmap.GetSafeHandle();  // 获取bitmap加载位图的句柄   
			m_picIndicator.SetBitmap(hBmp);    // 设置图片控件m_picIndicator的位图图片为IDB_BITMAP_RED

			CDialogEx::OnPaint();
		}
		else
		{
			CBitmap bitmap;  // CBitmap对象，用于加载位图    
			HBITMAP hBmp;    // 保存CBitmap加载的位图的句柄   

			bitmap.LoadBitmap(IDB_BITMAP_GREEN);  // 将位图IDB_BITMAP1加载到bitmap   
			hBmp = (HBITMAP)bitmap.GetSafeHandle();  // 获取bitmap加载位图的句柄   
			m_picIndicator.SetBitmap(hBmp);    // 设置图片控件m_picIndicator的位图图片为IDB_BITMAP_RED

			CDialogEx::OnPaint();
		}
/*****************************************************************************************************************/

		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CComDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CComDlg::ComboAddString(void)
{
	//m_cboPort.AddString(_T("COM1"));
	//m_cboPort.AddString(_T("COM2"));
	//m_cboPort.AddString(_T("COM3"));
	//m_cboPort.AddString(_T("COM4"));
	//m_cboPort.AddString(_T("COM5"));
	//m_cboPort.AddString(_T("COM6"));
	//m_cboPort.AddString(_T("COM7"));
	//m_cboPort.AddString(_T("COM8"));
	
	//m_cboBaudRate.AddString(_T("2400"));
	//m_cboBaudRate.AddString(_T("4800"));
	//m_cboBaudRate.AddString(_T("9600"));
	//m_cboBaudRate.AddString(_T("19200"));
	//m_cboBaudRate.AddString(_T("57600"));
	//m_cboBaudRate.AddString(_T("115200"));

	//m_cboCheck.AddString(_T("NONE"));
	//m_cboCheck.AddString(_T("ODD"));
	//m_cboCheck.AddString(_T("EVEN"));
	//m_cboCheck.AddString(_T("MARK"));
	//m_cboCheck.AddString(_T("SPACE"));

	//m_cboDataBit.AddString(_T("5"));
	//m_cboDataBit.AddString(_T("6"));
	//m_cboDataBit.AddString(_T("7"));
	//m_cboDataBit.AddString(_T("8"));
	
	//m_cboStopBit.AddString(_T("1"));
	//m_cboStopBit.AddString(_T("1.5"));
	//m_cboStopBit.AddString(_T("2"));

	m_cboPort.SetCurSel(0);
	m_cboBaudRate.SetCurSel(2);
	m_cboCheck.SetCurSel(0);
	m_cboDataBit.SetCurSel(3);
	m_cboStopBit.SetCurSel(0);
}
BEGIN_EVENTSINK_MAP(CComDlg, CDialogEx)
	ON_EVENT(CComDlg, IDC_MSCOMM, 1, CComDlg::OnCommMscomm, VTS_NONE)
END_EVENTSINK_MAP()

/*
CString CComDlg::ByteToString(byte ByteArr[], int len)
{
	CString str = "";
	CString strtemp;
	for(int i = 0; i < len; i++)
	{
		strtemp.Format(_T("%02X"),ByteArr[i]);
		str = str + strtemp + " ";
	}
	str = str.TrimRight(" ");

	return str;
}*/

void CComDlg::OnCommMscomm()
{
	// TODO: 在此处添加消息处理程序代码
	UpdateData(TRUE); 

	static unsigned int cnt=0;  
	VARIANT variant_inp;    
	COleSafeArray safearray_inp;   
	long len,k;    
	byte rxdata[1024]; //设置 BYTE 数组   CString strtemp; 

	switch(m_mscomm.get_CommEvent())  
	{
	case CMscomm::comEvReceive: //值为 2 表示接收缓冲区内有字符  

		m_mscomm.put_InputMode(CMscomm::comInputModeBinary);//以二进制方式读取数据

		cnt++;   
		variant_inp = m_mscomm.get_Input();     
		safearray_inp = variant_inp; ///变量转换    
		len = safearray_inp.GetOneDimSize(); //得到有效的数据长度   

		//状态栏显示接收到的字符个数
		CString strReceiveNum;
		m_ulReceiveNum += len;
		strReceiveNum.Format("%d", m_ulReceiveNum);
		strReceiveNum = "接收：" + strReceiveNum;
		m_StatusBar.SetText(strReceiveNum, 2, 0);//SBT_POPOUT, SBT_NOBORDERS

		for(k = 0; k < len; k++)    
		{   
			safearray_inp.GetElement(&k, rxdata + k);

			if(1 == m_chkHexReceive.GetCheck()) //接收到的数据以十六进制显示
			{
				//safearray_inp.GetElement(&k, rxdata + k);  
				CString strtemp = "";
				strtemp.Format(_T("%02X"),rxdata[k]);
				m_strReceive = m_strReceive + strtemp + " "; 
			}
			else	//接收到的数据以字符格式显示
			{
				CString strtemp = "";
				//safearray_inp.GetElement(&k, rxdata + k);    
				strtemp.Format("%c",rxdata[k]); //将字符送入临时变量strtemp存放
				m_strReceive = m_strReceive + strtemp;
			}
		}   
		break;
	}

	UpdateData(FALSE); //更新编辑框内容

	//注意：在更新完编辑框的内容之后，还要设置接收编辑框定位到最后一行
	int nLineCount = m_editReceive.GetLineCount();
	int nLineLength = m_editReceive.LineLength(nLineCount);
	m_editReceive.LineScroll(nLineCount, nLineLength);
	//TRACE("%d", nLineCount);
}

CString CComDlg::getCheck(void)
{
	CString strCheck;

	switch(m_cboCheck.GetCurSel())
	{
	case 0: strCheck = "n"; break;
	case 1:  strCheck = "o"; break;
	case 2: strCheck = "e"; break;
	case 3: strCheck = "m"; break;
	case 4:strCheck = "s"; break;
	default:break;
	}

	return strCheck;
}

void CComDlg::OnBnClickedButtonOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); 

	CString strOpen;
	GetDlgItemText(IDC_BUTTON_OPEN, strOpen);
	if(strOpen == "打开")
	{
		m_mscomm.put_InBufferSize(1024); //接收缓冲区  
		m_mscomm.put_OutBufferSize(1024);//发送缓冲区   
		m_mscomm.put_InputLen(0);//设置当前接收区数据长度为0,表示全部读取  
		m_mscomm.put_InputMode(CMscomm::comInputModeBinary);//以二进制方式读写数据   
		m_mscomm.put_RThreshold(1);//接收缓冲区有1个及1个以上字符时，将引发接收数据的OnComm事件
		
		//校验位
		CString strCheck = getCheck();

		CString strSettings = m_strBaudRate + strCheck + m_strDataBit + m_strStopBit;
		//MessageBox(strSettings);
		//"9600,n,8,1" 和 "9600n81" 均对
		//m_mscomm.put_Settings(_T("9600,n,8,1"));//波特率9600，无检验位，8个数据位，1个停止位  
		m_mscomm.put_Settings(strSettings);

		//端口号
		m_mscomm.put_CommPort(m_cboPort.GetCurSel() + 1);

		//真正打开串口 
		try
		{
			m_mscomm.put_PortOpen(TRUE);//put_PortOpen(TRUE)，参数为TRUE则打开串口，为FALSE则关闭串口
		}
		catch (CException* e)
		{
			MessageBox("端口不存在！", "打开串口", MB_ICONERROR);
			return;
		}
		
		SetDlgItemText(IDC_BUTTON_OPEN, _T("关闭")); //串口打开之后，设置按钮为“关闭”

		CBitmap bitmap;  // CBitmap对象，用于加载位图    
		HBITMAP hBmp;    // 保存CBitmap加载的位图的句柄   
  
		bitmap.LoadBitmap(IDB_BITMAP_GREEN);  // 将位图IDB_BITMAP1加载到bitmap   
		hBmp = (HBITMAP)bitmap.GetSafeHandle();  // 获取bitmap加载位图的句柄   
		m_picIndicator.SetBitmap(hBmp);    // 设置图片控件m_picIndicator的位图图片为IDB_BITMAP_RED 
	}
	else // 此时串口已经处于打开状态
	{
		m_mscomm.put_PortOpen(FALSE);//put_PortOpen(TRUE)，参数为TRUE则打开串口，为FALSE则关闭串口  
		SetDlgItemText(IDC_BUTTON_OPEN, _T("打开")); //串口打开之后，设置按钮为“关闭”

		CBitmap bitmap;  // CBitmap对象，用于加载位图    
		HBITMAP hBmp;    // 保存CBitmap加载的位图的句柄   
  
		bitmap.LoadBitmap(IDB_BITMAP_RED);  // 将位图IDB_BITMAP1加载到bitmap   
		hBmp = (HBITMAP)bitmap.GetSafeHandle();  // 获取bitmap加载位图的句柄   
		m_picIndicator.SetBitmap(hBmp);    // 设置图片控件m_picIndicator的位图图片为IDB_BITMAP_RED  
	}
}

CString CComDlg::GetOrderedStr()
{
	CString str;

	int i = 0;
	int length = m_strSend.GetLength();
	for(i = 0; i < length - 1; i++)//"31 32 33 回车 34"   "34 31 327"    "34 31 32 7"    "32 33 3 34"
	{
		if(m_strSend.Mid(i, 1) != " " && m_strSend.Mid(i, 1) != "\r")
		{
			if(m_strSend.Mid(i+1, 1) !=  " " && m_strSend.Mid(i+1, 1) !=  "\r")
			{
				CString strTemp;
				strTemp = m_strSend.Mid(i, 2);
				str = str + strTemp;
				i++;
			}
			else
			{
				str = str + "0" + m_strSend.Mid(i, 1);
			}
		}

		if(m_strSend.Mid(i, 1) == "\r" && m_strSend.Mid(i+1, 1) == "\n") //碰到回车,也就是\n\r,则直接跳过\n\r这两个字符! 
			i++;     
	}	

	if(i == m_strSend.GetLength()-1 && m_strSend.Mid(i, 1) != " ")
		str = str + "0" + m_strSend.Mid(i, 1);  //该行防止"34 31 32 7"中7丢失
	//至此, "31323334"      "34313207"      "34313207"     "32330334"

	//MessageBox(str);

	return str;
}

void CComDlg::OnBnClickedButtonSend()
{
	UpdateData(TRUE); //读取编辑框内容    

	CString strSend;
	GetDlgItemText(IDC_BUTTON_SEND, strSend);
	if(strSend == "发送")
	{
		try
		{
			CString strOrdered = "";
			if(1 == m_chkHexSend.GetCheck())
			{
				hexToSend.RemoveAll();
				strOrdered = GetOrderedStr();
				//MessageBox(strOrdered);
				for(int i = 0; i< strOrdered.GetLength(); i += 2)
				{
					CString strTemp = strOrdered.Mid(i, 2);
					char *p = strTemp.GetBuffer(2);
					hexToSend.Add(strtol(p, NULL, 16));
				}
				m_mscomm.put_Output(COleVariant(hexToSend));//发送数据
				//int num = hexToSend.GetCount();
				//TRACE("%d", num);
			}
			else
			{
				strToSend = m_strSend;
				m_mscomm.put_Output(COleVariant(strToSend));//发送数据
			}
			
			

			if(1 == m_chkTimer.GetCheck())
			{
				SetTimer(1, m_uiSecs, NULL); // 启动ID为1的定时器，定时时间为1秒
				SetDlgItemText(IDC_BUTTON_SEND, _T("停止发送")); //串口打开之后，设置按钮为“关闭”
				m_editSend.SetReadOnly(TRUE);
				m_btnClearSend.EnableWindow(FALSE);
				m_btnLoadFile.EnableWindow(FALSE);
				m_btnSaveFile.EnableWindow(FALSE);
				m_chkTimer.EnableWindow(FALSE);
				m_editTime.EnableWindow(FALSE);

				m_cboPort.EnableWindow(FALSE);
				m_cboBaudRate.EnableWindow(FALSE);
				m_cboCheck.EnableWindow(FALSE);
				m_cboDataBit.EnableWindow(FALSE);
				m_cboStopBit.EnableWindow(FALSE);

				m_btnOpen.EnableWindow(FALSE);
			}

			//状态栏显示发送的字符个数
			CString strSendNum;
			if(1 == m_chkHexSend.GetCheck())
				m_ulSendNum += hexToSend.GetCount();
			else
				m_ulSendNum += strToSend.GetLength();

			strSendNum.Format("%d", m_ulSendNum);
			strSendNum = "发送：" + strSendNum;
			m_StatusBar.SetText(strSendNum, 1, 0);//SBT_POPOUT, SBT_NOBORDERS
		}
		catch (CException* e)
		{
			MessageBox("端口尚未打开！", "发送", MB_ICONERROR);
			return;
		}
	}
	else
	{
		KillTimer(1); 
		SetDlgItemText(IDC_BUTTON_SEND, _T("发送")); //串口打开之后，设置按钮为“关闭”
		m_editSend.SetReadOnly(FALSE);
		m_btnClearSend.EnableWindow(TRUE);
		m_btnLoadFile.EnableWindow(TRUE);
		m_btnSaveFile.EnableWindow(TRUE);
		m_chkTimer.EnableWindow(TRUE);
		m_editTime.EnableWindow(TRUE);

		m_cboPort.EnableWindow(TRUE);
		m_cboBaudRate.EnableWindow(TRUE);
		m_cboCheck.EnableWindow(TRUE);
		m_cboDataBit.EnableWindow(TRUE);
		m_cboStopBit.EnableWindow(TRUE);

		m_btnOpen.EnableWindow(TRUE);
	}
	
	  
	//m_mscomm.put_Output(m_editSend);//发送数据  
	//m_editSend.Empty(); //发送后清空输入框 
	m_editSend.SetWindowText(_T(""));

	UpdateData(FALSE); //更新编辑框内容

	//注意：在更新完编辑框的内容之后，还要设置接收编辑框定位到最后一行
	int nLineCount = m_editReceive.GetLineCount();
	int nLineLength = m_editReceive.LineLength(nLineCount);
	m_editReceive.LineScroll(nLineCount, nLineLength);
	//TRACE("%d", nLineCount);
}

void CComDlg::OnBnClickedButtonClearReceive()
{
	// TODO: 在此添加控件通知处理程序代码
	m_strReceive = "";
	//m_editReceive.SetWindowText(_T(""));
	UpdateData(FALSE);
}

void CComDlg::OnBnClickedButtonClearSend()
{
	// TODO: 在此添加控件通知处理程序代码
	m_editSend.SetWindowText(_T(""));
}

void CComDlg::OnCbnSelchangeCombo()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); //读取编辑框内容

	CString strOpen;
	GetDlgItemText(IDC_BUTTON_OPEN, strOpen);

	if(strOpen == "关闭")
	{
		CString strCheck = getCheck();
		CString strSettings = m_strBaudRate + strCheck + m_strDataBit + m_strStopBit; 

		//MessageBox(strSettings);
		m_mscomm.put_Settings(strSettings);

		WORD id = LOWORD(GetCurrentMessage()->wParam);
		//CString strID;
		//strID.Format("%d", id);
		//MessageBox(strID);

		if(id == IDC_PORT_COMBO)
		{
			m_mscomm.put_PortOpen(FALSE);//put_PortOpen(TRUE)，参数为TRUE则打开串口，为FALSE则关闭串口  
			m_mscomm.put_CommPort(m_cboPort.GetCurSel() + 1);//端口号
			try
			{
				m_mscomm.put_PortOpen(TRUE);//put_PortOpen(TRUE)，参数为TRUE则打开串口，为FALSE则关闭串口
			}
			catch (CException* e)
			{
				MessageBox("端口不存在！", "打开串口", MB_ICONERROR);
				SetDlgItemText(IDC_BUTTON_OPEN, _T("打开")); //串口打开之后，设置按钮为“关闭”

				CBitmap bitmap;  // CBitmap对象，用于加载位图    
				HBITMAP hBmp;    // 保存CBitmap加载的位图的句柄   
  
				bitmap.LoadBitmap(IDB_BITMAP_RED);  // 将位图IDB_BITMAP1加载到bitmap   
				hBmp = (HBITMAP)bitmap.GetSafeHandle();  // 获取bitmap加载位图的句柄   
				m_picIndicator.SetBitmap(hBmp);    // 设置图片控件m_picIndicator的位图图片为IDB_BITMAP_RED
			}	
		}
	}
}


void CComDlg::OnBnClickedButtonLoadFile()
{
	m_strSend = "";

	TCHAR szFilter[] = _T("文本文件(*.txt)|*.txt|所有文件(*.*)|*.*||");// 设置过滤器   
    CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);// 构造打开文件对话框   
	CString strFilePath;   
  
    if (IDOK == fileDlg.DoModal())// 显示打开文件对话框  
    {      
        strFilePath = fileDlg.GetPathName();   // 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里
        //MessageBox(strFilePath);  

		CFile file;      // CFile对象
		char readBuffer[2048]; 
		if (file.Open(strFilePath, CFile::modeRead))
		{
			int nRet = file.Read(readBuffer, 2048);

			for(int i = 0; i < nRet; i++)
			{
				CString str;
				str.Format("%c", readBuffer[i]);
				m_strSend += str;
			}
		}
		UpdateData(FALSE);
    }  
}


void CComDlg::OnBnClickedButtonSaveFile()
{
	UpdateData(TRUE);

	TCHAR szFilter[] = _T("文本文件(*.txt)|*.txt|Word文件(*.doc)|*.doc|所有文件(*.*)|*.*||"); // 设置过滤器  
    CFileDialog fileDlg(FALSE, _T("doc"), _T("InitFileName"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);// 构造保存文件对话框   
	CString strFilePath;   
  
    // 显示保存文件对话框   
    if (IDOK == fileDlg.DoModal())   
    {    
        strFilePath = fileDlg.GetPathName();   
        //MessageBox(strFilePath);   

		CFile file;      // CFile对象
		if (file.Open(strFilePath, CFile::modeCreate | CFile::modeReadWrite))
		{
			char *p = m_strReceive.GetBuffer(m_strReceive.GetLength());
			file.Write(p, m_strReceive.GetLength());

			file.Close();  
		}
    }   
}


void CComDlg::OnBnClickedButtonResetCnt()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ulSendNum = 0;
	m_ulReceiveNum = 0;

	m_StatusBar.SetText("发送：0", 1, 0);
	m_StatusBar.SetText("接收：0", 2, 0);
}


void CComDlg::OnBnClickedCheckSendHex()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if (1 == m_chkHexSend.GetCheck()) //此时要把字符格式转换成十六进制
	{
		char *p = m_strSend.GetBuffer(m_strSend.GetLength());
		m_strSend.ReleaseBuffer();

		CString str = "";
		int length = m_strSend.GetLength();

		for(int i = 0; i < length; i++)
		{
			CString strTemp;
			strTemp.Format("%02X", p[i]);
			str = str + strTemp + " ";
		}
		m_strSend = str.TrimRight(" ");
	}
	else	//此时要把十六进制转换成字符格式
	{
		int length = m_strSend.GetLength();
		CString str;
		for(int i = 0; i< length; i += 3)
		{
			CString strTemp = m_strSend.Mid(i, 2);
			char *p = strTemp.GetBuffer(2);
			int num = strtol(p, NULL, 16);
			strTemp.Format("%c", num);
			str = str + strTemp;
		}
		m_strSend = str;
	}

	UpdateData(FALSE);
}


void CComDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)   
	{   
	case 1:      
		{
			if(1 == m_chkHexSend.GetCheck())
				m_mscomm.put_Output(COleVariant(hexToSend));//发送数据
			else
				m_mscomm.put_Output(COleVariant(strToSend));//发送数据
				

			//状态栏显示发送的字符个数
			CString strSendNum;
			if(1 == m_chkHexSend.GetCheck())
				m_ulSendNum += hexToSend.GetCount();
			else
				m_ulSendNum += strToSend.GetLength();

			strSendNum.Format("%d", m_ulSendNum);
			strSendNum = "发送：" + strSendNum;
			m_StatusBar.SetText(strSendNum, 1, 0);//SBT_POPOUT, SBT_NOBORDERS

			break;  
		}

	default:   
		break;   
	}   
	CDialogEx::OnTimer(nIDEvent);
}
