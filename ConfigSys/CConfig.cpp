#include "stdafx.h"
#include "CConfig.h"

CConfig::CConfig()
{
}

CConfig::~CConfig()
{
}

//Set
void CConfig::SetConf(CString & ClientName, CString & SASName, CString & DoorNb)
{
	m_strClientName = ClientName;
	m_strSASName = SASName;
	m_strDoorNb = DoorNb;
}

//Print pour le load
void CConfig::Print(t_param & pParam) const
{
	pParam.pEDClientName->SetWindowTextA(m_strClientName);
	pParam.pEDSasName->SetWindowTextA(m_strSASName);
}







//----- Fonction friends -----//

//Load
fstream & operator >> (fstream & is, CConfig & config)
{
	// TODO: insérer une instruction return ici
	char line[BUFSIZ * 2];

	is.getline(line, BUFSIZ * 2);


	///////////////////////////////////////////////////////////
	// ----- Il faut récupérer les données du fichier ----- //
	//////////////////////////////////////////////////////////

	config.m_strClientName = _T("Oui");
	//config.m_strClientName = ??
	
	return is;
}

//Save
fstream & operator<<(fstream & os, const CConfig & config)
{
	// TODO: insérer une instruction return ici
	os << "#-------------------------# \r# SAS Configuration \r#-------------------------#\r\n" <<
		"# Client name :\r" << config.m_strClientName << "\r\n# SAS name :\r" << config.m_strSASName << "\r\n# Door nb :\r" << config.m_strDoorNb;
	return os;
}
