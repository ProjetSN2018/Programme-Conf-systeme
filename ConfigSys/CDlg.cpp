#include "stdafx.h"
#include "ConfigSys.h"
#include "CDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// boîte de dialogue CDlg

CDlg::CDlg(CWnd* pParent)
	: CDialogEx(IDD_CONFIGSYS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BT_NEW, &CDlg::OnBnClickedBtNew)
	ON_BN_CLICKED(IDC_BT_LOAD, &CDlg::OnBnClickedBtLoad)
	ON_BN_CLICKED(IDC_BT_SAVE, &CDlg::OnBnClickedBtSave)
	ON_EN_KILLFOCUS(IDC_ED_CLIENT_NAME, &CDlg::OnEnKillfocusEdClientName)
	ON_EN_KILLFOCUS(IDC_ED_SAS_NAME, &CDlg::OnEnKillfocusEdSasName)
	ON_EN_KILLFOCUS(IDC_ED_DOOR_NB, &CDlg::OnEnKillfocusEdDoorNb)
	ON_BN_CLICKED(IDC_CHK_AUTO, &CDlg::OnBnClickedChkAuto)
	ON_BN_CLICKED(IDC_CHK_SAUTO, &CDlg::OnBnClickedChkSauto)
	ON_BN_CLICKED(IDC_CHK_MANUAL, &CDlg::OnBnClickedChkManual)
END_MESSAGE_MAP()


// gestionnaires de messages pour CDlg

//Initialisation
BOOL CDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);		

	/////////////////////////////////////////
	m_pST_CLIENT_NAME = (CStatic*)GetDlgItem(IDC_ST_CIENT_NAME);
	m_pST_SAS_NAME = (CStatic*)GetDlgItem(IDC_ST_SAS_NAME);
	m_pST_DOOR_NB = (CStatic*)GetDlgItem(IDC_ST_DOOR_NB);
	m_pST_MODE = (CStatic*)GetDlgItem(IDC_ST_MODE);

	m_pED_CLIENT_NAME = (CEdit*)GetDlgItem(IDC_ED_CLIENT_NAME);
	m_pED_SAS_NAME = (CEdit*)GetDlgItem(IDC_ED_SAS_NAME);
	m_pED_DOOR_NB = (CEdit*)GetDlgItem(IDC_ED_DOOR_NB);

	m_pCHK_AUTO = (CCheckListBox*)GetDlgItem(IDC_CHK_AUTO);
	m_pCHK_SAUTO = (CCheckListBox*)GetDlgItem(IDC_CHK_SAUTO);
	m_pCHK_MANUAL = (CCheckListBox*)GetDlgItem(IDC_CHK_MANUAL);

	m_pBT_NEW = (CButton*)GetDlgItem(IDC_BT_NEW);
	m_pBT_LOAD = (CButton*)GetDlgItem(IDC_BT_LOAD);
	m_pBT_SAVE = (CButton*)GetDlgItem(IDC_BT_SAVE);

	m_pBT_SAVE->EnableWindow(false);

	m_pED_CLIENT_NAME->EnableWindow(false);
	m_pED_SAS_NAME->EnableWindow(false);
	m_pED_DOOR_NB->EnableWindow(false);

	m_pCHK_AUTO->EnableWindow(false);
	m_pCHK_SAUTO->EnableWindow(false);
	m_pCHK_MANUAL->EnableWindow(false);
	
	m_param = {
		m_pED_CLIENT_NAME,
		m_pED_SAS_NAME,
		m_pED_DOOR_NB,
		m_pCHK_AUTO,
		m_pCHK_SAUTO,
		m_pCHK_MANUAL
	};

	m_nStatus = 0;

	return TRUE;  // retourne TRUE, sauf si vous avez défini le focus sur un contrôle
}

void CDlg::OnCancel()
{
	//Verification si l'utilisateur veut quitter
	int quit = MessageBox(_T("Do you want to quit ?"), _T("EXIT"), MB_ICONQUESTION | MB_YESNO);
	//Si oui, on quitte
	if(quit == 6) CDialogEx::OnCancel();
}

void CDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Centrer l'icône dans le rectangle client
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon);
		int y = (rect.Height() - cyIcon);

		// Dessiner l'icône
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//----- NEW -----//
void CDlg::OnBnClickedBtNew()
{
	//Déjà en insertion = add
	if (mIsBitsSet(m_nStatus, ST_INSERTION))
	{
		//Si tous les ch sont remplient
		if (mIsBitsSet(m_nStatus, ST_CLIENT_NAME_OK) && mIsBitsSet(m_nStatus, ST_SAS_NAME_OK) && mIsBitsSet(m_nStatus, ST_DOOR_NB_OK) && ((mIsBitsSet(m_nStatus, ST_MODE_AUTO_OK)) || (mIsBitsSet(m_nStatus, ST_MODE_SAUTO_OK)) || (mIsBitsSet(m_nStatus, ST_MODE_MANUAL_OK))))
		{
			mBitsClr(m_nStatus, ST_INSERTION);

			//Set les paramètres écrit par l'utilisateur dans l'objet CConfig
			m_Config.SetConf(m_ClientName, m_SASName, m_DoorNb, m_ModeAuto,m_ModeSauto,m_ModeManual);
			SetDlgItemText(IDC_BT_NEW, _T("New"));
			//m_pBT_LOAD->EnableWindow();
			SetDlgItemText(IDC_BT_LOAD, _T("Load"));
			m_pED_CLIENT_NAME->EnableWindow(false);
			m_pED_SAS_NAME->EnableWindow(false);
			m_pBT_SAVE->EnableWindow();
		}
		else MessageBox(_T("Missing parameter(s) !"), _T("ERROR !!!"), MB_ICONERROR);
	}

	//Passage en mode insertion
	else
	{
		mBitsSet(m_nStatus, ST_INSERTION);
		SetDlgItemText(IDC_ED_CLIENT_NAME, _T(""));
		SetDlgItemText(IDC_ED_SAS_NAME, _T(""));
		SetDlgItemText(IDC_ED_DOOR_NB, _T(""));

		SetDlgItemText(IDC_BT_NEW, _T("Add"));
		m_pBT_LOAD->EnableWindow();
		SetDlgItemText(IDC_BT_LOAD, _T("Cancel"));

		//Activation des fenêtre pour entrer les paramèrtres
		m_pED_CLIENT_NAME->EnableWindow();
		m_pED_SAS_NAME->EnableWindow();
		m_pED_DOOR_NB->EnableWindow();
		m_pCHK_AUTO->EnableWindow();
		m_pCHK_SAUTO->EnableWindow();
		m_pCHK_MANUAL->EnableWindow();
	}
}

