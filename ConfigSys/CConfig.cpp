#include "stdafx.h"
#include "CConfig.h"

CConfig::CConfig()
{
}

CConfig::~CConfig()
{
}

//Set
void CConfig::SetConf(CString & ClientName, CString & SASName, CString & DoorNb, CString& ChkAuto)
{
	m_strClientName = ClientName;
	m_strSASName = SASName;
	m_strDoorNb = DoorNb;
	m_strChkAuto = ChkAuto;
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
	/*char recBuff[BUFSIZ * 2];
	CString buff;
	CString data;

	is.getline(recBuff, BUFSIZ * 2);
	buff = recBuff;

	if (recBuff[0] == '#') return;

	else
	{
		data = buff.Mid(1);
		config.m_strClientName = data;
	}*/

	//config.m_strClientName = _T("Oui");

	char line[BUFSIZ * 2];
	is.getline(line, BUFSIZ * 2);
	char* pch = strtok(line, "#");
	config.m_strClientName = pch;
	/*pch = strtok(NULL, "#");
	config.m_strSASName = pch;*/
	/*pch = strtok(NULL, ";");
	record.m_duration = pch;
	pch = strtok(NULL, ";");
	record.m_station = pch;
	pch = strtok(NULL, ";");
	record.m_statut = pch;
	pch = strtok(NULL, ";");
	record.m_course = pch;*/

	return is;


	///////////////////////////////////////////////////////////
	// ----- Il faut récupérer les données du fichier ----- //
	//////////////////////////////////////////////////////////

	//config.m_strClientName = ??
	
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
		"\r\n# Mode :\r" << config.m_strChkAuto;

	return os;
}
