#pragma once
#include "CConfig.h"
#include "afxwin.h"

// boîte de dialogue CDlg
class CDlg : public CDialogEx
{
// Construction
public:
	CDlg(CWnd* pParent = NULL);	// constructeur standard

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONFIGSYS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);


// Implémentation
protected:
	HICON m_hIcon;

public :
	enum t_status {
		NONE = 0,
		ALL = 0xFFFFFFFF,
		ST_INSERTION = 0x000001
	};

private:
	CConfig				m_Config;

	CConfig::t_param	m_param;

	CStatic*			m_pST_CLIENT_NAME;
	CStatic*			m_pST_SAS_NAME;
	CStatic*			m_pST_DOOR_NB;
	CStatic*			m_pST_MODE;

	CEdit*				m_pED_CLIENT_NAME;
	CEdit*				m_pED_SAS_NAME;
	CEdit*				m_pED_DOOR_NB;

	CButton*			m_pBT_NEW;
	CButton*			m_pBT_LOAD;
	CButton*			m_pBT_SAVE;

	CButton*			m_pCHK_AUTO;
	CButton*			m_pCHK_SAUTO;
	CButton*			m_pCHK_MANUAL;

	int					m_nStatus;

protected:
	// Fonctions générées de la table des messages
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtNew();
	afx_msg void OnBnClickedBtLoad();
	afx_msg void OnBnClickedBtSave();
	virtual void OnCancel();
	afx_msg void OnChgeClientName();
};