//----- LOAD -----//
void CDlg::OnBnClickedBtLoad()
{
	//Si on est en mode insertion = cancel
	if (mIsBitsSet(m_nStatus, ST_INSERTION))
	{
		mBitsClr(m_nStatus, ST_INSERTION);

		//Clear les fenêtres
		SetDlgItemText(IDC_ED_CLIENT_NAME, _T(""));
		SetDlgItemText(IDC_ED_SAS_NAME, _T(""));
		SetDlgItemText(IDC_ED_DOOR_NB, _T(""));

		//m_pCHK_AUTO->SetCheck(IDC_CHK_AUTO, BST_UNCHECKED);
		m_pBT_LOAD->EnableWindow(false);

		//On désactive les fenêtres
		m_pBT_SAVE->EnableWindow(false);

		m_pED_CLIENT_NAME->EnableWindow(false);
		m_pED_SAS_NAME->EnableWindow(false);
		m_pED_DOOR_NB->EnableWindow(false);
		m_pCHK_AUTO->EnableWindow(false);
		m_pCHK_SAUTO->EnableWindow(false);
		m_pCHK_MANUAL->EnableWindow(false);


		SetDlgItemText(IDC_BT_NEW, "New");
		SetDlgItemText(IDC_BT_LOAD, "Load");
	}

	//Sinon
	else
	{
		CString openFilter(_T("Config File (*.conf)|*.conf||")); //Filtre d'extension des fichiers
		CFileDialog fileOpenDialog(
			TRUE,		//Boite de dialogue "Ouvrir"
			_T("conf"),
			NULL,
			OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST,
			openFilter,
			AfxGetMainWnd()
		);
		if (fileOpenDialog.DoModal() == IDOK)
		{//Si un nom de fichier a été sélectionné....
			fstream file;
			file.open(fileOpenDialog.GetPathName().GetString(), fstream::in);
			if (file.is_open())
			{
				//On écrit ce qu'il y a dans le fichier dans l'objet
				do {
					file >> m_Config;
				} while (!file.eof());

				file.close();

				//On afffcihe
				m_Config.Print(m_param);
			}
			//On active les fenêtres
			m_pED_CLIENT_NAME->EnableWindow();
			m_pED_SAS_NAME->EnableWindow();
			m_pED_DOOR_NB->EnableWindow();
			m_pCHK_AUTO->EnableWindow();
			m_pCHK_SAUTO->EnableWindow();
			m_pCHK_MANUAL->EnableWindow();
			m_pBT_SAVE->EnableWindow();
		}
	}
}

//----- SAVE -----//
void CDlg::OnBnClickedBtSave()
{
	CString openFilter(_T("Config File (*.conf)|*.conf||"));
	CFileDialog fileOpenDialog(
		FALSE,
		_T("conf"),
		NULL,
		OFN_HIDEREADONLY,
		openFilter,
		AfxGetMainWnd()
	);
	if (fileOpenDialog.DoModal() == IDOK)
	{
		fstream file;
		file.open(fileOpenDialog.GetPathName().GetString(), fstream::out);
		if (file.is_open())
		{
			//On écrit de l'objet vers le fichier
			file << m_Config;
			file.close();
		}
	}
}

void CDlg::OnEnKillfocusEdClientName()
{
	m_pED_CLIENT_NAME->GetWindowTextA(m_ClientName);
	if (m_ClientName.IsEmpty())return;
	mBitsSet(m_nStatus, ST_CLIENT_NAME_OK);
}


void CDlg::OnEnKillfocusEdSasName()
{
	m_pED_SAS_NAME->GetWindowTextA(m_SASName);
	if (m_SASName.IsEmpty())return;
	mBitsSet(m_nStatus, ST_SAS_NAME_OK);
}


void CDlg::OnEnKillfocusEdDoorNb()
{
	m_pED_DOOR_NB->GetWindowTextA(m_DoorNb);
	if (m_DoorNb.IsEmpty())return;
	mBitsSet(m_nStatus, ST_DOOR_NB_OK);
}


void CDlg::OnBnClickedChkAuto()
{
	m_pCHK_AUTO->GetWindowTextA(m_DoorNb);
	if (m_DoorNb.IsEmpty())return;
	mBitsSet(m_nStatus, ST_MODE_AUTO_OK);
}


void CDlg::OnBnClickedChkSauto()
{
	m_pCHK_SAUTO->GetWindowTextA(m_ModeSauto);
	if (m_DoorNb.IsEmpty())return;
	mBitsSet(m_nStatus, ST_MODE_SAUTO_OK);
}


void CDlg::OnBnClickedChkManual()
{
	m_pCHK_MANUAL->GetWindowTextA(m_ModeManual);
	if (m_DoorNb.IsEmpty())return;
	mBitsSet(m_nStatus, ST_MODE_MANUAL_OK);
}