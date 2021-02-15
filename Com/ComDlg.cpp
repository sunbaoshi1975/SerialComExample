
// ComDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Com.h"
#include "ComDlg.h"
#include "afxdialogex.h"

#include "mscomm.h" // comEvReceive

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CComDlg �Ի���




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
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_EARTH); // ͼ��ĳɵ�����Ǹ�ͼ��
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


// CComDlg ��Ϣ�������

BOOL CComDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	ComboAddString();
	
	/* //����ƽ׶��Ѿ���ʼ����ͼƬ�ˣ��������ﲻ����
	CBitmap bitmap;  // CBitmap�������ڼ���λͼ    
    HBITMAP hBmp;    // ����CBitmap���ص�λͼ�ľ��   
  
    bitmap.LoadBitmap(IDB_BITMAP_RED);  // ��λͼIDB_BITMAP1���ص�bitmap   
    hBmp = (HBITMAP)bitmap.GetSafeHandle();  // ��ȡbitmap����λͼ�ľ��   
    m_picIndicator.SetBitmap(hBmp);    // ����ͼƬ�ؼ�m_picIndicator��λͼͼƬΪIDB_BITMAP_RED   

	*/

	m_StatusBar.Create(WS_CHILD|WS_VISIBLE|SBT_OWNERDRAW, /*CRect(0,0,0,0),*/ CRect(500,550,0,660),this, 0);
	int strPartDim[3]= {400, 550,-1}; //�ָ�����
	m_StatusBar.SetParts(3, strPartDim);// Sets the number of parts in a status bar control and 
										// the coordinate of the right edge of each part.

	//m_StatusBar.SetMinHeight(300);

	//����״̬���ı�
	m_StatusBar.SetText("�����", 0, 0);//SBT_POPOUT, SBT_NOBORDERS
	m_StatusBar.SetText("���ͣ�0", 1, 0);
	m_StatusBar.SetText("���գ�0", 2, 0);

	//CRect rect;
	//m_StatusBar.GetClientRect(&rect);
	//CRect rectPane1;
	//m_StatusBar.GetRect(3, &rectPane1); 

/********************************************* ���á���ť�������� *************************************/
	CFont font;
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));       // zero out structure
	lf.lfHeight = 12;                      // request a 12-pixel-height font
	_tcscpy_s(lf.lfFaceName, LF_FACESIZE, _T("����"));              // request a face name "Arial"
	font.CreateFontIndirect(&lf);  // create the font
	GetDlgItem(IDC_BUTTON_SEND)->SetFont(&font);// ��ȡ��ťIDC_BUTTON_SEND��CWndָ�룬������������
/*****************************************************************************************************/

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CComDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//m_picIndicator.SetRedraw(TRUE);  
		//m_picIndicator.Invalidate();  
		//m_picIndicator.UpdateWindow();
/************** ÿ����С������ʾ���������߱����������ڵ�����ʾ��ָʾ�ƾͲ�����ʾ�ˣ�����ʵ���ػ�ָʾ�� ****************/
		CString strOpen;
		GetDlgItemText(IDC_BUTTON_OPEN, strOpen);
		if(strOpen == "��")
		{
			CBitmap bitmap;  // CBitmap�������ڼ���λͼ    
			HBITMAP hBmp;    // ����CBitmap���ص�λͼ�ľ��   

			bitmap.LoadBitmap(IDB_BITMAP_RED);  // ��λͼIDB_BITMAP1���ص�bitmap   
			hBmp = (HBITMAP)bitmap.GetSafeHandle();  // ��ȡbitmap����λͼ�ľ��   
			m_picIndicator.SetBitmap(hBmp);    // ����ͼƬ�ؼ�m_picIndicator��λͼͼƬΪIDB_BITMAP_RED

			CDialogEx::OnPaint();
		}
		else
		{
			CBitmap bitmap;  // CBitmap�������ڼ���λͼ    
			HBITMAP hBmp;    // ����CBitmap���ص�λͼ�ľ��   

			bitmap.LoadBitmap(IDB_BITMAP_GREEN);  // ��λͼIDB_BITMAP1���ص�bitmap   
			hBmp = (HBITMAP)bitmap.GetSafeHandle();  // ��ȡbitmap����λͼ�ľ��   
			m_picIndicator.SetBitmap(hBmp);    // ����ͼƬ�ؼ�m_picIndicator��λͼͼƬΪIDB_BITMAP_RED

			CDialogEx::OnPaint();
		}
