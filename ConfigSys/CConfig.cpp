#include "stdafx.h"
#include "CConfig.h"

CConfig::CConfig()
{
}

CConfig::~CConfig()
{
}

//Set
void CConfig::SetConf(CString & ClientName, CString & SASName, CString & DoorNb, CString& ChkAuto, CString& ChkSAuto, CString& ChkManual)
{
	m_strClientName = ClientName;
	m_strSASName = SASName;
	m_strDoorNb = DoorNb;
	m_strModeAuto = ChkAuto;
	m_strModeSauto = ChkSAuto;
	m_strModeManual = ChkManual;
}

//Print pour le load
void CConfig::Print(t_param & pParam) const
{
	pParam.pEDClientName->SetWindowTextA(m_strClientName);
	pParam.pEDSasName->SetWindowTextA(m_strSASName);
	pParam.pEDDoorNb->SetWindowTextA(m_strDoorNb);
	//pParam.pChkAuto->GetCheck(IDC_CHK_AUTO);
}



//----- Fonction friends -----//

//Load
fstream & operator >> (fstream & is, CConfig & config)
{
	// TODO: insérer une instruction return ici

	//config.m_strClientName = _T("Oui");
	int i = 0;
	CString tabParam[NB_PARAM];
	char line[BUFSIZ * 2];
	CString buf;
	
	//Tant que le buffer n'est pas remplie
	while (tabParam[NB_PARAM-1].IsEmpty())
	{
		is.getline(line, BUFSIZ * 2, '\r');
		//On regarde le premier caractère
		//Si ce n'est pas '#'
		if (CString(line).Find('#') == -1)
		{
			//On écrit la ligne dans le tableau à l'index i
			tabParam[i] = line;
			i++;
		}
	}

	config.m_strClientName = tabParam[PARAM_CLIENT_NAME];
	config.m_strSASName = tabParam[PARAM_SAS_NAME];
	config.m_strDoorNb = tabParam[PARAM_DOOR_NB];

	return is;
}

//Save
fstream & operator<<(fstream & os, const CConfig & config)
{
	// TODO: insérer une instruction return ici
	os << "#-------------------------# \r# SAS Configuration \r#-------------------------#\r\n" <<
		"# Client name :\r" << config.m_strClientName <<
		"\r\n# SAS name :\r" << config.m_strSASName <<
		"\r\n# Door nb :\r" << config.m_strDoorNb <<
		"\r\n# Mode :\r";
	if (config.m_strModeAuto.IsEmpty());
	else os << config.m_strModeAuto << ";";
	if (config.m_strModeSauto.IsEmpty());
	else os << config.m_strModeSauto << ";";
	if (config.m_strModeManual.IsEmpty());
	else os << config.m_strModeManual << ";";

	return os;
}
