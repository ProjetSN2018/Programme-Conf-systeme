#include "stdafx.h"
#include "CConfig.h"

CConfig::CConfig()
{
}

CConfig::~CConfig()
{
}

//Print pour le load
void CConfig::Print(t_param & pParam) const
{
	pParam.pEDClientName->SetWindowText(m_strClientName);
	pParam.pEDSasName->SetWindowText(m_strSASName);
	pParam.pEDDoorNb->SetWindowText(m_strDoorNb);



	/*if (m_strMode == "Auto;") { pParam.pChkAuto->SetCheck(BST_CHECKED); }
	if (m_strMode == "Semi auto;") { pParam.pChkSauto->SetCheck(BST_CHECKED); }
	if (m_strMode == "Manuel;") { pParam.pChkManual->SetCheck(BST_CHECKED); }
	if (m_strMode == "Auto;Semi auto;") 
	{ 
		pParam.pChkAuto->SetCheck(BST_CHECKED);
		pParam.pChkSauto->SetCheck(BST_CHECKED);
	}
	if (m_strMode == "Auto;Manuel;")
	{
		pParam.pChkAuto->SetCheck(BST_CHECKED);
		pParam.pChkManual->SetCheck(BST_CHECKED);
	}
	if (m_strMode == "Semi auto;Manuel;")
	{
		pParam.pChkSauto->SetCheck(BST_CHECKED);
		pParam.pChkManual->SetCheck(BST_CHECKED);
	}
	if (m_strMode == "Auto;Semi auto;Manuel;")
	{
		pParam.pChkAuto->SetCheck(BST_CHECKED);
		pParam.pChkSauto->SetCheck(BST_CHECKED);
		pParam.pChkManual->SetCheck(BST_CHECKED);
	}*/
}

bool CConfig::SetConfig(t_param& param)
{
	param.pEDClientName->GetWindowText(m_strClientName);
	param.pEDSasName->GetWindowText(m_strSASName);
	param.pEDDoorNb->GetWindowText(m_strDoorNb);
	if (param.pChkAuto->GetCheck()) param.pChkAuto->GetWindowText(m_strModeAuto);
	if (param.pChkSauto->GetCheck()) param.pChkSauto->GetWindowText(m_strModeSauto);
	if (param.pChkManual->GetCheck()) param.pChkManual->GetWindowText(m_strModeManual);


	if (m_strClientName.IsEmpty() || m_strSASName.IsEmpty() || m_strDoorNb.IsEmpty() || (m_strModeAuto.IsEmpty() && m_strModeSauto.IsEmpty() && m_strModeManual.IsEmpty())) return false;
	if (param.pEDClientName->GetWindowTextLength() > 15 ||
		param.pEDSasName->GetWindowTextLength() > 10 ||
		m_strDoorNb > (CString)_T("5") || m_strDoorNb <= (CString)_T("0")
		) return false;

	return true;
}



//----- Fonction friends -----//

//Load
fstream & operator >> (fstream & is, CConfig & config)
{
	// TODO: insérer une instruction return ici

	int i = 0;
	CString tabParam[NB_PARAM];
	char line[BUFSIZ * 2];
	
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
	//config.m_strMode = tabParam[PARAM_MODE];

	return is;
}

//Save
fstream & operator<<(fstream & os, const CConfig & config)
{
	// TODO: insérer une instruction return ici

	os << "#-------------------------# \r# SAS Configuration \r#-------------------------#\r\n" <<
		"# Client name :\r" << CStringA(config.m_strClientName) <<
		"\r\n# SAS name :\r" << CStringA(config.m_strSASName) <<
		"\r\n# Door nb :\r" << CStringA(config.m_strDoorNb) <<
		"\r\n# Mode :\r";
	if (config.m_strModeAuto.IsEmpty());
	else os << CStringA(config.m_strModeAuto) << ";";
	if (config.m_strModeSauto.IsEmpty());
	else os << CStringA(config.m_strModeSauto) << ";";
	if (config.m_strModeManual.IsEmpty());
	else os << CStringA(config.m_strModeManual) << ";";

	return os;
}