/*****************************************************************************************************************/

		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
	// TODO: �ڴ˴������Ϣ����������
	UpdateData(TRUE); 

	static unsigned int cnt=0;  
	VARIANT variant_inp;    
	COleSafeArray safearray_inp;   
	long len,k;    
	byte rxdata[1024]; //���� BYTE ����   CString strtemp; 

	switch(m_mscomm.get_CommEvent())  
	{
	case CMscomm::comEvReceive: //ֵΪ 2 ��ʾ���ջ����������ַ�  

		m_mscomm.put_InputMode(CMscomm::comInputModeBinary);//�Զ����Ʒ�ʽ��ȡ����

		cnt++;   
		variant_inp = m_mscomm.get_Input();     
		safearray_inp = variant_inp; ///����ת��    
		len = safearray_inp.GetOneDimSize(); //�õ���Ч�����ݳ���   

		//״̬����ʾ���յ����ַ�����
		CString strReceiveNum;
		m_ulReceiveNum += len;
		strReceiveNum.Format("%d", m_ulReceiveNum);
		strReceiveNum = "���գ�" + strReceiveNum;
		m_StatusBar.SetText(strReceiveNum, 2, 0);//SBT_POPOUT, SBT_NOBORDERS

		for(k = 0; k < len; k++)    
		{   
			safearray_inp.GetElement(&k, rxdata + k);

			if(1 == m_chkHexReceive.GetCheck()) //���յ���������ʮ��������ʾ
			{
				//safearray_inp.GetElement(&k, rxdata + k);  
				CString strtemp = "";
				strtemp.Format(_T("%02X"),rxdata[k]);
				m_strReceive = m_strReceive + strtemp + " "; 
			}
			else	//���յ����������ַ���ʽ��ʾ
			{
				CString strtemp = "";
				//safearray_inp.GetElement(&k, rxdata + k);    
				strtemp.Format("%c",rxdata[k]); //���ַ�������ʱ����strtemp���
				m_strReceive = m_strReceive + strtemp;
			}
		}   
		break;
	}

	UpdateData(FALSE); //���±༭������

	//ע�⣺�ڸ�����༭�������֮�󣬻�Ҫ���ý��ձ༭��λ�����һ��
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE); 

	CString strOpen;
	GetDlgItemText(IDC_BUTTON_OPEN, strOpen);
	if(strOpen == "��")
	{
		m_mscomm.put_InBufferSize(1024); //���ջ�����  
		m_mscomm.put_OutBufferSize(1024);//���ͻ�����   
		m_mscomm.put_InputLen(0);//���õ�ǰ���������ݳ���Ϊ0,��ʾȫ����ȡ  
		m_mscomm.put_InputMode(CMscomm::comInputModeBinary);//�Զ����Ʒ�ʽ��д����   
		m_mscomm.put_RThreshold(1);//���ջ�������1����1�������ַ�ʱ���������������ݵ�OnComm�¼�
		
		//У��λ
		CString strCheck = getCheck();

		CString strSettings = m_strBaudRate + strCheck + m_strDataBit + m_strStopBit;
		//MessageBox(strSettings);
		//"9600,n,8,1" �� "9600n81" ����
		//m_mscomm.put_Settings(_T("9600,n,8,1"));//������9600���޼���λ��8������λ��1��ֹͣλ  
		m_mscomm.put_Settings(strSettings);

		//�˿ں�
		m_mscomm.put_CommPort(m_cboPort.GetCurSel() + 1);

		//�����򿪴��� 
		try
		{
			m_mscomm.put_PortOpen(TRUE);//put_PortOpen(TRUE)������ΪTRUE��򿪴��ڣ�ΪFALSE��رմ���
		}
		catch (CException* e)
		{
			MessageBox("�˿ڲ����ڣ�", "�򿪴���", MB_ICONERROR);
			return;
		}
		
		SetDlgItemText(IDC_BUTTON_OPEN, _T("�ر�")); //���ڴ�֮�����ð�ťΪ���رա�

		CBitmap bitmap;  // CBitmap�������ڼ���λͼ    
		HBITMAP hBmp;    // ����CBitmap���ص�λͼ�ľ��   
  
		bitmap.LoadBitmap(IDB_BITMAP_GREEN);  // ��λͼIDB_BITMAP1���ص�bitmap   
		hBmp = (HBITMAP)bitmap.GetSafeHandle();  // ��ȡbitmap����λͼ�ľ��   
		m_picIndicator.SetBitmap(hBmp);    // ����ͼƬ�ؼ�m_picIndicator��λͼͼƬΪIDB_BITMAP_RED 
	}
	else // ��ʱ�����Ѿ����ڴ�״̬
	{
		m_mscomm.put_PortOpen(FALSE);//put_PortOpen(TRUE)������ΪTRUE��򿪴��ڣ�ΪFALSE��رմ���  
		SetDlgItemText(IDC_BUTTON_OPEN, _T("��")); //���ڴ�֮�����ð�ťΪ���رա�

		CBitmap bitmap;  // CBitmap�������ڼ���λͼ    
		HBITMAP hBmp;    // ����CBitmap���ص�λͼ�ľ��   
  
		bitmap.LoadBitmap(IDB_BITMAP_RED);  // ��λͼIDB_BITMAP1���ص�bitmap   
		hBmp = (HBITMAP)bitmap.GetSafeHandle();  // ��ȡbitmap����λͼ�ľ��   
		m_picIndicator.SetBitmap(hBmp);    // ����ͼƬ�ؼ�m_picIndicator��λͼͼƬΪIDB_BITMAP_RED  
	}
}

