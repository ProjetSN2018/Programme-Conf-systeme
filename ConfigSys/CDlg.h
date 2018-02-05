#pragma once
#include "CConfig.h"

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
		ST_INSERTION = 0x000001,
		ST_CLIENT_NAME_OK = 0x000002,
		ST_SAS_NAME_OK = 0x000004,
		ST_DOOR_NB_OK = 0x000008,
		ST_MODE_AUTO_OK = 0x000010,
		ST_MODE_SAUTO_OK = 0x000020,
		ST_MODE_MANUAL_OK = 0x000040
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

	CCheckListBox*		m_pCHK_AUTO;
	CCheckListBox*		m_pCHK_SAUTO;
	CCheckListBox*		m_pCHK_MANUAL;

	int					m_nStatus;
	CString				m_ClientName;
	CString				m_SASName;
	CString				m_DoorNb;
	CString				m_ModeAuto;
	CString				m_ModeSauto;
	CString				m_ModeManual;

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
	afx_msg void OnEnKillfocusEdClientName();
	afx_msg void OnEnKillfocusEdSasName();
	afx_msg void OnEnKillfocusEdDoorNb();
	afx_msg void OnBnClickedChkAuto();
	afx_msg void OnBnClickedChkSauto();
	afx_msg void OnBnClickedChkManual();
};
