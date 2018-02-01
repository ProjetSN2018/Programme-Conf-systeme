
// CDlg.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "ConfigSys.h"
#include "CDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define	ST_CDLG_LOAD_DONE		0x00000001

// boîte de dialogue CDlg



CDlg::CDlg(CWnd* pParent /*=NULL*/)
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
END_MESSAGE_MAP()


// gestionnaires de messages pour CDlg

BOOL CDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Définir l'icône de cette boîte de dialogue.  L'infrastructure effectue cela automatiquement
	//  lorsque la fenêtre principale de l'application n'est pas une boîte de dialogue
	SetIcon(m_hIcon, TRUE);			// Définir une grande icône
	SetIcon(m_hIcon, FALSE);		// Définir une petite icône

	// TODO: ajoutez ici une initialisation supplémentaire

	//
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
		m_pED_DOOR_NB
	};

	m_nStatus = 0;

	return TRUE;  // retourne TRUE, sauf si vous avez défini le focus sur un contrôle
}

void CDlg::OnCancel()
{
	// TODO: ajoutez ici votre code spécialisé et/ou l'appel de la classe de base
	//delete m_pConfigs; m_pConfigs = nullptr;

	int quit = MessageBox(_T("Do you want to quit ?"), _T("EXIT"), MB_ICONQUESTION | MB_YESNO);
	if(quit == 6) CDialogEx::OnCancel();
}

// Si vous ajoutez un bouton Réduire à votre boîte de dialogue, vous devez utiliser le code ci-dessous
//  pour dessiner l'icône.  Pour les applications MFC utilisant le modèle Document/Vue,
//  cela est fait automatiquement par l'infrastructure.

void CDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // contexte de périphérique pour la peinture

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Centrer l'icône dans le rectangle client
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Dessiner l'icône
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Le système appelle cette fonction pour obtenir le curseur à afficher lorsque l'utilisateur fait glisser
//  la fenêtre réduite.
HCURSOR CDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//----- NEW -----//
void CDlg::OnBnClickedBtNew()
{
	// TODO: ajoutez ici le code de votre gestionnaire de notification de contrôle
	if (mIsBitsSet(m_nStatus, ST_INSERTION))
	{
		if (mIsBitsSet(m_nStatus, ST_CLIENT_NAME_OK) && mIsBitsSet(m_nStatus, ST_SAS_NAME_OK) && mIsBitsSet(m_nStatus, ST_DOOR_NB_OK))
		{
			mBitsClr(m_nStatus, ST_INSERTION);
			m_Config.SetConf(m_ClientName, m_SASName, m_DoorNb);
			SetDlgItemText(IDC_BT_NEW, _T("New"));
			m_pBT_LOAD->EnableWindow();
			SetDlgItemText(IDC_BT_LOAD, _T("Load"));
			m_pED_CLIENT_NAME->EnableWindow(false);
			m_pED_SAS_NAME->EnableWindow(false);
			m_pBT_SAVE->EnableWindow();
		}
		else
		{
			MessageBox(_T("Missing parameter(s) !"), _T("ERROR !!!"), MB_ICONERROR);
		}
	}
	else
	{
		mBitsSet(m_nStatus, ST_INSERTION);
		SetDlgItemText(IDC_ED_CLIENT_NAME, _T(""));
		SetDlgItemText(IDC_ED_SAS_NAME, _T(""));
		SetDlgItemText(IDC_ED_DOOR_NB, _T(""));

		SetDlgItemText(IDC_BT_NEW, _T("Add"));
		m_pBT_LOAD->EnableWindow();
		SetDlgItemText(IDC_BT_LOAD, _T("Cancel"));
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
	if (mIsBitsSet(m_nStatus, ST_INSERTION))
	{
		//Si on est en mode insertion
		mBitsClr(m_nStatus, ST_INSERTION);

		SetDlgItemText(IDC_ED_CLIENT_NAME, _T(""));
		SetDlgItemText(IDC_ED_SAS_NAME, _T(""));
		SetDlgItemText(IDC_ED_DOOR_NB, _T(""));

		m_pBT_SAVE->EnableWindow(false);

		m_pED_CLIENT_NAME->EnableWindow(false);
		m_pED_SAS_NAME->EnableWindow(false);
		m_pED_DOOR_NB->EnableWindow(false);

	/*	m_pCHK_AUTO->EnableWindow(false);
		m_pCHK_SAUTO->EnableWindow(false);
		m_pCHK_MANUAL->EnableWindow(false);*/


		SetDlgItemText(IDC_BT_NEW, "New");
		SetDlgItemText(IDC_BT_LOAD, "Load");
	}

	else
	{
		// TODO: ajoutez ici le code de votre gestionnaire de notification de contrôle
		CString openFilter(_T("Config File (*.conf)|*.conf||")); //Filtre d'extension des fichiers
		CFileDialog fileOpenDialog(
			TRUE,		//Boite de dialogue "Ouvrir"
			_T("conf"),
			NULL,
			OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST,
			openFilter,
			AfxGetMainWnd()
		);
		mBitsClr(m_nStatus, ST_CDLG_LOAD_DONE);
		if (fileOpenDialog.DoModal() == IDOK)
		{//Si un nom de fichier a été sélectionné....
			fstream file;
			file.open(fileOpenDialog.GetPathName().GetString(), fstream::in);
			if (file.is_open())
			{
				do {
					file >> m_Config;
				} while (!file.eof());

				file.close();
				m_Config.Print(m_param);
			}
		}
	}
}

//----- SAVE -----//
void CDlg::OnBnClickedBtSave()
{
	// TODO: ajoutez ici le code de votre gestionnaire de notification de contrôle
	CString openFilter(_T("Config File (*.conf)|*.conf||")); //Filtre d'extension des fichiers  
	CFileDialog fileOpenDialog(
		FALSE,  //Boite de dialogue "Enregister sous..."  
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
			file << m_Config;

			file.close();
		}
	}
}


void CDlg::OnEnKillfocusEdClientName()
{
	// TODO: ajoutez ici le code de votre gestionnaire de notification de contrôle
	if (mIsBitsSet(m_nStatus, ST_INSERTION))
	{
		m_pED_CLIENT_NAME->GetWindowTextA(m_ClientName);
		if (m_ClientName.IsEmpty())return;
		mBitsSet(m_nStatus, ST_CLIENT_NAME_OK);
	}
}


void CDlg::OnEnKillfocusEdSasName()
{
	// TODO: ajoutez ici le code de votre gestionnaire de notification de contrôle
	if (mIsBitsSet(m_nStatus, ST_INSERTION))
	{
		m_pED_SAS_NAME->GetWindowTextA(m_SASName);
		if (m_SASName.IsEmpty())return;
		mBitsSet(m_nStatus, ST_SAS_NAME_OK);
	}
}


void CDlg::OnEnKillfocusEdDoorNb()
{
	// TODO: ajoutez ici le code de votre gestionnaire de notification de contrôle
	if (mIsBitsSet(m_nStatus, ST_INSERTION))
	{
		m_pED_DOOR_NB->GetWindowTextA(m_DoorNb);
		if (m_DoorNb.IsEmpty())return;
		mBitsSet(m_nStatus, ST_DOOR_NB_OK);
	}
}