CString CComDlg::GetOrderedStr()
{
	CString str;

	int i = 0;
	int length = m_strSend.GetLength();
	for(i = 0; i < length - 1; i++)//"31 32 33 �س� 34"   "34 31 327"    "34 31 32 7"    "32 33 3 34"
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

		if(m_strSend.Mid(i, 1) == "\r" && m_strSend.Mid(i+1, 1) == "\n") //�����س�,Ҳ����\n\r,��ֱ������\n\r�������ַ�! 
			i++;     
	}	

	if(i == m_strSend.GetLength()-1 && m_strSend.Mid(i, 1) != " ")
		str = str + "0" + m_strSend.Mid(i, 1);  //���з�ֹ"34 31 32 7"��7��ʧ
	//����, "31323334"      "34313207"      "34313207"     "32330334"

	//MessageBox(str);

	return str;
}

void CComDlg::OnBnClickedButtonSend()
{
	UpdateData(TRUE); //��ȡ�༭������    

	CString strSend;
	GetDlgItemText(IDC_BUTTON_SEND, strSend);
	if(strSend == "����")
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
				m_mscomm.put_Output(COleVariant(hexToSend));//��������
				//int num = hexToSend.GetCount();
				//TRACE("%d", num);
			}
			else
			{
				strToSend = m_strSend;
				m_mscomm.put_Output(COleVariant(strToSend));//��������
			}
			
			

			if(1 == m_chkTimer.GetCheck())
			{
				SetTimer(1, m_uiSecs, NULL); // ����IDΪ1�Ķ�ʱ������ʱʱ��Ϊ1��
				SetDlgItemText(IDC_BUTTON_SEND, _T("ֹͣ����")); //���ڴ�֮�����ð�ťΪ���رա�
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

			//״̬����ʾ���͵��ַ�����
			CString strSendNum;
			if(1 == m_chkHexSend.GetCheck())
				m_ulSendNum += hexToSend.GetCount();
			else
				m_ulSendNum += strToSend.GetLength();

			strSendNum.Format("%d", m_ulSendNum);
			strSendNum = "���ͣ�" + strSendNum;
			m_StatusBar.SetText(strSendNum, 1, 0);//SBT_POPOUT, SBT_NOBORDERS
		}
		catch (CException* e)
		{
			MessageBox("�˿���δ�򿪣�", "����", MB_ICONERROR);
			return;
		}
	}
	else
	{
		KillTimer(1); 
		SetDlgItemText(IDC_BUTTON_SEND, _T("����")); //���ڴ�֮�����ð�ťΪ���رա�
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
	
	  
	//m_mscomm.put_Output(m_editSend);//��������  
	//m_editSend.Empty(); //���ͺ��������� 
	m_editSend.SetWindowText(_T(""));

	UpdateData(FALSE); //���±༭������

	//ע�⣺�ڸ�����༭�������֮�󣬻�Ҫ���ý��ձ༭��λ�����һ��
	int nLineCount = m_editReceive.GetLineCount();
	int nLineLength = m_editReceive.LineLength(nLineCount);
	m_editReceive.LineScroll(nLineCount, nLineLength);
	//TRACE("%d", nLineCount);
}

