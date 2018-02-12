
// ConfigSys.cpp : Définit les comportements de classe pour l'application.
//

#include "stdafx.h"
#include "ConfigSys.h"
#include "CDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CApp

BEGIN_MESSAGE_MAP(CApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// construction CApp

CApp::CApp()
{
	// TODO: ajoutez ici du code de construction,
	// Placez toutes les initialisations significatives dans InitInstance
}


// Seul et unique objet CApp

CApp theApp;


// initialisation de CApp

BOOL CApp::InitInstance()
{
	CWinApp::InitInstance();


	// Créer le gestionnaire de shell, si la boîte de dialogue contient
	// des contrôles d'arborescence ou de liste de shell.
	CShellManager *pShellManager = new CShellManager;

	// Active le gestionnaire visuel "natif Windows" pour activer les thèmes dans les contrôles MFC
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Initialisation standard
	// Si vous n'utilisez pas ces fonctionnalités et que vous souhaitez réduire la taille
	// de votre exécutable final, vous devez supprimer ci-dessous
	// les routines d'initialisation spécifiques dont vous n'avez pas besoin.
	// Changez la clé de Registre sous laquelle nos paramètres sont enregistrés
	// TODO: modifiez cette chaîne avec des informations appropriées,
	// telles que le nom de votre société ou organisation
	SetRegistryKey(_T("Applications locales générées par AppWizard"));

	CDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: placez ici le code définissant le comportement lorsque la boîte de dialogue est
		//  fermée avec OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: placez ici le code définissant le comportement lorsque la boîte de dialogue est
		//  fermée avec Annuler
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Avertissement : échec de création de la boîte de dialogue, par conséquent, l'application s'arrête de manière inattendue.\n");
		TRACE(traceAppMsg, 0, "Avertissement : si vous utilisez les contrôles MFC de la boîte de dialogue, vous ne pouvez pas exécuter #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	// Supprimer le gestionnaire de shell créé ci-dessus.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

#ifndef _AFXDLL
	ControlBarCleanUp();
#endif

	// Lorsque la boîte de dialogue est fermée, retourner FALSE afin de quitter
	//  l'application, plutôt que de démarrer la pompe de messages de l'application.
	return FALSE;
}

