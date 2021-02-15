
// ComDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "mscomm.h"
#include "PictureEx.h" // 我自己加的


// CComDlg 对话框
class CComDlg : public CDialogEx
{
// 构造
public:
	CComDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_COM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cboPort;
	CComboBox m_cboBaudRate;
	CComboBox m_cboCheck;
	CComboBox m_cboDataBit;
	CComboBox m_cboStopBit;

	void ComboAddString(void);
	CString GetOrderedStr();
	CString strToSend;
	CByteArray hexToSend;
	CMscomm m_mscomm;
	CEdit m_editSend;
	CEdit m_editReceive;
	CButton m_btnSend;
	DECLARE_EVENTSINK_MAP()
	void OnCommMscomm();
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonSend();
	CString m_strSend;
	CString m_strReceive;
	CString m_strPort;
	afx_msg void OnBnClickedButtonClearReceive();
	afx_msg void OnBnClickedButtonClearSend();
	CString m_strDataBit;
	CString m_strStopBit;

	CString m_strCheck;
	CStatic m_picIndicator;
public:
	CString ByteToString(byte rxdata[], int len);
	CString getCheck(void);
	afx_msg void OnCbnSelchangeCombo();
	CString m_strBaudRate;
	afx_msg void OnBnClickedButtonLoadFile();
	afx_msg void OnBnClickedButtonSaveFile();
	afx_msg void OnBnClickedCheckHex();
	CButton m_checkHex;
	CStatusBarCtrl m_StatusBar;
public:
	unsigned long m_ulSendNum;
	unsigned long m_ulReceiveNum;
	CButton m_chkHexSend;
	CButton m_chkHexReceive;
	afx_msg void OnBnClickedButtonResetCnt();
	afx_msg void OnBnClickedCheckSendHex();
	CButton m_chkTimer;
	UINT m_uiSecs;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CButton m_btnSaveFile;
	CButton m_btnLoadFile;
	CButton m_btnClearSend;
	CEdit m_editTime;
	CButton m_btnOpen;
};