void CComDlg::OnBnClickedButtonClearReceive()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_strReceive = "";
	//m_editReceive.SetWindowText(_T(""));
	UpdateData(FALSE);
}

void CComDlg::OnBnClickedButtonClearSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_editSend.SetWindowText(_T(""));
}

void CComDlg::OnCbnSelchangeCombo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE); //��ȡ�༭������

	CString strOpen;
	GetDlgItemText(IDC_BUTTON_OPEN, strOpen);

	if(strOpen == "�ر�")
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
			m_mscomm.put_PortOpen(FALSE);//put_PortOpen(TRUE)������ΪTRUE��򿪴��ڣ�ΪFALSE��رմ���  
			m_mscomm.put_CommPort(m_cboPort.GetCurSel() + 1);//�˿ں�
			try
			{
				m_mscomm.put_PortOpen(TRUE);//put_PortOpen(TRUE)������ΪTRUE��򿪴��ڣ�ΪFALSE��رմ���
			}
			catch (CException* e)
			{
				MessageBox("�˿ڲ����ڣ�", "�򿪴���", MB_ICONERROR);
				SetDlgItemText(IDC_BUTTON_OPEN, _T("��")); //���ڴ�֮�����ð�ťΪ���رա�

				CBitmap bitmap;  // CBitmap�������ڼ���λͼ    
				HBITMAP hBmp;    // ����CBitmap���ص�λͼ�ľ��   
  
				bitmap.LoadBitmap(IDB_BITMAP_RED);  // ��λͼIDB_BITMAP1���ص�bitmap   
				hBmp = (HBITMAP)bitmap.GetSafeHandle();  // ��ȡbitmap����λͼ�ľ��   
				m_picIndicator.SetBitmap(hBmp);    // ����ͼƬ�ؼ�m_picIndicator��λͼͼƬΪIDB_BITMAP_RED
			}	
		}
	}
}


void CComDlg::OnBnClickedButtonLoadFile()
{
	m_strSend = "";

	TCHAR szFilter[] = _T("�ı��ļ�(*.txt)|*.txt|�����ļ�(*.*)|*.*||");// ���ù�����   
    CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);// ������ļ��Ի���   
	CString strFilePath;   
  
    if (IDOK == fileDlg.DoModal())// ��ʾ���ļ��Ի���  
    {      
        strFilePath = fileDlg.GetPathName();   // ���������ļ��Ի����ϵġ��򿪡���ť����ѡ����ļ�·����ʾ���༭����
        //MessageBox(strFilePath);  

		CFile file;      // CFile����
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

	TCHAR szFilter[] = _T("�ı��ļ�(*.txt)|*.txt|Word�ļ�(*.doc)|*.doc|�����ļ�(*.*)|*.*||"); // ���ù�����  
    CFileDialog fileDlg(FALSE, _T("doc"), _T("InitFileName"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);// ���챣���ļ��Ի���   
	CString strFilePath;   
  
    // ��ʾ�����ļ��Ի���   
    if (IDOK == fileDlg.DoModal())   
    {    
        strFilePath = fileDlg.GetPathName();   
        //MessageBox(strFilePath);   

		CFile file;      // CFile����
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ulSendNum = 0;
	m_ulReceiveNum = 0;

	m_StatusBar.SetText("���ͣ�0", 1, 0);
	m_StatusBar.SetText("���գ�0", 2, 0);
}


void CComDlg::OnBnClickedCheckSendHex()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	if (1 == m_chkHexSend.GetCheck()) //��ʱҪ���ַ���ʽת����ʮ������
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
	else	//��ʱҪ��ʮ������ת�����ַ���ʽ
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent)   
	{   
	case 1:      
		{
			if(1 == m_chkHexSend.GetCheck())
				m_mscomm.put_Output(COleVariant(hexToSend));//��������
			else
				m_mscomm.put_Output(COleVariant(strToSend));//��������
				

			//״̬����ʾ���͵��ַ�����
			CString strSendNum;
			if(1 == m_chkHexSend.GetCheck())
				m_ulSendNum += hexToSend.GetCount();
			else
				m_ulSendNum += strToSend.GetLength();

			strSendNum.Format("%d", m_ulSendNum);
			strSendNum = "���ͣ�" + strSendNum;
			m_StatusBar.SetText(strSendNum, 1, 0);//SBT_POPOUT, SBT_NOBORDERS

			break;  
		}

	default:   
		break;   
	}   
	CDialogEx::OnTimer(nIDEvent);
}
